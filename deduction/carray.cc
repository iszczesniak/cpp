#include <iostream>

template <typename T, unsigned I>
void
roo(T (&)[I])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template <typename T, unsigned I>
void
poo(T (*)[I])
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int
main()
{
  const char *t1[] = {"Hello", "World!"};
  int t2[] = {1, 2, 3, 4, 5};

  roo(t1);
  roo(t2);

  poo(&t1);
  poo(&t2);
}
