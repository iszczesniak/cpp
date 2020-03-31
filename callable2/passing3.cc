#include <iostream>
#include <functional>

using namespace std;

using callable = void();

void
f(std::function<callable> c)
{
  c();
}

// This is a functor struct.
struct callme
{
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
}
