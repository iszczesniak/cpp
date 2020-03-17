#include <iostream>

using namespace std;

template <char* txt>
void
print()
{
  cout << txt << endl;
}

const char *txt = "Hello!";

int
main()
{
  //  print<&txt>();
}
