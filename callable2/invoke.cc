#include <functional>
#include <iostream>

using namespace std;

int
foo(int x)
{
  cout << "foo: ";
  return ++x;
}

int
main()
{
  cout << foo(1) << endl;
  cout << invoke(foo, 1) << endl;

  auto lambda = [](int x){cout << "lambda: "; return ++x;};
  cout << lambda(1) << endl;
  cout << invoke(lambda, 1) << endl;
}
