---
title: Koncepty
---

# Wprowadzenie

Alexander Stepanov powiedział:

> Concepts are all about semantics.

Koncept ma mieć jakieś **znaczenie**.  Jak mówimy o liczbie
całkowitej, to wiemy o co chodzi, nie musimy precyzyjnie opisywać jak,
na przykład, jest ona reprezentowana w pamięci komputera, bo jest to
już raczej szczegół implementacyjny.  Koncept jest pewną ugruntowaną
ideą.

Możemy powiedzieć, że typ danych `int` już jest konceptem: jest to typ
całkowity ze znakiem, którego implementacja zależy od systemu.  Typ
może być 24 bitowy lub 32 bitowy, w kodowaniu zależnym od systemu,
np. little-endian lub big-endian.

Koncepty przeszły długą drogę, żeby w końcu być w C++20.  Od strony
technicznej programowania w C++, koncepty pozwalają na wygodną i pełną
definicję wymagań stawianych argumentom szablonu.  Dzięki konceptom
wzbogacono i uproszczono programowanie uogólnione w C++, a komunikaty
o błędach generowane przez kompilator są **jasne**.

Koncept jako idea programowania funkcjonuje w programowaniu od dekad.
Koncept jest to zbiór **minimalnych** warunków, które typ danych musi
spełniać.  Ponieważ mówimy o minimalnych warunkach, to koncepty są
minimalistyczne: stawiane są tylko te wymagania, które są niezbędne.
W ten sposób programowanie uogólnione ma swoje korzenie w algebrze
abstrakcyjnej zapoczątkowanej przez Emmy Noether, której podstawą jest
stawianie minimalnych warunków strukturom algebraicznym.  W
informatyce, podstawowe własności typów i struktur danych możemy
opisać własnościami struktur algebraicznych.

Możemy nawet powiedzieć, że `std::vector<T>` jest pewnym konceptem,
który reprezentuje wektor.  Możemy powiedzieć nawet, że sortowanie
jest pewnym konceptem, pewną ideą oderwaną od sortowanych danych.  W
C++ jednak koncepty dotyczą wyłącznie danych, a nie algorytmów.  Na
przykład, w C++ nie ma sposobu upewnienia się, że algorytm sortuje
stabilnie.  Jeżli chcemy sortować stabilnie, to powinniśmy wybrać
`std::stable_sort`, w przeciwnym razie `std::sort`.

Koncept jako idea była stosowana od początku w standardowej bibliotece
szablonów.  Już wtedy, w dokumentacji STLa na stronie Silicon Graphics
(SGI) mówiono o iteratorze jako koncepcie.  Wtedy nie bardzo
wiedziałem o co chodzi, a dokumentacja tych konceptów nie trafiała do
mnie, bo nie było w niej przykładowych programów z konceptami.  Mi się
to po prostu nie kompilowało.  Koncepty jako idea były, ale nie były
zdefiniowane w postaci biblioteki C++, bo język nie miał takiej
funkcjonalności.  Teraz jest i to bogata.

# Koncept w C++20

**Koncept to nazwane ograniczenie.**  Ponieważ ograniczenie jest
sparametryzowane (ma parametry, więc przyjmuje argumenty), to koncept
też jest sparametryzowany, czyli jest szablonem.  Oto prosty przykład:

```cpp
{% include_relative intro.cc %}
```

Ponieważ ograniczenie jest predykatem czasu kompilacji, to koncept też
nim jest, ale nazwanym.  Tak więc w C++ mamy szablonowe mogą być nie
tylko struktury danych, funkcje, czy typy, ale też koncepty.

Koncept definiujemy tak:

```cpp
template <lista parametrów>
concept nazwa = ograniczenie
```

Koncept nie może mieć ograniczeń, czyli po liście parametrów nie
możemy napisać `requires` i podać ograniczenia na parametry.

# Skrócone zapisy

Korzystając z konceptów możemy skrócić definicję szablonów używających
konceptów.  Zamiast deklarować typowy parametr `T` z użyciem
`typename` i potem definiować ograniczenie na tym parametrze, na
przykład, `requires incr<T>`, to możemy zadeklarować parametr szablonu
już nie jako typowy, ale spełniający koncept `incr`, czyli jako `incr
T`.  Oto przykład:

```cpp
{% include_relative short.cc %}
```

Pozwolono nam jeszcze bardziej skrócić definicję szablonu.  Już nie
musimy pisać, że chodzi o szablon, którego parametr spełnia jakiś
koncept.  Teraz możemy zdefiniować funkcję szablonową, używając nazwy
konceptu jako typu parametru funkcji, po której podajemy typ `auto`.
Taki koncept musi być jednoargumentowy.  Oto przykład:

```cpp
{% include_relative shorter.cc %}
```

# Standardowe koncepty

W bibliotece standardowej C++, główną biblioteką konceptów jest
`concepts`, ale koncepty są zdefiniowane też w innym bibliotekach.  Na
przykład w bibliotece `iterator` zdefiniowano koncept `incrementable`.

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
