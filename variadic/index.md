---
title: Variadic template
---

# Introduction

C++11 introduced a **variadic template** that can accept any number of
template arguments, including none.  A variadic template is a
compile-time mechanism that is instantiated when used.

We recognize a variadic template by the ellipsis `...` in the
parameter list:

```cpp
{% include_relative intro.cc %}
```

In the above example, the ellipsis was used in the definition of a
parameter pack, and then in the pack expansion.

# Parameter pack

We define a **parameter pack** with the ellipsis that is followed by
the pack name.  A parameter pack can be of a template or a function.
A parameter pack is used in a **pack expansion** or a **fold
expression**.

## Template parameter pack

A **template parameter pack** defines template parameters of the same
kind: in the example above they are of the type kind, in the example
below of the value kind.

```cpp
{% include_relative value_pack.cc %}
```

### Pack expansion

The name of a pack with a trailing ellipsis is called a pack
expansion.  A template parameter pack is expended to a comma-separated
list of template parameters.

```cpp
{% include_relative expansion.cc %}
```

In the examples above, the template arguments were explicitly given,
because the functions and the constructor didn't have parameters
defined and call arguments passed, based on which the template
arguments could be deduced.  Arguments for template parameters of a
pack are deduced based on the definition of a **function parameter
pack** and the call arguments.

## Function parameter pack

A function parameter pack is defined in the list of function
parameters, also with the ellipsis: first we put the name of a
template parameter pack, the ellipsis, and then the name of the
function parameter pack.  Interestingly, the definition of the
function parameter pack is also the expansion of the template
parameter pack.

```cpp
{% include_relative fun_par_pack.cc %}
```

In the example above, the function accepts arguments by value.  To
make the function accept its arguments by a const reference, we define
the pack as `const Args &... args`.

### Pack expansion

An expansion of a function parameter pack is written as the name of
the pack followed by the ellipsis.

```cpp
{% include_relative factory.cc %}
```

A template parameter pack can be expanded in lockstep with (in tandem
with) the expansion of the function parameter pack, e.g., when we
initialize base objects using parameters of a constructor of the
derived class:

```cpp
{% include_relative lockstep.cc %}
```

# Recursive processing

We can process function arguments recursively.  The trick is to define
two function parameters: the first is a regular one to be processed by
the current call, the other is a parameter pack to be processed by
recursive call.  A pack is expended to an argument list for the
recursive call.  This way, the recursive-call pack is missing the
first parameter of the current-call pack.

```cpp
{% include_relative recursive.cc %}
```

# Wyrażenie złożenia

Wyrażenie złożenia (ang. a fold expression, od C++17) jest przepisem
na wygenerowanie wyrażenia z użyciem dowolnego **dwuargumentowego
operatora `op`** i paczki parametrów.  Wyrażenie tak się nazywa, bo
składa docelowe wyrażenie (to, które sami napisalibyśmy "ręcznie") do
skompresowanego zapisu.  Wyrażenie złożenia jest konkretyzowane w
czasie kompilacji dla danej paczki parametrów, co eliminuje potrzebę
przetwarzania rekurencyjnego.  Wyrażenie złożenia poznajemy po `...` i
nawiasach.  Są cztery wersje: dwie jednoargumentowe i dwie
dwuargumentowe, ale ciągle z użyciem tego samego operatora `op`.

Paczka `p` składa się z parametrów p<sub>1</sub>, p<sub>2</sub>, ...,
p<sub>(n-1)</sub>, p<sub>n</sub>.  Wyrażenie złożenia wymaga wyrażenia
`E`, które używa paczki `p`.  Wyrażenie `E` opracowane dla parametru
p<sub>i</sub> zapisujemy jako E<sub>i</sub>.

## Wersja jednoargumentowa

Wersje jednoargumentowe wyrażenia złożenia, gdzie argumentem jest `E`:

* wersja lewa: `(... op E)` -> ((E<sub>1</sub> op E<sub>2</sub>) op ...)

* wersja prawa: `(E op ...)` -> (... op (E<sub>(n-1)</sub> op E<sub>n</sub>))

Wersja lewa przetwarza parametry paczki od lewej strony (do prawej,
czyli od p<sub>1</sub> do p<sub>n</sub>), a prawa od prawej (do lewej,
czyli od p<sub>n</sub> do p<sub>1</sub>).  Zatem wersja lewa
przetwarza argumenty tak, jakby operator miał wiązanie lewe, a prawa
tak, jakby miał wiązanie prawe.

