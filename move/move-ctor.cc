#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  // The implementation of the move constructor has to use the
  // std::move function to move the base object of class A of object
  // b, and the string of object b, otherwise they would be copied.
  B(B &&b): A(std::move(b)), m_s(std::move(b.m_s))
  {
  }
};
