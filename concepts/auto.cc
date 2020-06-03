#include <iostream>

using namespace std;

void
print(auto x)
{
  cout << "Print: " << x << endl;
}
  
int
main()
{
  print(1);
  print(.1);
  print("Hello World!");
}
