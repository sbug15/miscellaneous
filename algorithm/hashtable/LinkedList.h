#pragma once

#include <iostream>
#include <string>

struct Item
{

  std::string key;
  Item *next;

};

class LinkedList
{
 private:
  Item *head;
  int length;

 public:
  LinkedList();
  ~LinkedList();

  void insertItem(Item *newItem);
  bool removeItem(std::string itemKey);
  Item * getItem(std::string itemKey);

  void printList();
  int getLength();

};
