#include <iostream>

using namespace std;

int main()
{
  int x = 1;
  char t[7] = "Hello!";
  t[0] = 'Y';

  cout << &x << endl;
  cout << &t << endl;

  *((char *)"Hello!") = 'Y';
}
