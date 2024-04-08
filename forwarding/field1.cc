#include <iostream>
#include <utility>

template <typename T>
struct A
{
  T &&m_ref;

  A(T &&ref): m_ref(std::forward<T>(ref))
  {
  }

  T &&
  operator*()
  {
    return std::forward<T>(m_ref);
  }
};

// A deduction guide.
template<typename T>
A(T &&) -> A<T>;

void foo(int &i)
{
  std::cout << "lvalue: " << i << std::endl;
}

void foo(int &&i)
{
  std::cout << "rvalue: " << i << std::endl;
}

int
main()
{
  int x = 10;

  foo(*A<int &>(x));
  foo(*A<int>(1));

  // To have the arguments deduced as for a forwarding reference, we
  // had to define a deduction guide.
  foo(*A(x));
  foo(*A(2));
}
