#include <iostream>
#include <memory>

template<typename A>
auto
my_make_unique(auto &&... t)
{
  return std::unique_ptr<A>(new A(std::forward<decltype(t)>(t)...));
}

struct A
{
  A(std::string &, double)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  A(std::string &&, int)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  std::string a("World");
  my_make_unique<A>(a, 1);
  my_make_unique<A>(std::string("Hello"), 1.1);
  my_make_unique<A>("Hello", 1);
}
