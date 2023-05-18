#include <iostream>

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

  std::cout << "x = " << x << std::endl;
}
