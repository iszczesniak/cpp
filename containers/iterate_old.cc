#include <iostream>
#include <vector>
#include <utility>

int main()
{
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);  

  // The legacy way of iterating.
  for(std::vector<int>::iterator i = v.begin();
      i != v.end(); ++i)
    std::cout << *i << std::endl;

  // We can modify the elements, because we're using a non-const
  // iterator.
  for(std::vector<int>::iterator i = v.begin();
      i != v.end(); ++i)
    std::cout << (*i)++ << std::endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a const iterator.

  // for(std::vector<int>::const_iterator i = v.begin();
  //     i != v.end(); ++i)
  //   std::cout << (*i)++ << std::endl;

  // We can use the 'auto' type -- the preferred way, because it's
  // less error-prone.  We let the compiler deduce the iterator type.
  for(auto i = v.begin(); i != v.end(); ++i)
    std::cout << (*i)++ << std::endl;

  // We're using const iterators here.
  for(auto i = v.cbegin(); i != v.cend(); ++i)
    std::cout << *i << std::endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a const iterator.

  // for(auto i = v.cbegin(); i != v.cend(); ++i)
  //   std::cout << (*i)++ << std::endl;

  // We're using const iterators here.
  for(auto i = std::as_const(v).begin();
      i != std::as_const(v).end(); ++i)
    std::cout << *i << std::endl;

  // That would not compile, because we're trying to modifying the
  // elements that we access through a const iterator.

  // for(auto i = std::as_const(v).begin();
  //     i != std::as_const(v).end(); ++i)
  //   std::cout << (*i)++ << std::endl;
}
