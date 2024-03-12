#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <template <typename...> typename C, typename T>
void
foo(const C<T> &c)
{
  cout << __PRETTY_FUNCTION__ << endl;
}

int
main()
{
    foo(set{"Hello", "World"});
    foo(vector{1, 2, 3});
}
