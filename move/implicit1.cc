#include <iostream>

using namespace std;

struct A
{
  A() = default;

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
