#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct A
{
  A(string &&t1, string &t2)
  {
    cout << t1 << t2 << endl;
  }
};

struct B: A
{
  template <typename... P>
  B(P &&... p): A(std::forward<P>(p)...)
  {
  }
};

int main()
{
  string l("World!");
  // B(string("Hello "), string("World!"));
  B(string("Hello "), l);
  // B(l, string("World!"));
  // B(l, l);
}
