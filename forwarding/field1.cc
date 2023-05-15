#include <utility>

using namespace std;

template <typename T>
struct A
{
  T &&m_ref;

  A(T &&ref): m_ref(ref)
  {
  }

  T &&
  operator()
  {
    return forward<T>(m_ref);
  }
};

int
main()
{
  int x;
  A a(x), b(1);
}
