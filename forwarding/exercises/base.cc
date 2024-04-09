#include <iostream>
#include <memory>

struct A
{
  A(std::string &)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  A(std::string &&)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

struct B: A
{
  template<typename T>
  B(T &&t): A(std::forward<T>(t))
  {
  }
};

int
main()
{
  std::string a("World");
  B{a};
  B("Hello");
}
