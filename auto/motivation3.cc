#include <iostream>
#include <vector>

using namespace std;

int
main()
{
  vector<int> v = {1, 2, 3};
  auto size = v.size();

  // We can iterate backwards with an index.
  for(auto i = v.size(); i--;)
    cout << v[i] << endl;

  // We can iterate forwards with an index.  We can ask the comiler to
  // deduce the type from 0, but we cannot be sure it will be the same
  // as vector<int>::size_type.
  for(auto i = 0; i < v.size(); ++i)
    cout << v[i] << endl;

  // This is correct, but without type deduction.
  for(vector<int>::size_type i = 0; i < v.size(); ++i)
    cout << v[i] << endl;

  // We ask the compiler to deduce the type from an expression.  This
  // is correct, and the most general, but somehow I don't like it.
  for(decltype(v.size()) i = 0; i < v.size(); ++i)
    cout << v[i] << endl;
}
