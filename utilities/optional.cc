#include <iostream>
#include <optional>

// The assignment operator is implicityly deleted because of the
// member reference.
struct A
{
  int &m_r;

  A(int &r): m_r(r)
  {
    std::cout << "direct-initialization ctor\n";
  }

  A(const A &a): m_r(a.m_r)
  {
    std::cout << "copy-ctor\n";
  }

  A(A &&a): m_r(a.m_r)
  {
    std::cout << "move-ctor\n";
  }
};

int main()
{
  std::optional<A> oa;

  int x;
  A a(x);

  // These require the assignment operator for A.
  // oa = a;
  // oa = A(x);

  oa.emplace(a);
  oa.emplace(A(x));
}
