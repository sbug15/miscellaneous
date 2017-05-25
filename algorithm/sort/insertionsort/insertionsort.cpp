#include <iostream>
#include <chrono>
#include <vector>

int binarysearch(int a[], int item, int left, int right)
{
  while (right >= left)
    {
      int mid = (right + left) / 2;
      if (item == a[mid])
	return mid;
      else if (item > a[mid])
	return binarysearch(a, item, mid + 1, right);
      else
	return binarysearch(a, item, left, mid - 1);
    }
  
  return -1;
}

int binarysearch2(int a[], int item, int left, int right)
{
  while (right >= left)
    {
      int mid = (right + left) / 2;
      if (item == a[mid])
	return (mid + 1);
      else if (item > a[mid])
	return binarysearch2(a, item, mid + 1, right);
      else
	return binarysearch2(a, item, left, mid - 1);
    }

  return (item > a[left]) ? left + 1 : left;
}

void insertionsort(int a[],int n)
{
  int key, i, j;

  for (i = 1; i < n; i++)
    {
      key = a[i];
      j = i - 1;
      while (j >= 0 && a[j] > key)
	{
	  a[j+1] = a[j];
	  j--;
	}

      a[j+1] = key;

    }
}

void insertion_binary_sort(int a[], int n)
{
  int key, i, j;

  for (i = 1; i < n; i++)
    {
      key = a[i];
      j = i - 1;

      int position = binarysearch2(a, key, 0, j);

      while (j >= position)
	{
	  a[j + 1] = a[j];
	  j--;
	}
      a[j + 1] = key;
    }
}

void printArr(int a[], int n)
{
  for (int i = 0; i < n; i++)
    {
      std::cout << a[i] << std::endl;
    }
}

int main()
{
  const int N = 1000*1000;
  std::vector<int> v1, v2;
  
  int a[] = {12, 11, 13, 5, 6};
  int n = sizeof(a) / sizeof(a[0]);

  int b[n];
  std::copy(a, a + n, b);

  insertionsort(a, n);
  printArr(a, n);
  std::cout << std::endl;
  insertion_binary_sort(b, n);
  printArr(b, n);  
  std::cout << std::endl;

  int find1 = binarysearch(a, 15, 0, n);
  int find2 = binarysearch(a, 12, 0, n);
  
  std::cout << find1 << std::endl;
  std::cout << find2 << std::endl;  

  return 0;
}
