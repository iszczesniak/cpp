---
title: Przeciążenia zwykłych funkcji
---

# Wyprowadzenie

Przeciążenie jest mechanizmem abstrakcji, czyli pozwala uogólniać kod.
Zwykłe (nieszablonowe) funkcje (zarówno nieskładowe jak i składowe)
mogą być przeciążane.  Kiedy wywołujemy funkcję, kompilator musi
wybrać funkcję spośród zbioru przeciążeń.

# Konwersja

# Funkcja składowa a nieskładowa, w tym operatorowa

# Klas nie można przeciążać

Możemy zdefiniować tylko jeden szablon klasy.  Jest to szablon
podstawowy, który możemy częściowo albo całkowicie specjalizować.  Nie
możemy definiować kolejnych szablonów podstawowych dla klasy o tej
samej nazwie, bo byłoby to przeciążanie klasy, na co C++ nie pozwala.
