#include <iostream>

using namespace std;

template <typename T>
void
print(T t)
{
  cout << t << endl;
}

int
main()
{
  // A template argument is deduced.
  print("Hello");           // T = const char *
  print(string("World!"));  // T = string 
  print(2020);              // T = int
  print(.1);                // T = double

  // We explicitely give a template argument.
  print<int>(1.2);          // T = int
  print<double>(1);         // T = double
  print<string>("Hello!");  // T = string
}
