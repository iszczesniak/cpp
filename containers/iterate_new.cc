#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
  vector v = {1, 2, 3};

  // We can modify the elements, because we use them through a
  // non-const reference of type: auto &
  for(auto &e: v)
    cout << ++e << endl;

  // Here we iterate with a const reference.
  for(const auto &e: v)
    cout << e << endl;

  // This would not compile, because we refer to the elements through
  // a const reference: const auto &

  // for(const auto &e: v)
  //   cout << ++e << endl;

  // We could also iterate through a non-const container and reference
  // the elements with a const reference, becasue we refer to the
  // non-const container with a const reference.
  for(auto &e: as_const(v))
    cout << e << endl;
}
