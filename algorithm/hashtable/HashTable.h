#pragma once

#include "LinkedList.h"

class HashTable
{
 private:
  LinkedList *array;
  int length;

  int hash(std::string itemKey);

 public:
  HashTable(int tableLength = 13);
  ~HashTable();

  void insertItem(Item * newItem);
  bool removeItem(std::string itemKey);
  Item * getItemByKey(std::string itemKey);
  void printTable();
  void printHistogram();
  int getLength();
  int getNumberofItems();
}
