#ifndef A_HPP
#define A_HPP

#include <string>

struct A
{
  std::string m_name;

  // For a direct-initialization with a string.
  A(const std::string &);
  // The copy constructor.
  A(const A &);

  void hello() const;
  ~A();
};

#endif // A_HPP
