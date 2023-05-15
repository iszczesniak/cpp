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

int
main()
{
  int x;
  A<int &> a(x);
  A<int> b(1);
}
