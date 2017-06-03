#include "HashTable.h"

HashTable::HashTable(int tableLength)
{
  if (tableLength <= 0) tableLength = 13;
  array = new LinkedList[tableLength];
  length = tableLength;
}

HashTable::~HashTable()
{
  delete [] array;
}

int HashTable::hash(std::string itemKey)
{
  int value = 0;
  for (int i = 0; i < itemKey.length(); i++)
    {
      value += itemKey[i];
    }
  return (value * itemKey.length()) % length;
}

void HashTable::insertItem(Item * newItem)
{
  int index = hash(newItem->key);
  array[index].insertItem(newIterm);
}

bool HashTable::removeItem(std::string itemKey)
{
  int index = hash(itemKey);
  array[index].removeItem(itemKey);
}

Item * HashTable::getItemByKey(std::string itemKey)
{
  int index = hash(itemKey);
  return array[index].getItem(itemKey);
}
