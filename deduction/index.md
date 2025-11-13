---
title: Template argument deduction
---

# Introduction

Template arguments are deduced for our convenience, so that we do not
have to provide them explicitly (and possibly make a mistake).  A
compiler deduces template arguments in the following cases:

* a call to a non-member template function (the most frequent),

* a call to a member template function (including a constructor),

* an initialization of a variable of type `auto` (including a function
  parameter and a return value).

# Deduction basics

We discuss the deduction using a non-member function template.  To
call a **template function**, a compiler has to instantiate a
**function template**, i.e., produce the code of a template function
based on the function template and its arguments.

A compiler deduces template arguments (of a function) based on:

* **types** of function parameters,

* **types** and **categories** of function arguments.

How an argument category affects deduction is quite complex, and
therefore is described in a separate topic on perfect argument
forwarding.

## The simplest case

In the simplest case we call a function with a single parameter:

```cpp
template <parameter list>
void
foo(ParameterType t)
{
  // Body of a function template.
}

int
main()
{
  foo(expr);
}
```

A compiler is supposed to deduce arguments for parameters (defined in
`parameter list`) of function template `foo` based on expression
`expr` and type `ParameterType` of parameter `t` of function `foo`.
To talk about deduction, type `ParameterType` must depend on (use in
its definition) at least one template parameter.  There are many ways
type `ParameterType` can depend on template parameters, and we discuss
the most important.

## The basic rule, no conversion

**Rule: the deduced argument should allow for the initialization of
the function parameter.**

A parameter is always initialized with an argument, either explicit or
default.

**No conversion: initialization without type conversion.**

We mean the conversion from the type of function argument `expr` to
type `ParameterType` of a function parameter.  Let's note that such
type conversions are allowed for regular (non-template) functions.

The initialization of parameter `t` in the above simplest case looks
like this:

```cpp
ParameterType t = expr;
```

A compiler must deduce arguments for template parameters used in the
definition of type `ParameterType`, so that the initialization of a
function parameter is possible without type conversion.  Deduction may
turn out impossible, making instantiation impossible.

## Examples

If `ParameterType` is a reference type to a const value of type `T`,
where `T` is a template parameter, and the function argument is `1`,
then the initialization looks like this:

```cpp
const T &t = 1;
```

The deduced type is `T = int`, because the initialization is possible
without type conversion.

However, if `ParameterType` is a reference type to a non-const value
of type `T`, then the initialization looks like this:

```cpp
T &t = 1;
```

The deduced type is still `T = int`, because an rvalue of a
fundamental type (literal `1`) is of a non-const type (so the standard
says).  Therefere instantiation cannot succeed, because non-const
lvalue reference `t` cannot be initialized with an rvalue.

## Note: "no conversion"

There is something wrong with the "no conversion" in the above
examples: `ParameterType` is **`const int &`** (or **`int &`**), while
expression `1` is of type **`int`**!  Aren't they supposed to be the
same?  No: function parameter type `ParameterType` and the type of
argument `expr` can differ with the top-level qualifiers and
declarator `&`, which follows from how variables can be initialized,
as discussed below.

# Top-level

The place of a qualifier or a declarator in a defined type affects:

* initialization of a value of this type,

* function overloading depending on the parameter of this type.

Type qualifiers and declarators can be top-level.

## Declarators

Declarators `*` of a pointer type and `&` of a reference type can be
used in various places in a defined type.  **A top-level qualifier**
is the first one from the right.  For instance, for type `int * const
&` the top-level qualifier is `&`.

## Qualifiers

Type qualifiers (`const` and `volatile`) can be **top-level** for any
type except a reference type.

### Regular type

The defined type (non-pointer, non-reference) can have a qualifier
given either before or after the used type.  There are no other places
for a qualifier, and the place makes no difference.  Qualifiers of a
regular type are called top-level, even though they can't be
lower-level.  For instance, `const int` and `int const` define the
same type, and `const` we call a top-level qualifier.

Those qualifiers matter only during compilation (not at run time): a
compiler cannot allow a data of a `const` type to be modified, and
should not optimize the access to the data of a `volatile` type.

**Leeway.** We can initialize a variable with an initializing
expression, even if their (regular) types differ with (top-level)
qualifiers, because it's about copying a value.  For example:

```cpp
{% include_relative cv_regular1.cc %}
```

This leeway applies to the initialization of a function parameter with
a function argument, which yields the following limitation.

**Limitation.** We cannot overload a function depending on the
qualifiers of a regular type (of a function parameter), because the
initialization of a parameter of a regular type (where the leeway puts
no requirements on the qualifiers) is unable to affect overload
resolution.

These qualifiers (that are an implementation detail of a function
body) do not matter for a caller and so they are removed by a compiler
from a function signature (as they are not part of a function
interface) to enable linking.  Please check (using `nm`) the function
signatures in the symbol table of the following program.

