#include <iostream>

using namespace std;

using callable = void();

// Here we accept a pointer to a callable.
void
f1(callable *c)
{
  c();
}

// I'm not sure what we accept here, but it compiles.
void
f2(callable c)
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
  f1(g);
  f2(g);

  // Here we implicitly get a pointer to the closure function.
  f1([]{cout << "World!\n";});
  f2([]{cout << "World!\n";});

  // This would not compile, because a functor does not convert to a
  // function pointer.  A functor is an object, which we
  // default-construct: callme().
  //
  // f(callme());
}
