#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector v = {1, 2, 3};

  // The legacy way of iterating.  We can modify the elements, because
  // we're using a non-const iterator.
  for(vector<int>::iterator i = v.begin(); i != v.end(); ++i)
    cout << (*i)++ << endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a const iterator.
  // for(vector<int>::const_iterator i = v.begin(); i != v.end(); ++i)
  //   cout << (*i)++ << endl;

  // We can use the 'auto' type -- the preferred way, because it's
  // less error-prone.  We let the compiler deduce the iterator type.
  for(auto i = v.begin(); i != v.end(); ++i)
    cout << (*i)++ << endl;

  // We're using const iterators here.
  for(auto i = v.cbegin(); i != v.cend(); ++i)
    cout << *i << endl;

  // We're using const iterators here as well.
  for(auto i = begin(as_const(v)); i != end(as_const(v)); ++i)
    cout << *i << endl;
}
