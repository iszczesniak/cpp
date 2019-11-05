#include <cassert>
#include <iostream>

int
main()
{
  int x = 1;

  // BŁĄD: brak inicjalizacji.
  // int &a;

  // Stała c.
  const int c = 300000000;

  // BŁĄD: non-const l-reference cannot bind to a const.
  // int &r = c;

  // Can't initialize a non-const lvalue-reference with an rvalue.
  // int &ncr = 1;

  // Can initialize a non-const lvalue-reference with an lvalue.  The
  // dereference expression is an lvalue.
  int &cr = *((int *)nullptr);

  // OK, z raz na zawsze zainicjalizowane.
  int &z = x, y = 2;

  // To samo, co wyżej, ale teraz wiadomo, do czego odnosi się &:
  // int y = 2, &z = x;

  // Ten zapis jest mylący, bo sugeruje, że & odnosi się też do y:
  // int& z = x, y = 2;

  // Wskaźnik na referencję to wskaźnik na obiekt.
  assert (&z == &x);

  // To nie jest reinicjalizacja!  Przypisujemy wartość zmiennej y do
  // zmiennej x.
  z = y;

  // x = 2
  std::cout << "x = " << x << std::endl;

  // Inicjalizujemy l-referencję na podstawie l-wartości z.
  int &zz = z;
  // Inicjalizacja referencji zz wyżej ma ten sam efekt co, taka
  // inicjalizacja:
  int &zx = x;
}
