#include <iostream>

struct A
{
  int m_i = 0;

  auto
  foo()
  {
    // Wygląda na to, że nasze domknięcie będzie miało pole m_i.
    return [=](int m){m_i = m;};
  }
};

int
main()
{
  A a;
  // Okazuje się, że domknięcie działa na obiekcie "a".
  a.foo()(1);
  std::cout << a.m_i << std::endl;
  auto c = A().foo();
  // Działamy na danych obiektu, który już nie istnieje!
  c(1);
}
