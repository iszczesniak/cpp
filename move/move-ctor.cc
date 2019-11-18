#include <string>
#include <utility>

struct A {};

struct B: A
{
  std::string m_s;

  B(B &&b): A(std::move(b)), m_s(std::move(b.m_s))
  {
  }
};
