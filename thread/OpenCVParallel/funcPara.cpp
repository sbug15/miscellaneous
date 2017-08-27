#include <stdio.h>
#include <functional>

double cm_to_inches(double cm) {
  return cm / 2.54;
}

static double derivative(const std::function<double(double)> &f, double x0, double eps) {
  double eps2 = eps / 2;
  double lo = x0 - eps2;
  double hi = x0 + eps2;
  return (f(hi) - f(lo)) / eps;
}

static double f(double x) {
  return x * x;
}

int main(void) {
  double (*func1)(double) = cm_to_inches;
  printf("%f\n", func1(15.0));

  double x = 1;
  printf("%f\n", derivative(f, x, 1e-5));
  printf("d/dx(x ^ 2) [@ x = %d] = %f\n", int(x), derivative(f, x, 1e-5));

  return 0;
}