```cpp
{% include_relative cv_regular2.cc %}
```

### Pointer type

The top-level qualifiers of a pointer type are located on the right of
the top-level `*` declarator, i.e., at the end of the type definition
(or at the beginning, reading from the right as we should).  They
qualify a type of a pointer variable, not the type of the data pointed
to.

Just like a variable of a regular type, we can initialize a variable
of a pointer type using a value whose (pointer) type differs with the
top-level qualifiers, because the value is copied.  And therefore we
cannot overload a function depending on the pointer types (of a
function parameter) that differ with the top-level qualifiers.  Here's
an example:

```cpp
{% include_relative cv_ptr1.cc %}
```

In a pointer type, on the left of the `*` top-level declarator, we can
put the *top-level* qualifiers of the type pointed to.  We can call
these qualifiers **lower-level**, if we talk about the pointer type.

**A requirement for a pointer type.** *Lower-level* qualifiers of a
pointer type must include the *top-level* qualifiers of the type
pointed to.

Here's an example:

```cpp
{% include_relative cv_ptr2.cc %}
```

Ten warunek pozwala przeciążać funkcje dla typów wskaźnikowych
(parametru funkcji), które różnią się kwalifikatorami dla typu
wskazywanych danych.  Chodzi o możliwość przeciążenia pod względem
typu danych, do których odnosi się wskaźnik.  Oto przykład:

```cpp
{% include_relative cv_ptr3.cc %}
```

### Typ referencyjny

Referencja albo nazywa pewną daną (np. element tablicy) albo jest
aliasem innej zmiennej.  Typ referencyjny nie ma kwalifikatorów
najwyższego rzędu, bo referencja ma wiernie odwzorować typ danej,
której jest aliasem: wyrażenie referencyjne jest zamieniane na
wyrażenie z tą daną, do której referencja się odnosi.  Co więcej,
referencję można tylko zainicjalizować, a potem już nie można jej
zmienić, żeby była aliasem innej danej, a kwalifikator `const`
najwyższego rzędu nie robiłby różnicy.  Tak więc, na przykład, typ
`int & const` jest niedopuszczalny.

Dlatego nie da się przeciążać funkcji dla typów referencyjnych
(parametru funkcji), które miałyby się różnić tylko kwalifikatorami
najwyższego rzędu.  Nawet deklaracja jednej funkcji jest niemożliwa,
jeżeli typ referencyjny jej parametru miałby mieć kwalifikator.

Podobnie jak w typie wskaźnikowym, tak i w typie referencyjnym, tuż po
lewej stronie deklaratora `&` najwyższego rzędu, możemy też podać
kwalifikatory **najwyższego rzędu** dla typu wskazywanych danych.
Kwalifikatory te możemy nazwać **niższego rzędu**, jeżeli mówimy o
typie referencyjnym.

**Warunek dla typu referencyjnego.** Kwalifikatory *niższego rzędu*
typu referencyjnego muszą zawierać kwalifikatory *najwyższego rzędu*
typu wskazywanych danych.

Oto przykład:

```cpp
{% include_relative cv_ref1.cc %}
```

Ten warunek pozwala przeciążać funkcje dla typów referencyjnych
(parametru funkcji), które różnią się kwalifikatorami dla typu
wskazywanych danych.  Chodzi o możliwość przeciążenia pod względem
typu danych, do których odnosi się referencja.  Oto przykład:

```cpp
{% include_relative cv_ref2.cc %}
```

# Typ wyrażenia

Każde wyrażenie w C++ jest typu niereferencyjnego, a więc i typ
argumentu funkcji jest niereferencyjny, nawet jeżeli wyrażeniem jest
nazwa referencji.  W standardzie napisano ([expr.type]), że kompilator
usuwa deklarator `&` najwyższego rzędu z typu wyrażenia przed jego
dalszym opracowaniem.

# Wnioskowanie typowego argumentu szablonu

Dla każdego **rodzaju** parametru szablonu, kompilator może wnioskować
argument.  Najczęściej chcemy, żeby kompilator wnioskował typowe (w
tym szablonowe) argumenty.

Typowy argument szablonu jest wnioskowany dla typowego parametru
szablonu.  To wnioskowanie jest najbardziej złożone (w porównaniu do
rodzaju wartościowego czy szablonowego), bo rozróżnia:

* typ parametru funkcji, w szczególności:

  - **zwykły** (niewskaźnikowy i niereferencyjny) dla przekazywania
    przez wartość,

  - **wskaźnikowy** dla przekazywania przez wskaźnik (które jest
    po prostu przekazywaniem przez wartość),

  - **referencyjny** dla przekazywania przez referencję.

* typ argumentu wywołania funkcji, w szczególności:

  - **funkcyjny**,

  - **tablicowy**.

