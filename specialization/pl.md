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
definicja zwykłej funkcji, bo nie używamy w niej (czyli w liście
parametrów funkcji i ciele funkcji) nazw parametrów szablonu
podstawowego, a jedynie ich ustalonych wartości (np. `int`, `1` czy
`std::list`).  Ale jest pewna różnica.

Różnica dotyczy nazwy funkcji.  W specjalizacji podajemy listę
argumentów szablonu podstawowego po nazwie funkcji, czego w definicji
zwykłej funkcji nie robimy.

Oto przykład:

```cpp
{% include_relative foo1.cc %}
```

Szablon podstawowy i specjalizację możemy także deklarować.  Jeżeli
zadeklarujemy szablon podstawowy, ale go nie zdefiniujemy, to nie
będzie podstawowej implementacji tego szablonu funkcji.  Będziemy
mogli specjalizować szablon i używać go wyłącznie dla tych
specjalizacji.  Pokazuje to przykład niżej.

Listę argumentów szablonu podstawowego możemy pominąć, jeżeli
kompilator jest w stanie wywnioskować te argumenty na podstawie listy
parametrów funkcji.  W przykładzie niżej pominęliśmy listę argumentów
(`<A>`) szablonu podstawowego po nazwie funkcji `foo` w deklaracji i
definicji specjalizacji.

```cpp
{% include_relative foo2.cc %}
```

Nie możemy częściowo specjalizować szablonów funkcji.  Specjalizacja
częściowa polegałaby na wprowadzeniu parametru dla specjalizacji, ale
nie jest to dozwolone, jak pokazuje przykład niżej.

```cpp
{% include_relative complete.cc %}
```

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu.  W
specjalizacji szablonu musimy podać argument `0` parametru `N`, bo
kompilator nie jest w stanie go wywnioskować.  Argument `int`
parametru `T` może być wywnioskowany, więc nie jest podany.

```cpp
{% include_relative print.cc %}
```

## Przeciążanie funkcji a szablony

Czy możemy się obyć bez szablonów?  W przykładzie niżej funkcja `foo`
jest przeciążona, żeby w zależności od argumentu wywołania funkcji
dostarczyć inną implementację.

Problem w tym, że nie mamy szablonu, który mógłby być zastosowany dla
dowolnego typu i dlatego dla argumentu `.2` typu `double` jest
wywołane przeciążenia dla typu `int`.

```cpp
{% include_relative overloads.cc %}
```

Możemy dołożyć szablon podstawowy do przykładu, jak pokazano niżej.
Mamy szablon dla dowolnego typu i przeciążenie dla typu `A`.  Czy dla
wywołania funkcji `foo` z argumentem `A()` będzie użyty szablon czy
przeciążenie?  A dokładnie mówiąc przeciążenie funkcji szablonowej
(czyli funkcji, która otrzymaliśmy po konkretyzacji podstawowego
szablonu funkcji dla `T = A`) czy przeciążenie zwykłej funkcji?
**Przeciążenie zwykłej funkcji zawsze ma pierwszeństwo.**

```cpp
{% include_relative mix1.cc %}
```

Możemy dodać także specjalizację dla `T = A`, ale i tak zostanie
wybrane przeciążenie zwykłej funkcji.  Podczas wyboru przeciążenia,
kompilator nie rozważa specjalizacji, a jedynie przeciążenia zwykłych
funkcji i przeciążenia funkcji szablonowych.  Tak więc dodanie
specjalizacji i tak nie namówi kompilator na jej użycie.

```cpp
{% include_relative mix2.cc %}
```

## Kiedy potrzebujemy specjalizacji

Wydaje się, że specjalizacja szablonu jest zbędna, bo tą samą
funkcjonalność uzyskaliśmy przeciążając zwykłą funkcję.  Jest jednak
funkcjonalność specjalizacji, której nie osiągniemy przez
przeciążenia.

Specjalizacja szablonów pozwala na zdefiniowanie przez użytkownika
funkcji dla kodu, który został już dołączony w pliku nagłówkowym,
np. biblioteki szablonowej.  Biblioteka deklaruje szablon funkcji,
którą potrzebuje, a definicję specjalizacji czy nawet szablonu
podstawowego można pozostawić użytkownikowi.  Tak może wyglądać plik
nagłówkowy `library.hpp`:

