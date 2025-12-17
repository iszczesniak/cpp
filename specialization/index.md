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

We cannot partially specialize a function template.  A partial
specialization would define a template parameter, but this is not
allowed:

```cpp
{% include_relative complete.cc %}
```

An example below shows a recursive function template, where the
recursion is terminated by a template specialization.  In the
specialization, we have to provide the argument `0` for parameter `N`,
because a compiler is unable to figure it out.  However, we didn't put
the argument `int` for the parameter `T`, because that a compiler can
figure out.

```cpp
{% include_relative print.cc %}
```

## Regular function vs function template

Can we do without templates?  Are overloads of regular functions not
enough?  In the example below the `foo` function is overloaded in
order to use different implementations depending on the function
argument.  The problem is that for every required type we either have
to implement an overload or use the implicit conversion, as in the
example below: for the argument `'1'` of type `char` there is called
the overload for type `int`.

```cpp
{% include_relative overloads.cc %}
```

In the above example, let's replace the regular function overload for
`const int &` with a primary template, so that with a single
implementation we can deal with `foo(1)` and foo('1').  Therefore in
the example below we have a primary template for any type, and a
regular function for type `A`.  Will the primary template or the
regular function be used when calling `foo` with an argument of type
`A`?  **A regular function always comes first.**

```cpp
{% include_relative mix1.cc %}
```

For the primary function template, we can add a specialization for `T
= A`, but a compler uses the regular function anyway.  During overload
resolution, a compiler does not consider specializations, but only the
overloads of regular functions and overloads of primary function
templates.

```cpp
{% include_relative mix2.cc %}
```

## When we need the specialization

It seems that a template specialization is redundant, because we
achieved similar functionality with regular function overloads.  There
is, however, a functionality of the specialization that we cannot
achieve with regular function overloads.

A template specialization allows a user to provide some implementation
to the code that was already included as a header file, e.g., a
template library.  A library declares a primary function template that
it requires, but the definition of a specialization or even of the
primary template leaves to the user.  That's how a header file
`library.hpp` can look like:

```cpp
{% include_relative library.hpp %}
```

And that's how to use the library:

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
