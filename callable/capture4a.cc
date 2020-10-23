#include <iostream>

using namespace std;

int
main()
{
  int x = 1, y = 2;

  {
    struct F
    {
      int x;
      int y;

      F(int x, int y): x(x), y(y)
      {
      }

      void
      operator()()
      {
        x = 10;
        y = 20;
      }
    };

    F f(x, y);
    f();
  }

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
}
