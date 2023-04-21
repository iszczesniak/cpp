#include <iostream>

using namespace std;

struct
{
  void operator () (auto &&f, auto &&a)
  {
    cout << __PRETTY_FUNCTION__ << endl;
    forward<decltype(f)>(f)(forward<decltype(a)>(a));
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
  // The lambda is passed by the rvalue reference.
  c([](int x){}, 1); // 1 is an rvalue.
  // The function is passed by the lvalue reference.
  c(roo, 1);

  int a;
  c([](int x){}, a); // a is an lvaule.
  c(loo, a);
}
