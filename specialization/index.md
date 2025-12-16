---
title: Template specialization
---

# Introduction

We can **specialize** a function or type template.  The template that
we specialize is called a **primary template** to differentiate it
from the specialization that is also a template.  A specialization
template is called a specialization in short.  A specialization
overwrites the definition of its primary template.  We cannot
specialize further a specialization.

A primary template (of a function or type) defines the template name
and its parameters: their number and their kinds.  A specialization
has to have the same name (of a function or type) and provide all
arguments for the primary template.

A specialization can be **partial** or **explicit**.  A specialization
of a function template can only be explicit (it cannot be partial).  A
specialization of a type template can be either partial or explicit.

As opposed to the explicit specialization, the partial specialization
allows to define template parameters that are used in the arguments of
the primary template.

# A function template specialization

A function template can be specialized only explicitly, i.e., all
arguments for the primary template are explicitly given: a explicit
specialization template has no parameters (its parameter list is
empty).  Therefore a declaration and a definition of a function
template specialization begin with the template header of an empty
parameter list:

```
template <>
```

Then there follows the definition of the function template that looks
just like a definition of a regular (non-template) function, because
we do not use in it (i.e., in the function parameter list and the
function body) the parameter names of the primary template, but just
its arguments (e.g., `int`, `1` or `std::list`).  But there is a
difference.

The difference is about the function name.  In the specialization we
put the argument list of the primary template after the function name,
which we don't do for a non-template function.

Here's an example:

```cpp
{% include_relative foo1.cc %}
```

We can also only declare a primary template or a specialization.  If
we declare a primary template and not define it later, then there is
no definition of this function primary template.  We can specialize
this template and use it only for the specializations defined.  This
is shown by the example below.

We can skip the argument list for the primary template if the compiler
is able to figure it out (deduce it?) based on the function parameter
list.  In the example below we skipped the argument list (`<A>`) of
the primary template after the function name `foo` in the declaration
and definition of the specialization.

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
