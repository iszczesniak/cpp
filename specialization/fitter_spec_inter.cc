#include <iostream>
#include <string>

template <typename T>
void primary1(void (T))
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T>
void primary2(void (T *))
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void spec1(int)
{
}

void spec2(int *)
{
}

int main()
{
  primary1(spec1);
  // primary2(spec1);

  primary1(spec2);
  primary2(spec2);
}
