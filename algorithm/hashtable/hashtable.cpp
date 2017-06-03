#include <iostream>
#include <string>


int hash(string key)
{
  int value = 0;
  for (int i = 0, i < key.length(); i++)
    value += key[i];
  return value % tableLength;
}
