#include <iostream>
#include <type_traits>

using namespace std;

struct A
{
  void
  hello() const
  {
    cout << "Hello World!\n";
  }
};

struct B: A
{
};

// Static polymorphism.
template <typename T> requires std::is_base_of_v<A, T>
void
sp(const T &t)
{
  t.hello();
}

// Dynamic polymorphism.
void
dp(const A &a)
{
  a.hello();
}

int
main()
{
  B b;
  sp(b);
  dp(b);
}
