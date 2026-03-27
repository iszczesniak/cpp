#ifndef A_HPP
#define A_HPP

#include <string>

struct A
{
  std::string m_name;

  // For a direct-initiation with a string.
  A(const std::string &);
  // Copy and move constructors.
  A(const A &);
  A(A &&);

  void hello() const;
  ~A();
};

#endif // A_HPP
