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
całkowity ze znakiem.  A już jego implementacja zależy od systemu: typ
może być 24 bitowy lub 32 bitowy, little-endian lub big-endian.

Koncepty przeszły długą drogę, żeby w końcu być w C++20.  Od strony
technicznej programowania w C++, koncepty pozwalają na wygodną i pełną
definicję wymagań stawianych argumentom szablonu.  Dzięki konceptom
wzbogacono i uproszczono programowanie uogólnione w C++, a komunikaty
o błędach generowane przez kompilator są **jasne**.

Koncept jako idea programowania funkcjonuje od dekad.  Koncept to
zbiór **minimalnych** warunków dotyczących typu.  Ponieważ mówimy o
minimalnych warunkach, to koncepty są minimalistyczne: stawiane są
tylko te wymagania, które są **niezbędne**.  W ten sposób
programowanie uogólnione ma swoje korzenie w algebrze abstrakcyjnej
zapoczątkowanej przez Emmy Noether, gdzie struktury algebraiczne
(np. monoid) definiuje się przez minimalne warunki.  W informatyce,
podstawowe własności typów (a w tym i struktur danych) możemy opisać
własnościami struktur algebraicznych.

Możemy nawet powiedzieć, że `std::set<T>` i `std::vector<T>` są
konceptami.  Możemy powiedzieć nawet, że sortowanie jest pewnym
konceptem, pewną ideą oderwaną od typu sortowanych danych.  W C++
jednak koncepty dotyczą wyłącznie danych, a nie algorytmów.  Na
przykład, w C++ nie ma sposobu upewnienia się, że algorytm sortuje
stabilnie.  Jeżli chcemy sortować stabilnie, to powinniśmy wybrać
`std::stable_sort`, w przeciwnym razie `std::sort`.

Koncept jako idea był zastosowany od początku przez Alexandra
Stepanova w standardowej bibliotece szablonów (STL).  Już wtedy, w
dokumentacji STLa na stronie Silicon Graphics (SGI) mówiono o
iteratorze jako koncepcie, o koncepcie jako abstrakcyjnej idei.  Wtedy
nie bardzo wiedziałem o co chodzi, a dokumentacja tych konceptów nie
trafiała do mnie, bo koncepty nie były wprost wpisane w przykładowe
programy, więc mi się to po prostu nie kompilowało.  Koncepty jako
idea były, ale nie były zdefiniowane w postaci biblioteki C++, bo
język nie miał takiej funkcjonalności.  Teraz jest i to bogata.

# Koncept w C++20

**Koncept to nazwane ograniczenie.** Ponieważ ograniczenie jest
predykatem czasu kompilacji, to koncept też nim jest, ale nazwanym.
Ponieważ ograniczenie jest sparametryzowane (ma parametry, więc
przyjmuje argumenty), to koncept też jest sparametryzowany, czyli jest
szablonem.  Tak więc w C++ szablony są nie tylko struktur danych,
funkcji, czy typów, ale też konceptów.

Koncept definiujemy tak:

```cpp
template <lista parametrów>
concept nazwa = ograniczenie
```

Koncept nie może mieć ograniczeń, czyli po liście parametrów nie
możemy napisać `requires` i podać ograniczenia na parametry.

Oto prosty przykład:

```cpp
{% include_relative intro.cc %}
```

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

Nazwę konceptu możeny nawet pominąć, pozostawiając typ `auto`:

```cpp
{% include_relative auto.cc %}
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
