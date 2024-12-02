#include <iostream>

using namespace std;

int main()
{
  auto c = [x = 0](auto i) mutable
           {
             cout << __PRETTY_FUNCTION__ << ", "
                  << "x = " << ++x << ", "
                  << "i = " << i << endl;
           };

  c(1);
  c(.1);
  c("Hello!");
}
