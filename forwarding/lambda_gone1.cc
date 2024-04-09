#include <iostream>

using namespace std;

struct
{
  template <typename F, typename A>
  void operator () (F &&f, A &&a)
  {
    cout << __PRETTY_FUNCTION__ << endl;
    forward<F>(f)(forward<A>(a));
  }
} c;

void loo(int &)
{
}

void roo(int &&)
{
}

int main()
{
  // The lambda is accepted by the rvalue reference.
  c([](int x){}, 1); // 1 is an rvalue.
  // The function is accepted by the lvalue reference.
  c(roo, 1);

  int a;
  c([](int x){}, a); // a is an lvaule.
  c(loo, a);
}
