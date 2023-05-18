#include <iostream>

struct functor_type
{
  int m_n;

  functor_type(int n): m_n(n)
  {
  }

  void operator()() const
  {
    for(int i = 0; i < m_n; ++i)
      std::cout << "Hello World from a functor!\n";
  }
};

int
main()
{
  functor_type f(10);
  f();
}
