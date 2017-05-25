#include <iostream>

bool dfs(int a[], int n, int i, int sum, int k)
{
  if (i == n) return (sum == k);

  if (dfs(a, n, i + 1, sum, k)) return true;

  if (dfs(a, n, i + 1, sum + a[i], k)) return true;

  return false;
}

int main()
{
  int a[] = {1, 2, 4, 7};
  int n = 4;
  int k = 15;
  
  if (dfs(a, n, 0, 0, k))
    std::cout << "Yes" << std::endl;
  else
    std::cout << "No" << std::endl;

  return 0;
}
