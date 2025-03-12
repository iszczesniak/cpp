#include <utility>

struct A
{
  int &m_r;

  A(int &r): m_r(r)
  {
  }
};

int
main()
{
  int i, j;
  A a(i), b(j);

  // These would not compile:
  // a = b;
  // a = std::move(b);
}
