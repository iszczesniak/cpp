---
title: Przeciążenia zwykłych funkcji
---

# Wyprowadzenie

Przeciążenie jest mechanizmem abstrakcji, czyli pozwala uogólniać kod.
Zwykłe (nieszablonowe) funkcje (zarówno nieskładowe jak i składowe)
mogą być przeciążane.  Kiedy wywołujemy funkcję, kompilator musi
wybrać wybrać przeciążenie, które użyje.

# Wybór przeciążenia:

* liczba argumentów, także domyślnymi,

# Stopień konwersja

Konwersje między typem argumentu a typem parametru dzieli się na:

1. Brak konwersji albo konwersja trywialna: T -> const T, rozpad
   tablicy, rozpad funkcji,

2. Promocje: całkowita (np. boot -> int, char -> int),
   zmiennoprzecinkowa: float -> double,

3. Konwersja: int -> double, double -> long double, Derived * -> Base
   *, Derived & -> Base &,

4. Konwersje definiowane przez użytkownika.

# Funkcja składowa a nieskładowa, w tym operatorowa

# Klas nie można przeciążać

Możemy zdefiniować tylko jeden szablon klasy.  Jest to szablon
podstawowy, który możemy częściowo albo całkowicie specjalizować.  Nie
możemy definiować kolejnych szablonów podstawowych dla klasy o tej
samej nazwie, bo byłoby to przeciążanie klasy, na co C++ nie pozwala.
