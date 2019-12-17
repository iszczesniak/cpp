#include <utility>

struct A
{
  int &m_i;

  A(int &i): m_i(i)
  {
  }
};

int
main()
{
  int i;
  A a(i), b(i);

  // These would not compile:
  // a = b;
  // a = std::move(b);
}
