#include <string>
#include <utility>

// This structure is given, and is not an answer to the exercise.
struct A
{
  // This is stated in the instructions:
  A(A &&) = delete;
  A & operator=(A &&) = delete;

  // Now that the move members have been declared deleted, we have to
  // explicitly declare the copy members default.
  A(const A &) = default;
  A & operator=(const A &) = default;
};

// The answer to the exercise.
struct B: A
{
  std::string m_txt;
  B(B &&src): A(src), m_txt(move(src.m_txt))
  {
  }

  B & operator=(B &&src)
  {
    A::operator=(src);
    m_txt = std::move(src.m_txt);
    return *this;
  }
};
