---
title: Specjalizacja szablonów
---

# Wprowadzenie

Możemy **specjalizować** szablon funkcji czy typu.  Szablon, który
specjalizujemy nazywamy **szablonem podstawowy** (ang. primary
template), żeby odróżnić go od specjalizacji, która też jest
szablonem.  Szablon specjalizacji nazywamy w skrócie specjalizacją.
Specjalizacja nadpisuje definicję swojego szablonu podstawowego.  Nie
można dalej specjalizować specjalizacji.

Szablon podstawowy (funkcji, typu) definiuje nazwę szablonu i jego
parametry: ich liczbę i rodzaje.  Specjalizacja musi mieć tą samą
nazwę (funkcji, typu) i dostarczyć wszystkie argumenty dla szablonu
podstawowego.

Specjalizacja może być **częściowa** (ang. partial specialization)
albo **jawna** (ang. explicit specialization).  Specjalizacja szablonu
funkcji może być tylko jawna (nie może być częściowa).  Specjalizacja
szablonu typu może być częściowa albo jawna.

W przeciwieństwie do specjalizacji jawnej, częściowa specjalizacja
pozwala na zdefiniowanie parametrów szablonu, które są używane w
argumentach szablonu podstawowego.

# Specjalizacja szablonu funkcji

Szablon funkcji może być specjalizowany tylko jawnie, czyli wszystkie
argumenty szablonu podstawowego są jawnie podane: szablon jawnej
specjalizacji nie ma już parametrów (jego lista parametrów jest
pusta).  Tak więc deklaracja i definicja specjalizacji szablonu
funkcji rozpoczynają się nagłówkiem szablonu z pustą listą parametrów:

```
template <>
```

Potem następuje definicja szablonu funkcji, która wygląda jak
definicja zwykłej (nieszablonowej) funkcji, bo nie używamy w niej
(czyli w liście parametrów funkcji i ciele funkcji) nazw parametrów
szablonu podstawowego, a jedynie ich argumentów (np. `int`, `1` czy
`std::list`).  Ale jest pewna różnica.

Różnica dotyczy nazwy funkcji.  W specjalizacji podajemy listę
argumentów szablonu podstawowego po nazwie funkcji, czego w definicji
zwykłej funkcji nie robimy.

Oto przykład:

```cpp
{% include_relative foo1.cc %}
```

Szablon podstawowy czy specjalizację możemy także tylko zadeklarować.
Jeżeli zadeklarujemy szablon podstawowy i go później nie zdefiniujemy,
to nie będzie implementacji tego szablonu podstawowego funkcji.
Będziemy mogli specjalizować ten szablon i używać go wyłącznie dla
zdefiniowanych specjalizacji.  Pokazuje to przykład niżej.

Listę argumentów szablonu podstawowego możemy pominąć, jeżeli
kompilator jest w stanie je wytrzasnąć (wywnioskować?) na podstawie
listy parametrów funkcji.  W przykładzie niżej pominęliśmy listę
argumentów (`<A>`) szablonu podstawowego po nazwie funkcji `foo` w
deklaracji i definicji specjalizacji.

```cpp
{% include_relative foo2.cc %}
```

Nie możemy częściowo specjalizować szablonu funkcji.  Częściowa
specjalizacja definiowałaby parametr szablonu, ale to nie jest
dozwolone:

```cpp
{% include_relative complete.cc %}
```

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu.  W
specjalizacji musimy podać argument `0` parametru `N`, bo kompilator
nie jest w stanie go wytrzasnąć.  Nie podaliśmy jednak argumentu `int`
dla parametru `T`, bo kompilator może go sobie wytrzasnąć.

```cpp
{% include_relative print.cc %}
```

## Zwykła funkcja a szablon funkcji

Czy możemy się obyć bez szablonów?  Czy przeciążenia zwykłych funkcji
nie wystarczą?  W przykładzie niżej funkcja `foo` jest przeciążona,
żeby można użyć różnych implementacji w zależności od argumentu
funkcji.  Problem w tym, że dla każdego wymaganego typu musimy
implementować przeciążenie, albo korzystać z konwersji niejawnej, jak
w przykładzie niżej: dla argumentu `'1'` typu `char` jest wywołane
przeciążenia dla typu `int`.

```cpp
{% include_relative overloads.cc %}
```

W powyższym przykładzie zamieńmy przeciążenie zwykłej funkcji dla
`const int &` na szablon podstawowy, żeby jedną implementacją załatwić
wywołania `foo(1)` i foo('1').  Zatem w przykładzie niżej mamy szablon
podstawowy dla dowolnego typu i zwykłą funkcję dla typu `A`.  Czy dla
wywołania funkcji `foo` z argumentem `A()` będzie użyty podstawowy
szablon funkcji czy zwykła funkcja?  **Zwykła funkcja zawsze ma
pierwszeństwo.**

```cpp
{% include_relative mix1.cc %}
```

