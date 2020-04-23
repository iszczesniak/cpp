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
  callme() = default;

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

  function<callable> c = callme();
  f(c);
  c = g;
  f(c);
  c = []{cout << "!\n";};
  f(c);    
}
