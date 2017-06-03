#include "LinkedList.h"

LinkedList::LinkedList()
{
  head = new Item;
  head->next = NULL;
  length = 0;
}

LinkedList::~LinkedList()
{
  Item *p = head;
  Item *q = head;

  while(q)
    {
      p = q;
      q = p->next;
      if (q) delete p;
    }
}

void LinkedList::insertItem(Item *newItem)
{
  if (!head->next)
    {
      head->next = newItem;
      newItem->next = NULL;
      length++;
      return;
    }

  Item *p = head;
  Item *q = head;

  while(q)
    {
      p = q;
      q = p->next;
    }
  p->next = newItem;
  newItem->next = NULL;
  length++;
}

bool LinkedList::removeItem(std::string itemKey)
{
  if (!head->next) return false;
  Item *p = head;
  Item *q = head;

  while(q)
    {
      if (q->key == itemKey)
        {
          p->next = q->next;
          delete q;
          length--;
          return true;
        }
      p = q;
      q = p->next;
    }
  return false;
}

Item * LinkedList::getItem(std::string itemKey)
{
  Item * p = head;
  Item * q = head;
  while(q)
    {
      p = q;
      if (p != head && p->key == itemKey)
        return p;
      q = p->next;
    }
  return NULL;
}

void LinkedList::printList()
{
  if (length == 0)
    {
      std::cout << "no keys\n";
      return;
    }

  Item *p = head;
  Item *q = head;
  while(q)
    {
      p = q;
      if (p != head)
        {
          std::cout << p->key << std::endl:
        }
      q = p->next;
    }
}

int LinkedList::getLength()
{
  return length;
}
