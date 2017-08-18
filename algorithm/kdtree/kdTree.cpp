#include <iostream>
#include <vector>
#include <algorithm>

// #define MANUAL_INPUT

int N, L;

inline double dist
(
 double x1,
 double y1,
 double x2,
 double y2
)
{
  return (x1- x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

inline double sq(double x)
{
  return x * x;
}

struct data
{
  int index;
  std::vector<double> v;
  data(int _d) : v(_d) {}
  data() {}
};

inline double dist(const data &x, const data& y)
{
  double ret = 0;
  for (unsigned int i = 0; i < x.v.size(); i++)
    ret += (x.v[i] - y.v[i]) * (x.v[i] - y.v[i]);
  return ret;
}

struct Node
{
  data val;
  Node *left;
  Node *right;
};

class axisSorter
{
  int k;

public:
  axisSorter(int _k) : k(_k) {}

  double operator()(const data& a, const data& b)
  {
    return a.v[k] < b.v[k];
  }
};

Node *makeKDTree(std::vector<data> &xs, int l, int r, int depth)
{
  if (l >= r)
    return NULL;

  sort(xs.begin() + l, xs.begin() + r, axisSorter(depth % xs[0].v.size()));

  int mid = (l + r) >> 1;

  Node *node = new Node();
  node->val = xs[mid];
  node->left = makeKDTree(xs, l, mid, depth + 1);
  node->right = makeKDTree(xs, mid + 1, r, depth + 1);

  return node;
}

data query(data &a, Node *node, int depth)
{
  int k = depth % a.v.size();
  if ((node->left != NULL && a.v[k] < node->val.v[k]) ||
      (node->left != NULL && node->right == NULL))
    {
      data d = query(a, node->left, depth + 1);
      if (dist(node->val, a) < dist(d, a))
	d = node->val;
      if (node->right != NULL &&
	  (sq(a.v[k] - node->val.v[k]) < dist(d, a)))
	{
	  data d2 = query(a, node->right, depth + 1);
	  if (dist(d2, a) < dist(d, a))
	    d = d2;
	}
      return d;
    }

  else if (node->right != NULL)
    {
      data d = query(a, node->right, depth + 1);
      if (dist(node->val, a) < dist(d, a))
	d = node->val;
      if (node->left != NULL &&
	  (sq(a.v[k] - node->val.v[k]) < dist(d, a)))
	{
	  data d2 = query(a, node->left, depth + 1);
	  if (dist(d2, a) <  dist(d, a))
	    d = d2;
	}
      return d;
    }
  else
    return node->val;
}

int main()
{

#ifdef MANUAL_INPUT  
  std::cout << "input N" << std::endl;
  std::cin >> N;
  std::vector<data(2)> xs(N);

  std::cout << "input elements" << std::endl;
  for (unsigned int i = 0; i < N; i++)
    {
      xs[i].index = i;
      std::cin >> xs[i].v[0] >> xs[i].v[1];
    }
#else
  N = 5;
  std::vector<data> xs(5, data(2));
  double inputPoints[][2] = {{2, 3}, {9, 4}, {5 ,6}, {7, 8}, {10, 11}};
  for (unsigned int i = 0; i < N; i++)
    {
      xs[i].index = i;
      xs[i].v[0] = inputPoints[i][0];
      xs[i].v[1] = inputPoints[i][1];
    }
#endif
  
  Node *root = makeKDTree(xs, 0, N, 0);

#ifdef MANUAL_INPUT
  std::cout << "input L" << std::endl;
  std::cin >> L;
  std::cout << "input elements" << std::endl;
  for (unsigned int i = 0; i < L; i++)
    {
      data a(2);
      std::cin >> a.v[0] >> a.v[1];

      data nearest = query(a, root, 0);
      std::cout << nearest.index << std::endl;
    }
#else
  L = 2;
  double queryPoints[][2] = {{5, 6}, {2, 4}};
  for (unsigned int i = 0; i < L; i++)
    {
      data a(2);
      a.v[0] = queryPoints[i][0];
      a.v[1] = queryPoints[i][1];
      data nearest = query(a, root, 0);
      std::cout << nearest.index << std::endl;
    }

#endif
  
  return 0;
}
