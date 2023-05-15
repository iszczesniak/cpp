#include <iostream>

using namespace std;

using callable = void();

// Here we accept a pointer to a callable.
void
f1(callable *c)
{
  c();
}

// The parameter type is the same as above.  It's a pointer to a
// function.  We could say that the function type decays into the
// function pointer type, because a function cannot be passed by
// value.

// void
// f1(callable c)
// {
//   c();
// }

void
f2(callable &c)
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
  // We cannot implicitly get a pointer to a closure function if the
  // lambda captured some data (these would be stored as member
  // fields, and we would need a pointer to the closure).
  int x;
  //  f1([x]{cout << "World!\n";});

  // Doesn't work for the function reference type.
  // f2([]{cout << "World!\n";});

  // This would not compile, because a functor does not convert to a
  // function pointer.  A functor is an object, which we
  // default-construct: callme().
  //
  // f1(callme());
  // f2(callme());
}