```cpp
{% include_relative library.hpp %}
```

Tak może wyglądać użycie biblioteki:

```cpp
{% include_relative need.cc %}
```

Jeżeli przeciążenie funkcji zadeklarujemy po dołączeniu biblioteki, to
funkcja `goo` nie będzie go znała i nie użyje go.  Funkcja wie
natomiast, że może użyć szablonu funkcji `foo`, bo jej szablon
podstawowy został zadeklarowany.

Możemy też przenieść definicję przeciążenia funkcji `foo` przed
dyrektywę `#include`, żeby funkcja `goo` mogła skorzystać z
przeciążenia, ale lepiej nie wprowadzać takiego nieporządku.

# Specjalizacja szablonów typów użytkownika

Możemy zadeklarować lub zdefiniować szablon typu użytkownika, czyli
struktury, klasy i unii.  Ten szablon podstawowy możemy specjalizować
całkowicie lub częściowo.  Szablon podstawowy i jej specjalizacje mają
jedynie wspólną nazwę typu, a ich interfejsy (składowe dostępne
użytkownikowi), implementacje i wielkości w pamięci mogą się
całkowicie różnić.

Przykładem specjalizacji typu w bibliotece standardowej jest
`std::vector<bool>`, czyli kontenera `std::vector` dla typu `bool`.
Ta specjalizacja ma podobny interfejs jak szablon podstawowy
`std::vector`, ale zupełnie inną implementację.

## Przykład całkowitej specjalizacji

Niżej definiujemy szablon podstawowy typu `A` z jedną funkcją składową
`foo`.  Całkowita specjalizacja dla argumentu `double` nie ma funkcji
`foo`, a ma funkcję `goo` i dziedziczy po `std::pair`.  Całkowita
specjalizacja typu ma identyczną składnię, jak całkowita specjalizacja
funkcji.

```cpp
{% include_relative struct_complete.cc %}
```

## Częściowa specjalizacja i przykład

W częściowej specjalizacji szablonu typu wprowadzamy parametr, który
używamy w definicji argumentu szablonu podstawowego.  Lista parametrów
specjalizacji nie jest już pusta, jak w przypadku całkowitej
specjalizacji.

W przykładzie niżej deklarujemy szablon podstawowy typu `A` z typowym
parametrem `T`, a następnie definiujemy dwie specjalizacje, obie z
parametrem `T`.  Parametry `T` trzech szablonów nie mają ze sobą nic
wspólnego, ponieważ mają lokalny zakres.

Pierwsza specjalizacja definiuje implementację typu `A` dla
przypadków, kiedy argumentem szablonu podstawowego jest `std::vector`.
Pozwalamy na dowolny typ elementów wektora poprzez użycie parametru
`T` specjalizacji.

Druga specjalizacja definiuje implementację typu `A` dla przypadków,
kiedy argumentem szablonu podstawowego jest typ szablonowy, który może
być skonkretyzowany z jednym argumentem `int`.

W funkcji `main` typ `A` został użyty z różnymi specjalizacjami.
Najciekawszy jest ostatni przypadek, który jest zakomentowany, bo nie
może się kompilować: kompilator nie jest w stanie zdecydować, której
specjalizacji użyć.

```cpp
{% include_relative struct_partial.cc %}
```

# Podsumowanie

* Specjalizować można szablony funkcji i typy szablonowe.

* Specjalizacja może być częściowa albo całkowita.

* Specjalizacja pozwala na nadpisanie implementacji szablonu
  podstawowego dla wybranych kombinacji jego argumentów.

# Quiz

* Czy szablon funkcji może być częściowo specjalizowany?

* Czy w wyborze przeciążenia pierwszeństwo ma funkcja szablonowa czy
  przeciążenie funkcji?

* Czy specjalizacja szablonu typu dziedziczy po podstawowym szablonie
  typu?

<!-- LocalWords: lvalue lvalues rvalue -->
