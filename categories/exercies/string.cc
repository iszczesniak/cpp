#include <string>

using namespace std;

string &operator++(string &s)
{
  return s;
}

string &operator++(string &s, int)
{
  return s;
}

int
main()
{
  string s;
  ++++s;
  ++s++;
  s++++;
}
