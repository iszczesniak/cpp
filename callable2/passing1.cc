#include <iostream>

using namespace std;

// A function pointer type.
using callable = void();

// The above type is the same as this one:
// using callable = void (*)();

void
f(callable c)
{
  c();
}

void
g()
{
  cout << "Hello ";
}

struct callme
{
  void
  operator()()
  {
  }
};

int
main()
{
  f(g);
  f([]{cout << "World!\n";});

  // This will not compile, because a functor does not convert to a
  // function pointer.
  //
  // f(callme());
}