* kategorię argumentu (opisane w innym temacie).

W zależności od omawianych szczególnych (najważniejszych) typów
parametru funkcji (zwykłych, wskaźnikowych, referencyjnych) stosowane
są nieco różne zasady, które jednak wynikają z podstawowej zasady z
ograniczeniem.  Dla tych szczególnych typów, wnioskowany typ może
różnić się od typu argumentu wywołania funkcji wyłącznie
kwalifikatorami lub deklaratorami najwyższego rzędu.  Wnioskowanym
typem nigdy nie będzie typ referencyjny, bo argument funkcji nigdy nie
jest typu referencyjnego.

## Zwykły typ parametru funkcji

**Wywnioskowany argument szablonu jest typem argumentu funkcji z
pominięciem kwalifikatorów najwyższego rzędu.**

Chodzi o to, że inicjalizacja parametrów funkcji (przy przekazywaniu
argumentów wywołania przez wartość) kopiuje wartość argumentu
wywołania do parametru funkcji.  Wnioskowanie nie musi zadbać o
kwalifikatory typu, bo w ciele funkcji działamy na kopii.  W definicji
parametru możemy podać kwalifikatory, żeby poprosić kompilator o
pilnowanie się z tym parametrem.

Przykład:

```cpp
{% include_relative arg_type_val1.cc %}
```

Ten typ paramatru szablonu może także przyjąc argument typu
wskaźnikowego:

```cpp
{% include_relative arg_type_val2.cc %}
```

## Wskaźnikowy typ parametru funkcji

**Wywnioskowany argument szablonu jest typem argumentu funkcji z
pominięciem deklaratora `*` i kwalifikatorów *najwyższego* rzędu.
Kwalifikatory najwyższego rzędu dla *typu wskazywanych danych* też są
pomijane, jeżeli znajdują się w definicji typu parametru funkcji.**

Wyjaśnienie:

* Deklarator `*` najwyższego rzędu jest pomijany, bo on już jest w
  definicji typu parametru funkcji.

* Kwalifikatory najwyższego rzędu są pomijane, bo nie mają one
  znaczenia dla funkcji, która działa na kopii wartości argumentu
  przekazanego do niej (tak jak w przypadku zwykłego typu parametru
  funkcji).

* Jeżeli w definicji typu parametru funkcji podamy kwalifikatory
  najwyższego rzędu dla **typu wskazywanych danych**, to te
  kwalifikatory będą pominięte we wywnioskowanym typie.  Jeżeli nie
  zostały podane, to kwalifikatory (typu wskazywanych danych)
  zdefiniowane przez typ argumentu funkcji będą propagowane do
  wywnioskowanego typu, co pozwala na inicjalizację parametru funkcji.

```cpp
{% include_relative arg_type_ptr.cc %}
```

## Referencyjny typ parametru funkcji

**Wywnioskowany argument szablonu jest typem argumentu funkcji z
pominięciem tych kwalifikatorów najwyższego rzędu, które zostały
podane w definicji typu danych, do których referencyjny parametr
funkcji się odnosi.**

Chodzi o to, żeby referencyjny parametr funkcji rzeczywiście mógł być
zainicjalizowany: jeżeli typ argumentu wywołania jest stały (bądź
ulotny), to referencja musi odnosić się do danej typu stałego (bądź
ulotnego).  Pamiętajmy, że typ argumentu nigdy nie jest referencyjny.

Przykład:

```cpp
{% include_relative arg_type_ref.cc %}
```

## Przekazywanie funkcji

Funkcję możemy przekazać przez:

* referencję,

* wskaźnik,

* ale nie wartość.

Funkcję możemy przekazać przez *referencję* używając referencyjnego
typu parametru funkcji, a dokładnie typu `F &`, gdzie `F` jest typowym
parametrem szablonu.  Wywnioskowanym argumentem szablonu będzie typ
referencji na przekazywaną funkcję.  Przykład:

```cpp
{% include_relative foo_ref.cc %}
```

Funkcję możemy przekazać przez *wskaźnik* używając wskaźnikowego typu
parametru funkcji szablonowej, a dokładnie typu `F *`, gdzie `F` jest
typowym parametrem szablonu.  Wywnioskowanym argumentem szablonu
będzie typ przekazywanej funkcji.  Przykład:

```cpp
{% include_relative foo_ptr.cc %}
```

Zamianę nazwy funkcji na wskaźnik do niej nazywamy **rozpadem funkcji
na wskaźnik** (ang. decay), który pochodzi z języka C.  Z rozpadu
skorzystaliśmy wyżej podając nazwę funkcji jako argument wywołania
funkcji szablonowej.

