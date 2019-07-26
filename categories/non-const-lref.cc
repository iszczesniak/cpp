#include <cassert>
#include <iostream>

int main()
{
  int x = 1;
  int y = 2;

  // BŁĄD: brak inicjalizacji.
  // int &a;

  // OK, raz na zawsze zainicjalizowane.
  int &z = x;

  // Wskaźnik na referencję to wskaźnik na obiekt.
  assert (&z == &x);

  // To nie jest reinicjalizacja!  Przypisujemy wartość zmiennej y do
  // zmiennej x.
  z = y;

  //
  std::cout << "x = " << x << std::endl;
}
