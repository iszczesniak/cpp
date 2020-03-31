#include <iostream>
#include <functional>

using namespace std;

using callable = void();

template <typename C>
void
f(C c)
{
  c();
}

// This is a functor struct.
struct callme
{
  callme()
  {
  }

  callme(const callme &)
  {
    cout << "copy-ctor\n";
  }

  void
  operator()()
  {
    cout << "Hello";
  }
};

// This function is a callable.
void
g()
{
  cout << " World";
}

int
main()
{
  // We pass a functor.
  f(callme());
 
  // We pass a function pointer.
  f(g);

  // We pass a closure.
  f([]{cout << "!\n";});

  // We can pass an std::function too.
  f(std::function<callable>(callme()));
  f<std::function<callable>>(callme());
}