Funkcję możemy także przekazać przez *wskaźnik* używając zwykłego
(niereferencyjnego i niewskaźnikowego) typu parametru funkcji, a
dokładnie typu `F`, gdzie `F` jest typowym parametrem szablonu.  Wtedy
wywnioskowanym argumentem szablonu będzie typ wskaźnikowy na funkcję.
Przykład:

```cpp
{% include_relative foo_reg.cc %}
```

## Przekazywanie tablic języka C

Tablicę języka C możemy przekazać do funkcji szablonowej przez:

* referencję,

* wskaźnik,

* ale nie wartość.

Tablicę możemy przekazać przez *referencję* używając referencyjnego
typu parametru funkcji szablonowej, a dokładnie typu `A &`, gdzie `A`
jest typowym parametrem szablonu.  Wywnioskowanym argumentem będzie
typ tablicy.  Przykład:

```cpp
{% include_relative car_ref.cc %}
```

Tablicę możemy przekazać przez *wskaźnik* używając wskaźnikowego typu
parametru funkcji szablonowej, a dokładnie typu `A *`, gdzie `A` jest
typowym parametrem szablonu.  Wywnioskowanym argumentem będzie typ
tablicy.  Przykład:

```cpp
{% include_relative car_ptr.cc %}
```

Jeżeli typem parametru funkcji szablonowej jest zwykły typ
(niereferencyjny i niewskaźnikowy), a argumentem wywołania funkcji
będzie nazwa tablicy, to do funkcji zostanie przekazany wskaźnik na
pierwszy element tablicy (a nie wskaźnik na tablicę), bo:

* tablica rozpadnie się (ang. decay) na wskaźnik na pierwszy element
  tablicy,

* wywnioskowanym argumentem będzie typ wskaźnikowy na element tablicy.

Oto przykład z rozpadem:

```cpp
{% include_relative car_val.cc %}
```

# Wartościowy argument szablonu

Wartościowy argument szablonu jest wnioskowany tylko na podstawie typu
argumentu wywołania funkcji, z którego można ten argument
wywnioskować.  Częścią typu argumentu wywołania funkcji musi być pewna
wartość, którą potrzebujemy, i która staje się wywnioskowanym
wartościowym argumentem.

Jedynymi typami argumentu wywołania funkcji, na podstawie których
możemy wywnioskować wartościowy argument szablonu, to:

* typ tablicy języka C,

* dowolny typ szablonowy.

## Typ tablicy języka C

Oto przykład:

```cpp
{% include_relative carray.cc %}
```

## Dowolny typ szablonowy

Typy wartościowych parametrów obu szablonów muszą się zgadzać.  Te oba
szablony to:

* szablon funkcji: wartościowy parametr tego szablonu ma wywnioskowany
  argument,

* szablon typu: tego szablonowego typu jest argument wywołania
  funkcji.

Na przykład, wartościowy parametr `I` musi mieć typ `std::size_t`, bo
takiego typu jest wartościowy parametr typu szablonowego `std::array`:

```cpp
{% include_relative array.cc %}
```

# Wiele parametrów funkcji szablonowej

W przykładach wyżej używaliśmy tylko jednego parametru funkcji
szablonowej, więc parametry szablonu mogły być użyte w co najwyżej
jednej definicji typu parametru funkcji szablonowej.  Parametrów
funkcji szablonowej może być jednak dowolna liczba, a parametr
szablonu może być użyty w dowolnej liczbie definicji typów parametrów
funkcji szablonowej.  Jak wtedy wnioskowane są argumenty szablonu?

Wtedy wnioskowanie argumentów szablonu odbywa się niezależnie dla
każdej pary parametru funkcji i argumentu wywołania.  Dla każdej pary
wnioskowane są argumenty dla parametrów szablonu, które zostały użyte
w definicji typu tego parametru funkcji.  Jeżeli jakiś argument został
wywnioskowany więcej niż raz (czyli dla różnych par), to musi on być
taki sam, w przeciwnym razie wnioskowanie nie udaje się.

Podczas wnioskowania nie jest dopuszczalna konwersja typów.  W
przykładzie niżej wnioskowane są różne argumenty, bo nie jest
dopuszczalna konwersja różnych typów argumentów wywołania funkcji.
Zatem w poniższym przykładzie wnioskowanie nie udaje się:

```cpp
{% include_relative fail.cc %}
```

# Podsumowanie

* Argument szablonu może być wywnioskowany albo podany (jawnie albo
  domyślnie).

* Wnioskowanie argumentów szablonu zależy od typu parametru funkcji i
  typu argumentu wywołania funkcji.

* Żeby zrozumieć wnioskowanie, należy znać szczegóły dotyczące
  inicjalizacji zmiennych, wskaźników i referencji.

# Quiz

* Na podstawie czego wnioskowane są argumenty szablonu?

* Czy wnioskowanie uwzględnia typ wartości zwracanej przez funkcję?

* Co to jest rozpad tablicy?
