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

Koncept jako idea był zastosowany od początku lat dziewięćdziesiątych
przez Alexandra Stepanova w standardowej bibliotece szablonów (STL).
Już wtedy, w dokumentacji STLa na stronie Silicon Graphics (SGI)
mówiono o iteratorze jako koncepcie, o koncepcie jako abstrakcyjnej
idei.  Wtedy nie bardzo wiedziałem o co chodzi, a dokumentacja tych
konceptów nie trafiała do mnie, bo koncepty nie były wprost wpisane w
przykładowe programy, więc mi się to po prostu nie kompilowało.
Koncepty jako idea były, ale nie były zdefiniowane w postaci
biblioteki C++, bo język nie miał takiej funkcjonalności.  Teraz jest
i to bogata.

# Koncept w C++20

**Koncept to nazwane ograniczenie.** Ponieważ ograniczenie jest
predykatem czasu kompilacji, to koncept też nim jest, ale nazwanym.
Ponieważ ograniczenie jest sparametryzowane (ma parametry, więc
przyjmuje argumenty), to koncept też jest sparametryzowany, czyli jest
szablonem.  Tak więc w C++ szablony są nie tylko struktur danych,
funkcji, czy typów, ale też konceptów.

W bibliotece standardowej C++, główną biblioteką konceptów jest
`concepts`, ale koncepty są zdefiniowane też w innych bibliotekach.
Na przykład w bibliotece `iterator` zdefiniowano koncept
`incrementable`.

Koncept definiujemy tak:

```
template <lista parametrów>
concept nazwa = ograniczenie;
```

Konceptu nie można ograniczyć, czyli po liście parametrów nie możemy
napisać `requires` i podać ograniczenie na parametry.

Oto prosty przykład:

```cpp
{% include_relative intro.cc %}
```

Raz zdefiniowany koncept możemy użyć w różnych miejscach.  Gdybyśmy
nie chcieli używać konceptów, a jedynie ograniczeń, to musielibyśmy te
ograniczenia (często rozbudowane) kopiować w każde miejsce użycia.
Wiemy z autopsji, że kopiowanie i wklejanie to najlepszy sposób na
wprowadzenie błędów.

**Koncepty wprowadzają porządek**.  Biblioteka standardowa definiuje
standardowe koncepty.  Jak użyjemy standardowego konceptu, to każdy
będzie wiedział, o co nam chodziło (także my sami, jak już zapomnimy).

## Skrócone zapisy

Korzystając z konceptów możemy skrócić definicję szablonów.  Zamiast
deklarować typowy parametr `T` z użyciem `typename` i potem definiować
ograniczenie na tym parametrze, na przykład, `requires incr<T>`, to
możemy zadeklarować parametr szablonu już nie z użyciem `typename`,
ale jako spełniający koncept `incr`, czyli jako `incr T`.  Oto
przykład:

```cpp
{% include_relative short.cc %}
```

C++ pozwala nam jeszcze bardziej skrócić definicję szablonu.  Już nie
musimy pisać, że chodzi o szablon, którego parametr spełnia jakiś
koncept.  Teraz możemy zdefiniować szablon funkcji używając nazwy
konceptu jako typu parametru funkcji, po której podajemy specyfikator
typu `auto`.  Jako pierwszy argument konceptu będzie przekazany
wywnioskowany typ, ten który jest podstawiany w miejsce `auto`.  Oto
przykład:

```cpp
{% include_relative shorter.cc %}
```

Przy deklaracji typu parametru funkcji, nazwę konceptu możemy nawet
pominiąć, pozostawiając typ `auto` -- tak możemy zdefiniować w sposób
skrócony szablon funkcji.  W przykładzie niżej definiujemy dwa
przeciążenia szablonu funkcji `print`: jedno bez ograniczeń, a drugie
dla typu spełniającego koncept `integral`.  Wygląda prosto, ale wiemy,
że skomplikowane.

```cpp
{% include_relative auto.cc %}
```

### Doskonałe przekazywanie argumentów

Jeżeli użyjemy skróconej definicji szablonu, to tracimy nazwę
parametru szablonu, który musimy przekazać funkcji `std::forward` w
przypadku doskonałego przekazywania argumentów.  W tej sytuacji cel
możemy osiągnąć przekazując funkcji `std::forward` typ parametru
funkcji (zadeklarowanego jako referencja przekazująca), który możemy
otrzymać z użyciem specyfikatora `decltype`.  Oto przykład:

```cpp
{% include_relative forward.cc %}
```

# Przykład

Ograniczenia i koncepty mogą dotyczyć także callable.  W ten sposób
możemy określić ograniczenia na callable dotyczące przyjmowanych
argumentów czy zwracanego typu.

W przykładzie niżej używamy szablonu wariadycznego do zdefiniowania
konceptu `Callable`.  Definiujemy także typ `EmptyCallable`, który
jest domyślnym argumentem szablonu funkcji `f`.  Zdefiniowaliśmy także
domyślny `{}` argument wywołania funkcji `f`.

Oto przykład:

```cpp
{% include_relative callable.cc %}
```

Ale biblioteka standardowa ma już koncept podobny do naszego
`Callable`, którym jest `invocable`.  Teraz nasz przykład jest lepszy:

```cpp
{% include_relative invocable.cc %}
```

# Podsumowanie

* Koncept to nazwane ograniczenie.

* Koncept z idei stał się funkcjonalnością C++20.

* Podstawowe koncepty zostały zdefiniowane w bibliotece standardowej.

# Quiz

* Kiedy warto używać konceptów a nie ograniczeń?

* Na czym polega skrócony zapis szablonu funkcji?

* Jak doskonale przekazać argument wywołania funkcji, kiedy jej
  szablon jest zadeklarowany w skrócony sposób?
