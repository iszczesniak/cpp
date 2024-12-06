#include <iostream>
#include <memory>

template<typename A, typename T>
auto
my_make_unique(T &&t)
{
  return std::unique_ptr<A>(new A(std::forward<T>(t)));
}

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

int
main()
{
  std::string a("World");
  my_make_unique<A>(a);
  my_make_unique<A>(std::string("Hello"));
  my_make_unique<A>("Hello");
}
