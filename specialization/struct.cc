#include <iostream>

// Definition of a primary template.
template <typename T>
struct A
{
  void
  foo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

// A complete specialization.
template<>
struct A<double>: std::pair<double, double>
{
  void
  goo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }  
};

int
main()
{
  A<int> i;
  i.foo();
  A<float>().foo();

  // Error: "foo" is in the primary template, which we've overwritten.
  // A<double>().foo();

  // But we can call "goo" alright.
  A<double>().goo();
}
