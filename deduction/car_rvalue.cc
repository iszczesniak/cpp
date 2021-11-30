#include <initializer_list>
#include <iostream>

using namespace std;

template<typename T>
void foo(T &)
{
  cout << "Overload #1: non-const lvalue reference\n";
  cout << __PRETTY_FUNCTION__ << "\n\n";
}

template<typename T>
void foo(const T &)
{
  cout << "Overload #2: const reference\n";
  cout << __PRETTY_FUNCTION__ << "\n\n";
}

template<typename T>
void foo(const initializer_list<T> &)
{
  cout << "Overload #3: const initializer_list\n";
  cout << __PRETTY_FUNCTION__ << "\n\n";
}

int main()
{
  int a[] = {1, 2, 3};
  foo(a); // Overload #1

  const int b[] = {1, 2, 3};
  foo(b); // Overload #2

  foo({1, 2, 3}); // Overload #3

  foo((int[3]){1, 2, 3}); // Overload #2
}