Dla podstawowego szablonu funkcji możemy dodać specjalizację dla `T =
A`, ale kompilator i tak używa zwykłej funkcja.  Podczas wyboru
przeciążenia, kompilator nie rozważa specjalizacji, a jedynie
przeciążenia zwykłych funkcji i przeciążenia podstawowych szablonów
funkcji.

```cpp
{% include_relative mix2.cc %}
```

## Kiedy potrzebujemy specjalizacji

Wydaje się, że specjalizacja szablonu jest zbędna, bo podobną
funkcjonalność uzyskaliśmy przeciążeniami zwykłej funkcji.  Jest
jednak funkcjonalność specjalizacji, której nie osiągniemy przez
przeciążenia.

Specjalizacja szablonów pozwala użytkownikowi do dostarczenie
implementacji dla kodu, który został już dołączony w pliku
nagłówkowym, np. biblioteki szablonowej.  Biblioteka deklaruje
podstawowy szablon funkcji, której wymaga, a definicję specjalizacji
czy nawet szablonu podstawowego pozostawia użytkownikowi.  Tak może
wyglądać plik nagłówkowy `library.hpp`:

```cpp
{% include_relative library.hpp %}
```

Tak może wyglądać użycie biblioteki:

```cpp
{% include_relative need.cc %}
```

C++ jest kompilatorem jednego przebiegu (ang. one-pass compiler), więc
jeżeli zwykłą funkcję `foo` zadeklarujemy po dołączeniu naszej
biblioteki, to funkcja biblioteczna `goo` nie zna jej i nie może jej
wywołać.  Natomiast funkcja `goo` zna i może użyć podstawowego
szablonu funkcji `foo`, bo został wcześniej zadeklarowany.

Moblibyśmy przenieść definicję zwykłej funkcji `foo` przed dyrektywę
`#include`, żeby funkcja `goo` mogła ją wywołać, ale lepiej nie
wprowadzać takiego nieporządku.

# Specjalizacja szablonów typów

Możemy zadeklarować lub zdefiniować szablon typu, czyli struktury,
klasy czy unii.  Ten szablon podstawowy możemy specjalizować jawnie
lub częściowo.  Szablon podstawowy i jej specjalizacje mają jedynie
wspólną nazwę typu, a ich interfejsy (składowe publiczne),
implementacje i wielkości w pamięci mogą się całkowicie różnić.

Przykładem specjalizacji typu w bibliotece standardowej jest
`std::vector<bool>`, czyli specjalizacja `std::vector` dla typu
`bool`.  Ta specjalizacja ma interfejs podobny do interfejsu szablonu
podstawowego, ale jej implementacja jest zupełnie inna.

## Przykład jawnej specjalizacji

Niżej definiujemy szablon podstawowy typu `A` z jedną funkcją składową
`foo`.  Dla jawnej specjalizacji dla argumentu `double`, typ `A`
dziedziczy po `std::pair`, ma funkcję `goo`, ale nie ma już funkcji
`foo`.

```cpp
{% include_relative struct_complete.cc %}
```

## Częściowa specjalizacja i przykład

Szablon częściowej specjalizacji definiuje od nowa swoje parametry,
które nie muszą mieć nic wspólnego z parametrami szablonu
podstawowego.  Ważne jedynie, żeby jawnie podać (po nazwie typu)
argumenty szablonu podstawowego, które muszą zależeć od (używać)
parametrów specjalizacji.

W przykładzie niżej deklarujemy szablon podstawowy typu `A` z typowym
parametrem `T`, a następnie definiujemy dwie specjalizacje, obie z
parametrem `T`.  Parametry `T` trzech szablonów nie mają ze sobą nic
wspólnego, ponieważ mają lokalny zakres.

Pierwsza specjalizacja definiuje implementację typu `A` dla przypadku,
gdzie argumentem szablonu podstawowego jest `std::vector`.  Pozwalamy
na dowolny typ elementów wektora poprzez użycie parametru `T`
specjalizacji.

Druga specjalizacja definiuje implementację typu `A` dla przypadku,
gdzie argumentem szablonu podstawowego jest szablon typu, który może
być skonkretyzowany z jednym argumentem `int`.

W funkcji `main` typ `A` został użyty z dwoma specjalizacjami.
Najciekawsze jest ostatnie użycie, które jest zakomentowane, bo nie
może się kompilować: kompilator nie jest w stanie zdecydować, której
specjalizacji użyć.

```cpp
{% include_relative struct_partial.cc %}
```

# Podsumowanie

* Specjalizować można szablon funkcji i szablon typu.

* Specjalizacja może być częściowa albo jawna.

* Specjalizacja pozwala na nadpisanie implementacji szablonu
  podstawowego.

# Quiz

* Czy szablon funkcji może być częściowo specjalizowany?

* Czy w wyborze przeciążenia pierwszeństwo ma funkcja szablonowa czy
  zwykła funkcja?

* Czy specjalizacja szablonu typu dziedziczy po podstawowym szablonie
  typu?

<!-- LocalWords: lvalue lvalues rvalue -->
