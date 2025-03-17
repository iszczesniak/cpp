#include "name.hpp"

#include <iostream>

using namespace std;

template <typename T>
struct A: name<T>
{
};

int main()
{
  const A<const char *> a1{"Hello"}, b1{"World"};
  cout << a1 << '\n' << b1 << '\n';
  cout << get_name(a1) << get_name(b1) << '\n';

  // Does not compile.
  // get_name(a1) = "Yellow";

  A<string> a2{"Hello"}, b2{"World"};
  get_name(a2) += " ";
  get_name(b2) += "!";
  cout << get_name(a2) << get_name(b2) << '\n';
}
