#include <iostream>

using namespace std;

using callable = void();

void
f(callable c)
{
  c();
}

// This function is a callable.
void
g()
{
  cout << "Hello ";
}

// This is a functor struct.
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
  // Here we pass a regular pointer to a function.
  f(g);

  // Here we implicitly get a pointer to the closure function.
  f([]{cout << "World!\n";});

  // This would not compile, because a functor does not convert to a
  // function pointer.  A functor is an object, which we
  // default-construct: callme().
  //
  // f(callme());
}
