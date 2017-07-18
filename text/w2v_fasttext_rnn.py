import sys
import importlib
from os.path import join, normpath, dirname, abspath
from os import getcwd

BASEPATH = normpath(getcwd() + '/../../')
sys.path.append(BASEPATH)
sys.path.append(join(BASEPATH, 'src'))

from contest_class import ContestTrainer

bot_ids = [4, 6, 11, 13, 14, 15, 19]
contest_instances = [ContestTrainer(bot_id) for bot_id in bot_ids]
str_period = '2017-02-28 23:59:59'

from gensim.models import word2vec
import MeCab
import numpy as np
from sklearn.pipeline import Pipeline
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.preprocessing import FunctionTransformer
from keras.models import Sequential
from keras.layers.core import Dense, Activation, Flatten, Dropout
from keras.layers import Convolution1D, MaxPooling1D
from keras_tqdm import TQDMNotebookCallback
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.base import BaseEstimator, TransformerMixin
from model.mixin import LabelMapperMixin

# Utility
dense_transformer = FunctionTransformer(lambda x: x.astype(np.float).toarray(), accept_sparse=True)
tagger = MeCab.Tagger('-O wakati')
def tokenize(text):
    return tagger.parse(text.strip()).split(' ')[:-1]

def get_wordvector_sequence(w2v_model, terms, max_sequence_length):
    vectors = np.ndarray((
        min(len(terms), max_sequence_length),
        w2v_model.vector_size
    ))
    
    for i, term in enumerate(terms[:max_sequence_length]):
        try:
            vectors[i] = w2v_model[term.decode('utf8')]
        except KeyError:
            vectors[i] = np.random.uniform(-0.25, 0.25, w2v_model.vector_size)

    return vectors

def get_wordvector_sequences(w2v_model, tokenized_texts, max_sequence_length):
    result = np.zeros((len(tokenized_texts), max_sequence_length, w2v_model.vector_size))
    
    for i, tokens in enumerate(tokenized_texts):
        wordvectors = get_wordvector_sequence(w2v_model, tokens, max_sequence_length)
        result[i, :wordvectors.shape[0]] = wordvectors
    
    return result
    
class RNNModel(LabelMapperMixin):
    def __init__(self, w2v_model, tokenizer = None):
        self.MAX_SEQUENCE_LENGTH = 20
        self.w2v_model = w2v_model
        self.EMBEDDING_DIM = w2v_model.vector_size
        if tokenizer:
            self.tokenizer = tokenizer
    
    def create_keras_model(self, n_classes):
        model = Sequential()

        model.add(Convolution1D(
            input_shape=(self.MAX_SEQUENCE_LENGTH, self.EMBEDDING_DIM),
            nb_filter=250,
            filter_length=3,
            border_mode='valid',
            activation='relu',
            subsample_length=1
        ))
        model.add(MaxPooling1D(pool_length=model.output_shape[1]))
        model.add(Flatten())
        model.add(Dense(250))
        model.add(Dropout(0.2))
        model.add(Activation('relu'))
        model.add(Dense(n_classes, activation='softmax'))
        model.compile(loss='sparse_categorical_crossentropy',
                      optimizer='Adam',
                      metrics=['acc'])
        return model
            
    def fit(self, docs, labels, *args, **kwargs):

        n_classes = np.max(labels) + 1
        
        X = get_wordvector_sequences(self.w2v_model, [tokenize(doc) for doc in docs], self.MAX_SEQUENCE_LENGTH)
        
        classifier = self.create_keras_model(n_classes);
        classifier.fit(X, labels, nb_epoch=20, batch_size=32)
        self.classifier = classifier
                
    def predict(self, docs):
        X = get_wordvector_sequences(self.w2v_model, [tokenize(doc) for doc in docs], self.MAX_SEQUENCE_LENGTH)
        return self.classifier.predict(X).argmax(axis=-1)

    def predict_proba(self, docs):
        X = get_wordvector_sequences(self.w2v_model, [tokenize(doc) for doc in docs], self.MAX_SEQUENCE_LENGTH)
        return self.classifier.predict_proba(X)


import sys
import importlib
from os.path import join, normpath, dirname, abspath
from os import getcwd
from bots.base_bot.base_bot.model.tokenizer import NormalTokenizer
from text_preprocessing import MeCabSplitter

BASEPATH = normpath(getcwd() + '/../../')
sys.path.append(BASEPATH)
sys.path.append(join(BASEPATH, 'src'))
from gensim.models import word2vec

# fasttext model
MODELPATH = join(BASEPATH, 'etc/keras/model/entity_vector/wiki.ja.vec')

w2v_model = word2vec.Word2Vec.load_word2vec_format(MODELPATH, binary=False)

models = [RNNModel(w2v_model, tokenizer = tokenize) for bot_id in bot_ids]

for trainer, model in zip(contest_instances, models):
    trainer.train(model, str_period)
    
import pandas as pd
columns = 'bot,bot_name,top1,top3,avg_score'.split(',')
df = pd.DataFrame(columns=columns)

result = []
for i, model in enumerate(models):
    top1, top3, avg_score = contest_instances[i].eval(model, str_period)
    result.append([contest_instances[i].bot_id, contest_instances[i].code, top1, top3, avg_score])

df = pd.DataFrame(result, columns = columns)

print df
print 'mAP:'
print df['avg_score'].mean()
