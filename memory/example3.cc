#include <string>

A g()
{
  return A("Hello World!");
}

A f(A a)
{
  return a;
}

int main()
{
  A a = f(g());
}
