#ifndef A_HPP
#define A_HPP

#include <string>

struct A
{
  std::string m_name;

  A(const std::string &name);
  ~A();
  A(const A &a);
  void hello() const;
};

#endif // A_HPP
