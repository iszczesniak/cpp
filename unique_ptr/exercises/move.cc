#include <iostream>
#include <memory>
#include <utility>

struct A
{
  A()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  A(const A &)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  ~A()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

struct B
{
  std::unique_ptr<A> m_up;

  B(): m_up(std::make_unique<A>())
  {
  }

  B(const B &b): m_up(std::make_unique<A>(*b.m_up))
  {
  }

  B(B &&b): m_up(std::move(b.m_up))
  {
  }

  B &operator=(const B &b)
  {
    m_up = std::make_unique<A>(*b.m_up);
    return *this;
  }

  B &operator=(B &&b)
  {
    m_up = std::move(b.m_up);
    return *this;
  }
};

int main()
{
  std::cout << "Testing the copy-ctor.\n";
  {
    B b1;
    B b2(b1);
  }

  std::cout << "Testing the move-ctor.\n";
  {
    B b1;
    B b2(std::move(b1));
  }

  std::cout << "Testing the copy-assignment.\n";
  {
    B b1, b2;
    b2 = b1;
  }

  std::cout << "Testing the move-assignment.\n";
  {
    B b1, b2;
    b2 = std::move(b1);
  }
}
