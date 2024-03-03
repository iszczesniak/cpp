#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// We have to define the function as non-member, because we cannot
// modify type std::string.
string
operator++(string &s, int)
{
  string tmp = s;
  next_permutation(s.begin(), s.end());
  return tmp;
}

int main()
{
  cout << "Permutations for abc:" << endl;
  for(string i = "abc"; i++ != "cba";)
    cout << i << endl;
}