Dla działania łącznego (np. dodawania) nie ma znaczenia, czy
przetwarzamy od lewej czy od prawej strony, więc oba wyrażenia
złożenia (lewe i prawe) zwrócą ten sam wynik.  Jeżeli jednak działanie
nie jest łączne, to trzeba wybrać właściwą wersję wyrażenia.  W
przykładzie niżej odejmowanie nie jest łączne i ma wiązanie lewe, więc
powinniśmy użyć lewego wyrażenia złożenia.

```cpp
{% include_relative unary_left.cc %}
```

Przykład poniżej pokazuje konieczność użycia prawego wyrażenia:

```cpp
{% include_relative unary_right.cc %}
```

## Wersja dwuargumentowa

Wersje dwuargumentowe wymagają drugiego argumentu, którym jest
wyrażenie inicjalizujące `A`.

* wersja lewa `(A op ... op E)` -> ((A op E<sub>1</sub>) op ...)

* wersja prawa `(E op ... op A)` -> (... op (E<sub>n</sub> op A))

Strumienie wejścia-wyjścia są często wyrażeniem inicjalizującym
dwuargumentowego wyrażenia złożenia, jak w przykładzie niżej.
Wyrażenie musi być lewe, bo:

* pierwszym argumentem operatora przekierowania (`>>` czy `<<`) jest
  strumień (wejściowy czy wyjściowy),

* operator przekierowania zwraca strumień, który otrzymał jako pierwszy
  argument,

* strumień zwracany przez wyrażenie przekierowania staje się pierwszym
  argumentem kolejnego wyrażenia przekierowania.

```cpp
{% include_relative binary_left.cc %}
```

Oto przykład z prawym wyrażeniem:

```cpp
{% include_relative binary_right.cc %}
```

## Z dwuargumentowego do jednoargumentowego

Jeżeli dodalibyśmy wyrażenie `A` na początek paczki, to moglibyśmy
skorzystać z jednoargumentowego wyrażenia złożenia, ale byłoby to
niewygodne i mniej ekspresywne, jak pokazano niżej:

```cpp
{% include_relative force_unary.cc %}
```

## Krótki a trudny przykład: lista oddzielona przecinkami

Przykład niżej używa operatora przecinka, który jest nietypowy,
ponieważ łączy dwa niezależne wyrażenia.  Łączone wyrażenia nie mają
ze sobą nic wspólnego i są opracowywane niezależnie.  Przecinek
gwarantuje jedynie, że pierwsze będzie wykonane pierwsze wyrażenie,
zatem nawiasy z drugiego wyrażenia nie mogą mieć wpływu na kolejność
wykonania pierwszego wyrażenia.  W poniższym przykładzie, nawiasowanie
nie ma wpływu na wynik, ponieważ kolejność opracowania wyrażeń z
operatorem `<<` ustalają przecinki.

```cpp
{% include_relative comma.cc %}
```

Przykład niżej używa wersji lewej, gdzie `E` to `(std::cout << ", " <<
p)` a operatorem jest przecinek.  Jeżeli paczka `p` jest pusta, to
wyrażenie złożenia jest puste.  Jeżeli `p` ma jeden parametr, to
kompilator dokooptowuje dodatkowy pusty parametr, jeżeli taki istnieje
(dla operatora `,` jest nim `void()`), bo `op` wymaga dwóch
argumentów.  Żeby na początku nie wypisać samego przecinka, to
pierwszy parametr wypisujemy poza paczką (tak, jak w przetwarzaniu
rekurencyjnym), a wypisanie każdego parametru z paczki jest
poprzedzone wypisaniem przecinka.

```cpp
{% include_relative complex.cc %}
```

# Podsumowanie

* Szablon wariadyczny przyjmuje dowolną liczbę argumentów.

* Paczka parametrów jest używana w rozwinięciach albo w wyrażeniach
  złożenia.

* Wariadyczne mogą być listy:

  - dziedziczenia i inicjalizacji,

  - parametrów szablonu i argumentów szablonu,

  - parametrów funkcji i argumentów funkcji.

# Quiz

* Czy paczka parametrów szablonu może przyjąć argumenty różnego
  rodzaju?

* Czy paczka parametrów może być pusta?

* Co to jest wyrażenie złożenia?
