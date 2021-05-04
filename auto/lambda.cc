#include <iostream>

using namespace std;

int main()
{
  auto c = [](auto i){cout << i << endl;};

  c(1);
  c(.1);
  c("Hello!");
}
