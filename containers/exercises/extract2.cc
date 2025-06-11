#include <iostream>
#include <list>
#include <set>
#include <string>

int main()
{
  std::set<std::string> s;
  std::list<std::string> l;

  s.emplace("Hello World!");
  s.insert(std::move(s.extract(s.begin()).value()));
}
