#include <initializer_list>
#include <iostream>

template<typename T>
void foo(T &)
{
  cout << "Overload #1: non-const lvalue reference\n";
  cout << __PRETTY_FUNCTION__ << endl;
}

template<typename T>
void foo(const T &)
{
  cout << "Overload #1: const reference\n";
  cout << __PRETTY_FUNCTION__ << endl;
}

template<typename T>
void foo(const T &)
{
  cout << "Overload #1: const reference\n";
  cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
  int a[] = {1, 2, 3};
  foo(a); // Overload #1
  const int b[] = {1, 2, 3};
  foo(b); // Overload #2
  
  foo({1, 2, 3});
}
