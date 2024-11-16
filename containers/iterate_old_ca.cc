#include <iostream>
#include <iterator>

using namespace std;

int main()
{
  int a[] = {1, 2, 3};

  // The old way of iterating.  We can modify the elements, because
  // we're using a pointer to non-const data.
  for(int *i = begin(a); i != end(a); ++i)
    cout << (*i)++ << endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a pointer to the const data.
  // for(const int *i = begin(a); i != end(a); ++i)
  //   cout << (*i)++ << endl;
  
  // We can use the 'auto' type -- the preferred way, because it's
  // less error-prone.  We let the compiler deduce the iterator type.
  for(auto i = begin(a); i != end(a); ++i)
    cout << (*i)++ << endl;

  // We're using a const iterator (a pointer to const data) here.
  for(auto i = cbegin(a); i != cend(a); ++i)
    cout << *i << endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a const iterator.
  // for(auto i = cbegin(a); i != cend(v); ++i)
  //   cout << (*i)++ << endl;

  // We're using const iterators here.
  for(auto i = begin(as_const(a)); i != end(as_const(a)); ++i)
    cout << *i << endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a const iterator.
  // for(auto i = begin(as_const(a)); i != end(as_const(a)); ++i)
  //   cout << (*i)++ << endl;
}
