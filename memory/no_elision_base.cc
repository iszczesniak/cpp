#include "A.hpp"
#include <string>

struct B: A
{
  B(const std::string &name): A(name)
  {
  }       
};

A named()
{
  B b("named");
  return b;
}

A unnamed()
{
  return B("unnamed");
}

int main()
{
  named();
  unnamed();
}
