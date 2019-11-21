#include <iostream>

using namespace std;

struct A
{
  A() = default;

  A(const A &source)
  {
    cout << "copy ctor\n";
  }

  A(A &&t)
  {
    cout << "move ctor\n";
  }

};
  
A foo(A a)
{
  return a;
}

int
main()
{
  foo(A());
}
