#include <iostream>

int
main()
{
  int x = 1, y = 2;

  {
    struct F
    {
      int &x;
      int &y;

      F(int &x, int &y): x(x), y(y)
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

  std::cout << "x = " << x << ", y = " << y << std::endl;
}
