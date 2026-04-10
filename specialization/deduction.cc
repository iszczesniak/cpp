#include <iostream>
#include <string>

template <typename T>
// void foo(void (&)(const T &t))
// void foo(void (*)(const T &t))
void foo(void (const T &t))
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void goo1(const int &)
{
}

void goo2(const std::string &)
{
}

void goo3(bool)
{
}

int main()
{
  foo(goo1);
  foo(goo2);
  // foo(goo3);
}
