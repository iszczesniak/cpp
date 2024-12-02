#include <iostream>

using namespace std;

struct
{
  int x = 0;

  template <typename I>
  void operator () (I i)
  {
    cout << __PRETTY_FUNCTION__ << ", "
         << "x = " << ++x << ", "
         << "i = " << i << endl;
  }
} f;

int main()
{
  f(1);
  f(.1);
  f("Hello!");
}
