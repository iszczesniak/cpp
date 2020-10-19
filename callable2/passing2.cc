#include <iostream>

using namespace std;

// This is a functor struct.
struct callme
{
  void
  operator()()
  {
    cout << "Hello World!\n";
  }
};

void
f(callme c)
{
  c();
}

// This function is a callable.
void
g()
{
  cout << "Hello ";
}

int
main()
{
  // We pass a functor.
  f(callme());
 
  // We can't pass a function pointer.
  //
  // f(g);

  // We can't pass a closure.
  //
  // f([]{cout << "World!\n";});
}
