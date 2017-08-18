#include <iostream>
#include <vector>

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

int main()
{
  std::cout << "input N" << std::endl;
  std::cin >> N;
  std::vector<double> xs(N), ys(N);
  std::cout << "input elements" << std::endl;
  for (unsigned int i = 0; i < N; i++)
    std::cin >> xs[i] >> ys[i];

  std::cout << "input L" << std::endl;
  std::cin >> L;
  std::cout << "input elements" << std::endl;
  for (unsigned int i = 0; i < L; i++)
    {
      double x, y;
      std::cin >> x >> y;
      double best = 1e100;
      int nearest = -1;
      for (unsigned int j = 0; j < N; j++)
	{
	  double curDist = dist(x, y, xs[j], ys[j]);
	  if (curDist < best)
	    {
	      best = curDist;
	      nearest = j;
	    }
	}
      std::cout << nearest << std::endl;
    }
  return 0;
}
