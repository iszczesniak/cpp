#include <iostream>

using namespace std;

struct fun
{
  int x = 0;

  template <typename I>
  void operator () (I i)
  {
    cout << __PRETTY_FUNCTION__ << ", "
         << "x = " << ++x << ", "
         << "i = " << i << endl;
  }
};

int main()
{
  fun c;
  c(1);
  c(.1);
  c("Hello!");
}
