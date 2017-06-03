// reverse string

#include <iostream>
#include <string>

// void reverse(char *str)
// {
//   char *end = str;
//   char tmp;

//   if (str)
//     {
//       while(*end)
//         ++end;

//       --end;

//       while(str < end)
//         {
//           tmp = *str;
//           *str++ = *end;
//           *end-- = tmp;
//         }
//     }
// }

// void reverseStr(std::string str)
// {
//   int len = str.length();
//   int i = 0;
//   int j = len - 1;
//   std::string tmp;

//   while (i < j)
//     {
//       tmp = str[i];
//       str[i] = str[j];
//       str[j] = tmp;
//       i++;
//       j--;
//     }
// }

  int main()
{
  char *data = "abcxyz123";
  std::string _str(data);
  // std::cout << _str << std::endl;
  return 0;
}
