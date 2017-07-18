# -*- coding: utf-8 -*-
from os import getcwd
from os.path import dirname, abspath, normpath, join
import sys
import pandas as pd
from copy import copy

BASEPATH = normpath(getcwd() + '/../../')
sys.path.append(BASEPATH)
sys.path.append(join(BASEPATH, 'src'))

from bots.base_bot.base_bot.trainer import Trainer as BaseTrainer
from src import app
from decorators import app_context
from sklearn.metrics import accuracy_score
import numpy as np
from bots.base_bot.base_bot.trainer import DataAccessor as Accessor
import pandas as pd
from models.line_bot import LineBotConfig
from models.templates import Template
from models.line_bot import LineBot


class DataAccessorContest(Accessor):

    def __init__(self, code, bot_id):
        super(DataAccessorContest, self).__init__(code, bot_id)

    @staticmethod
    def str_to_datetime(_str):
        from datetime import datetime as dt
        return dt.strptime(_str, '%Y-%m-%d %H:%M:%S')

    @classmethod
    def get_train_templates(cls, bot_id, _operator, str_period):
        import operator
        columns = ',index,request,response,id'.split(',')
        df = pd.DataFrame(columns=columns)
        config = LineBotConfig.query.filter_by(line_bot_id=bot_id).first()
        if config is None:
            return df
        templates = config.templates.filter(
            Template.status != 'deleting').all()
        data = []
        datetime_period = DataAccessorContest.str_to_datetime(str_period)
        print datetime_period
        for t in templates:
            if t.created_at <= datetime_period:
                data.append([0, t.name, t.request, t.response, t.id])
                for r in t.requests:
                    if (r.created_at is None):
                        if _operator is operator.gt or _operator is operator.ge:
                            pass
                        else:
                            data.append(
                                [0, t.name, r.request, t.response, t.id])
                    else:
                        if _operator(r.created_at, datetime_period):
                            data.append(
                                [0, t.name, r.request, t.response, t.id])

        df = pd.DataFrame(data, columns=columns)
        df['id'] = df['id'].astype('int64')  # float64 -> int64
        return df

    def get_templates(self, str_period, _operator):
        return DataAccessorContest.get_train_templates(self.bot_id, str_period, _operator)


class ContestTrainer(BaseTrainer):
    codes = []
    steps = 24000
    data_accessor_class = DataAccessorContest
    model = None

    def __init__(self, *args, **kwargs):
        try:
            super(ContestTrainer, self).__init__(*args, **kwargs)
            print "Successfully loaded {} data".format(self.code)
        except:
            print "Cannot load bot data"
            raise

    def get_data(self,  _operator, str_period):
        templates = self.data_accessor.get_templates(_operator, str_period)
        docs = templates['request'].reset_index(drop=True)
        labels = templates['index'].reset_index(drop=True)
        responses = templates['response'].reset_index(drop=True)
        return docs, labels, responses

    def get_training_data(self, str_period, for_eval=False):
        import operator
        return self.get_data(operator.le, str_period)

    def get_test_data(self, str_period, for_eval=False):
        import operator
        return self.get_data(operator.gt, str_period)

    def train(self, model, str_period, seed=42, steps_list=None, classifier_params=None):
        print 'Loading train data from bot ' + str(self.bot_id) + '...'
        docs, labels, responses = app_context(
            self.get_training_data)(str_period, for_eval=True)
        valid_ind = ~pd.isnull(docs).values
        docs = docs[valid_ind]
        labels = labels[valid_ind]

        if isinstance(docs, pd.Series):
            docs.reset_index(drop=True, inplace=True)
        if isinstance(labels, pd.Series):
            labels.reset_index(drop=True, inplace=True)

        np.random.seed(seed)

        n_samples = len(labels)
        indices = np.random.permutation(n_samples)

        shuffle_docs = docs[indices]
        shuffle_labels = labels[indices]

        extra_docs = []

        if classifier_params is None:
            classifier_params = {}

        if steps_list is None:
            steps_list = [self.steps]

        print 'Training...'
        for i, steps in enumerate(steps_list):
            _classifier_params = copy(classifier_params)
            if i > 0:
                _classifier_params.update({'continue_training': True})

            model.map_and_fit(
                shuffle_docs, shuffle_labels, extra_docs=extra_docs, dnn_steps=steps,
                classifier_params=_classifier_params, library=self.library
            )

        return model

    def eval(self, model, str_period):
        print 'Loading test data from bot ' + str(self.bot_id) + '...'
        docs, labels, responses = app_context(
            self.get_test_data)(str_period, for_eval=True)
        valid_ind = ~pd.isnull(docs).values
        docs = docs[valid_ind]
        labels = labels[valid_ind]

        # top1 score
        y_pred = model.predict_and_map(docs)
        top1 = accuracy_score(y_pred, labels)

        label_list = model.label_mapping
        n = 3
        y_proba = model.predict_proba(docs)
        top_n = np.argsort(y_proba)[:, :-n - 1:-1]
        count = 0

        # top3 score & mAP
        avg_score = 0.0
        y_rankings = np.argsort(y_proba)[:, ::-1]

        for i, label in enumerate(labels):
            int_label = label_list.index(label)
            if int_label in top_n[i]:
                count += 1

            index, = np.where(y_rankings[i] == int_label)
            avg_score += 1.0 / (index[0] + 1.0)

        top3 = count * 1.0 / len(labels)
        avg_score /= len(y_pred)

        return top1, top3, avg_score
