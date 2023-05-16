#include <iostream>
#include <utility>

using namespace std;

template <typename C>
void f(C &&c)
{
  cout << __PRETTY_FUNCTION__ << '\n';
  forward<C>(c)();
}

void g()
{
}

struct callme
{
  void operator()() &
  {
    cout << "lvalue of callme\n";
  }

  void operator()() &&
  {
    cout << "rvalue of callme\n";
  }
};

int main()
{
  // Expression g is an lvalue.
  f(g); // C = void (&)()
  // The lambda expression in an rvalue.
  f([]{});

  callme c;
  f(c);
  f(callme());
}
