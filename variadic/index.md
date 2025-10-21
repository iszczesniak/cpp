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
the pack name, e.g., `p`.  Pack `p` is made of parameters
p<sub>1</sub>, p<sub>2</sub>, ..., p<sub>(n-1)</sub>, p<sub>n</sub>.
A parameter pack can be of a template or a function.  A parameter pack
is used in a **pack expansion** or a **fold expression**.

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

# Fold expression

A fold expression (since C++17) describes how to generate a *target
(intended) expression* using any **binary operator `op`** and a
parameter pack.  A fold expression is called that way, because it
folds (like a tablecloth) the target expression (which we could write
"by hand") to a compressed format.  A fold expression is expanded,
instantiated for a given parameter pack, and that can replace
recursive processing.  We recognize the fold expression by the
ellipsis and parentheses.  There are four versions: two unary, and two
binary, that use the same binary (that requires two operands) operator
`op`.

Part of a fold expression is expression `E` that uses pack `p`.  A
fold expression is expanded by instantating expression `E` for the
subsequent parameters of pack `p`.  Expression `E` for parameter
p<sub>i</sub> is denoted by E<sub>i</sub>.  We denote expression `E`
instantiated for parameter p<sub>i</sub> by E<sub>i</sub>.

## Unary versions

The unary versions require one expression `E` and operator `op`.  They
are expanded something like this:

E<sub>1</sub> op E<sub>2</sub> op ... op E<sub>(n-1)</sub> op
E<sub>n</sub>

The result of the above expression depends on the associativity of
operator `op`, because the direction in which subexpressions with
operator `op` (e.g., E<sub>1</sub> op E<sub>2</sub>) are evaluated is
given by the associativity of operator `op`: either from left to right
for the left-to-right associativity, or from right to left for the
right-to-left associativity.

For an associative operation (e.g, addition), the direction doesn't
matter as the result is the same.  If the operation is not
associative, the direction matters.  Check this out: 3 - 2 - 1 is
evaluated from left to right: (3 - 2) - 1 = 0, and not from right to
left: 3 - (2 - 1) = 2.  Conclusion: operator `-` must have the
left-to-right associativity (even though it's not associative).

There is no fold expression that would be expanded as show above, so
that a compiler evaluates the subexpressions in the direction given by
the associativity of operator `op`.  There are, however, two versions
(of a unary fold expression) that impose the direction:

* the left version: `(... op E)` expended to ((E<sub>1</sub> op
  E<sub>2</sub>) op ...)

* the right version: `(E op ...)` expended to (... op
  (E<sub>(n-1)</sub> op E<sub>n</sub>))

Therefore:

* the left version evaluates the subexpressions from left to right, as
  though the operator `op` had the left-to-right associativity,

* the right version evaluates the subexpressions from right to left,
  as though the operator `op` has the right-to-left associativity.

For an associative operation, both versions yield the same result.
However, if an operation is not associative, then we have to choose
the proper version, depending on the associativity of operator `op`.
In the following example, subtraction is not associative and has the
left-to-right associativity, so we have to use the left version of the
unary fold expression.

```cpp
{% include_relative unary_left.cc %}
```

In the example below we have to use the right version:

```cpp
{% include_relative unary_right.cc %}
```

## Binary version

The binary versions require an initializing expression `A` that is the
second argument.  A compiler differentiates arguments `A` and `E` by
the parameter pack.  There are two versions:

* the left version: `(A op ... op E)` expanded to ((A op
  E<sub>1</sub>) op ...)

* the right version: `(E op ... op A)` expanded to (... op
  (E<sub>n</sub> op A))

Input-output streams are commonly the initializing expression of a
binary fold expression with the stream insertion (`<<`) or extraction
(`>>`) operators, for which we have to use the left version because:

* the left operand of a stream operator (`>>` or `<<`) is an input or
  output stream,

* a stream operator returns the stream that it accepted as its left
  operand,

* a stream returned by a stream operator becomes the left operand of
  another stream operator.

Here's an example:

```cpp
{% include_relative binary_left.cc %}
```

Here's an example with the right version:

```cpp
{% include_relative binary_right.cc %}
```

## From binary to unary

A binary fold expression is handy and expressive, but we could do
without it: we can add expression `A` to the parameter pack and use
the unary fold expression.  We add either at the front of the pack to
use the left version or at the back to use the right version.  The
example below uses the stream operators, so we have to use the left
version.

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
