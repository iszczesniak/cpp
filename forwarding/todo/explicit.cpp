#include <iostream>
#include <utility>

struct A
{
  A & operator=(const A &) = delete;
    
  template <typename Self>
  auto && operator=(this Self &&self, A &&src)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return std::forward<Self>(self);
  }
};

int main()
{
    A a;
    //    a = a;
    a = A();
}
