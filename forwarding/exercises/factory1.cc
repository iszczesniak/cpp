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

template<typename T>
auto
my_make_unique(T &&t)
{
  return std::unique_ptr<A>(new A(std::forward<T>(t)));
}

int
main()
{
  std::string a("World");
  my_make_unique(a);
  my_make_unique(std::string("Hello"));
  my_make_unique("Hello");
}
