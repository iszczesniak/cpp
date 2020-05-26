---
title: Koncepty
---

# Wprowadzenie

**Koncepty** przeszły długą drogę, żeby w końcu być w C++20.  Od
strony technicznej programowania w C++, koncepty pozwalają na wygodną
i pełną definicję wymagań stawianych argumentom szablonu.  Dzięki
konceptom uproszczono składnię szablonów funkcji, a komunikaty o
błędach generowane przez kompilator są **proste**.

Koncept jako idea programowania funkcjonuje w programowaniu od dekad.
*Koncept jest to zbiór **minimalnych** warunków, które typ danych musi
spełniać.* Ponieważ mówimy o minimalnych warunkach, to koncepty są
minimalistyczne: stawiane są tylko te wymagania, które są absolutnie
potrzebne.  W ten sposób programowanie uogólnione ma swoje korzenie w
algebrze abstrakcyjnej zapoczątkowanej przez Emmy Noether.

Możemy powiedzieć, że typ danych `int` jest konceptem: jest to typ
całkowity, którego implementacja zależy od 

# Koncept w C++20

Koncept to szablon predykatu, który jest opracowywany w czasie
kompilacji.  Predykat to wyrażenie typu logicznego.  To więc w C++
szablononowe są już nie tylko struktury danych, funkcje, czy typy, ale
też koncepty.  Definicja szablonu konceptu wygląda tak:




<!-- LocalWords: expr -->
<!-- LocalWords: lvalue lvalues rvalue -->
<!-- LocalWords: rvalue -->

<!-- LocalWords: deklaratora -->
<!-- LocalWords: deklaratorem -->

<!-- LocalWords: inicjalizowana -->
<!-- LocalWords: inicjalizowaną -->
<!-- LocalWords: inicjalizowane -->
<!-- LocalWords: inicjalizującego -->
<!-- LocalWords: inicjalizującym -->

<!-- LocalWords: wyoptymalizowana -->
<!-- LocalWords: wyoptymalizowane -->
<!-- LocalWords: wyoptymalizowanie -->

<!-- LocalWords: zainicjalizowana -->
<!-- LocalWords: zainicjalizowaną -->
<!-- LocalWords: zainicjalizowane -->

<!-- LocalWords: binds -->
<!-- LocalWords: nullptr -->
<!-- LocalWords: object -->
<!-- LocalWords: overload -->
<!-- LocalWords: name names -->
<!-- LocalWords: member -->
<!-- LocalWords: move -->
<!-- LocalWords: reference references -->
<!-- LocalWords: refer refers -->
<!-- LocalWords: resolution -->
<!-- LocalWords: title -->
