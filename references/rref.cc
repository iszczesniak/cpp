#include <iostream>

int main()
{
  // BŁĄD: brak inicjalizacji.
  // int &&a;

  int i;

  // BŁĄD: r-referencja nie może wskazać l-wartości.
  // int &&z = i;

  int &l = i;
  // BŁĄD: r-referencja nie może być inicjalizowana l-wartością (którą
  // jest l-referencja).
  // int &&r = l;

  // OK: wskazujemy r-wartość.
  int &&x = 1;

  // BŁĄD: Inicjalizacja r-referencji na podstawie l-wartości (x ma
  // nazwę, więc jest l-wartością)
  // int &&z = x;
}
