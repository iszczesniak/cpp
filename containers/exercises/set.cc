#include <cassert>
#include <iostream>
#include <set>
#include <string>

int
main()
{
  std::set<std::pair<int, std::string>> s;

  s.emplace(1, "Joe");

  auto *p1 = &(s.begin()->second);
  
  auto nh = s.extract(s.begin());
  ++nh.value().first;
  s.insert(std::move(nh));

  auto *p2 = &(s.begin()->second);

  assert(p1 == p2);
    
  std::cout << s.begin()->first << std::endl;
}
