#include <iostream>
#include <algorithm>

static inline bool isTriangle(int a, int b, int c)
{
  int sum = a + b + c;
  int maxEdge = std::max(a, std::max(b, c));
  int sum2Edge = sum - maxEdge;
  if (maxEdge < sum2Edge)
    return true;
  else
    return false;
}

int maxTriangle(const int* a, int n)
{
  int result = 0;
  std::cout << n << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++)
	{
	  if (isTriangle(a[i], a[j], a[k]))
	    {
	      result = std::max(result, a[i] + a[j] + a[k]);
	    }
	}
    }
  }
  return result;
}
		       
int main()
{
  int a[] = {2, 3, 4, 5, 10};
  std::cout << maxTriangle(a, 5) << std::endl;

  return 0;
}
