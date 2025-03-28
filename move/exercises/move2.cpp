#include <string>
#include <utility>

// This is a given.
struct A
{
};

// This is the answer to the exercise.
struct B: A
{
  std::string m_txt;

  B(B &&src): A(std::move(src)), m_txt(src.m_txt)
  {
  }

  B &operator=(B &&src)
  {
    A::operator=(std::move(src));
    m_txt = src.m_txt;
    return *this;
  }
};
