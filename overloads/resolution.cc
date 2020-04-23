#include <iostream>

void
foo(const char *, const char *)
{
  std::cout << "normal\n";
}

template <typename T1, typename T2>
void
foo(T1 t1, T2 t2)
{
  std::cout << "template\n";
}

int
main()
{
  char a1[] = "Hello";
  const char a2[] = "World!";
  foo(a1, a2);
}
