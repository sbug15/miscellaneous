#include <iostream>
#include <functional>

struct Foo
{
  int num_;
  Foo(int num) :
    num_(num) {}
  void print_add(const int i) const
  {
    std::cout << this->num_ + i << std::endl;
  }
};

void print_num(const int i)
{
  std::cout << i << std::endl;
}

int main()
{
  std::function<void(int)> f_display = print_num;
  f_display(-9);

  std::function<void()> f_display_42 = []() {print_num(42);};
  f_display_42();

  std::function<void()> f_display_31337 = std::bind(print_num, 31337);
  f_display_31337();

  std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
  Foo foo(314159);
  f_add_display(foo, 1);
}
