#include <concepts>
#include <iostream>

using namespace std;

void
print(const auto &x)
{
  cout << "Print: " << x << endl;
}

void
print(const integral auto &x)
{
  cout << "Print for integrals: " << x << endl;
}

int
main()
{
  print(1);
  print(.1);
  print("Hello World!");
}
