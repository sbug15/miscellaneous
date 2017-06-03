// check if char string is unique

#include <iostream>

bool isUnique(char *str)
{
  bool *char_set = new bool[256];
  char *end = str;

  while(*end)
    {
      int val = *end;
      std::cout << val << std::endl;
      if (char_set[val])
        {
          std::cout << "not unique" << std::endl;
          return false;
        }

      char_set[val] = true;
      end++;
    }

  std::cout << "unique" << std::endl;
  return true;
}

int main()
{
  char *arr = "0abc9az";
  if (isUnique(arr))
    std::cout << "unique" << std::endl;

  return 0;
}
