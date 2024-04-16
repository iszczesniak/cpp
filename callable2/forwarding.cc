#include <iostream>
#include <utility>

using namespace std;

template <typename C>
void f(C &&c)
{
  cout << __PRETTY_FUNCTION__ << '\n';
  // Here we perfectly forward (or rather call) the callable.
  std::forward<C>(c)();
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
  // Because function f accepts a callable by a forwarding reference,
  // we can pass to it by reference both a function and a closure.

  // Expression g is an lvalue.
  f(g); // C = void (&)()
  // The lambda expression in an rvalue.
  f([]{});

  // Forwarding the callable in function f is needed here.
  callme c;
  // Function f should call the passed callable as an lvalue.
  f(c);
  // Function f should call the passed callable as an rvalue.
  f(callme());
}
