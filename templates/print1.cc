#include <iostream>
#include <string>

using namespace std;

template <typename T>
void
print(const T &t)
{
  cout << t << endl;
}

int
main()
{
  print(1);
  print(0.5);
  print("Hello!");
  print(string("Hello!"));
}
