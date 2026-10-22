#include <iostream>

using namespace std;

struct X
{
  X() = default;
  X(const X &source)
  {
    cout << "Copying from " << &source << " to " << this << '\n';
  }
};

X named()
{
  X x;
  return x;
}

X unnamed()
{
  return X();
}

int main()
{
  X xn = named();
  // X xu1 = unnamed();
  // X xu2 = X();
}
