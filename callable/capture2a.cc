#include <iostream>

using namespace std;

int
main()
{
  int x = 1;

  {
    struct
    {
      void
      operator()(int &x) const
      {
        x = 10;
      }
    } f;
    f(x);
  }

  cout << "x = " << x << endl;
}
