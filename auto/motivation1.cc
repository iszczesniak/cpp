#include <deque>
#include <iostream>
#include <vector>

int
main()
{
  std::deque<std::vector<int>> d;

  // Iterating the old way: we have to explicitly declare the types.
  for(std::deque<std::vector<int>>::iterator i = d.begin();
      i != d.end(); ++i)
    for(std::vector<int>::iterator j = i->begin();
        j != i->end(); ++j);

  // Iterating the old way: we ask the compiler to deduce the types.
  for(auto i = d.begin(); i != d.end(); ++i)
    for(auto j = i->begin(); j != i->end(); ++j);

  // Iterating the new way.
  for(auto &e: d)
    for(auto &f: e);
}
