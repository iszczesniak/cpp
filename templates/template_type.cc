#include <forward_list>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <template <typename> typename C, typename T>
void
foo(T t)
{
  cout << __PRETTY_FUNCTION__ << endl;
  C<T> c;
  c.push_back(t);
}

// Type my_list has only one template parameter.  We pass only one
// parameter to std::list, and use the default values for whatever
// remaining parameters there are for std::list.
template <typename T>
using my_list = std::list<T>;

// using my_vector
template <typename T>
using my_vector = std::vector<T>;

// using my_forward_list
template <typename T>
using my_forward_list = std::forward_list<T>;

int
main()
{
  foo<my_list>(1);
  foo<my_list>("Hello");
  foo<my_vector>(.1);
  foo<my_vector>("World");

  // This is cool: pointer to an instantiated function template.  We
  // instantiate the function right here, because we point to it.
  void (*fp)(double) = foo<my_list, double>;
  fp(1);
}
