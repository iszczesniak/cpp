#include <iostream>
#include <string>

template <typename T>
// void primary(void (*)(const T &t))
// void primary(void (&)(const T &t))
void primary(void (const T &t))
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void spec1(const int &)
{
}

void spec2(const std::string &)
{
}

void spec3(bool)
{
}

int main()
{
  primary(spec1);
  primary(spec2);
  // primary(spec3);
}
