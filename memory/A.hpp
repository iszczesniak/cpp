#ifndef A_HPP
#define A_HPP

#include <string>

struct A
{
  std::string m_name;

  // For direct-initiation with a string.
  A(const std::string &name);
  ~A();

  // Copy and move constructors.
  A(const A &a);
  A(A &&a);

  void hello() const;
};

#endif // A_HPP
