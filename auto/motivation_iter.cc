#include <deque>
#include <iostream>
#include <vector>

int
main()
{
  std::deque<std::vector<int>> d;

  // We iterate using iterators with an explicitely declared type.
  for(std::deque<std::vector<int>>::iterator i = d.begin();
      i != d.end(); ++i)
    for(std::vector<int>::iterator j = i->begin();
        j != i->end(); ++j);

  // We iterate using iterators, but let the compiler deduce the type.
  for(auto i = d.begin(); i != d.end(); ++i)
    for(auto j = i->begin(); j != i->end(); ++j);
}
