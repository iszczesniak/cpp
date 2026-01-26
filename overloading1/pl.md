---
title: Przeciążenia zwykłych funkcji
---

# Wyprowadzenie

Przeciążenie jest mechanizmem abstrakcji, czyli pozwala uogólniać kod.
Zwykłe (nieszablonowe) funkcje (zarówno nieskładowe jak i składowe)
mogą być przeciążane.  Kiedy wywołujemy funkcję, kompilator musi
wybrać wybrać przeciążenie, które użyje.

# Wybór przeciążenia:

* liczba argumentów, w uwzględnieniem argumentów domyślnych,

# Stopień konwersji

Konwersje między typem argumentu a typem parametru dzieli się na:

1. Brak konwersji albo konwersja trywialna: T -> const T, rozpad
   tablicy, rozpad funkcji,

2. Promocje: całkowita (np. boot -> int, char -> int),
   zmiennoprzecinkowa: float -> double,

3. Konwersja: int -> double, double -> long double, Derived * -> Base
   *, Derived & -> Base &,

4. Konwersje definiowane przez użytkownika.

# Funkcja składowa a nieskładowa, w tym operatorowa
