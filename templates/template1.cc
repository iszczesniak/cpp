#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <template <typename...> typename C, typename T>
void
foo(T t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  C<T> c;
  c.push_back(t);
}

int
main()
{
  foo<list>(1);
  foo<list>("Hello");
  foo<vector>(.1);
  foo<vector>("World");

  // This is cool: pointer to an instantiated function template.  We
  // instantiate the function right here, because we point to it.
  void (*fp)(double) = foo<list, double>;
  fp(1);
}
