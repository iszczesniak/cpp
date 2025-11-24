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

## The basic rule without type conversion

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
put the *top-level* qualifiers for the type pointed to.  We can call
these qualifiers **lower-level**, if we talk about the pointer type.

**A requirement for a pointer type.** The *lower-level* qualifiers of
a pointer type must include the *top-level* qualifiers of the type
pointed to.

Here's an example:

```cpp
{% include_relative cv_ptr2.cc %}
```

That requirement allows to overload functions depending on the pointer
types (of a function parameter), that differ with qualifiers for the
data pointed to.  It's about being able to overload for the data types
pointed to.  Here's an example:

```cpp
{% include_relative cv_ptr3.cc %}
```

### Reference type

A reference either names some data (e.g., a temporary, a table
element) or is an alias to some other variable.  A reference type does
not have qualifiers, because it's supposed to represent verbatim its
initializing expression.  What's more, a reference can only be
initialized, and later cannot be changed (so that it names some
different data), so a `const` top-level qualifier would make no
difference.  For instance, type `int & const` is wrong.

Therefore a function cannot be overloaded for reference types (of a
function parameter), that would differ with the top-level qualifiers.
It's just impossible: we cannot declare a function with a parameter of
a cv-qualified reference type.

Just as for a pointer type, for a reference type too, on the left of
the top-level `&` declarator, we can put the *top-level* qualifiers
for the type refered to.  We can call these qualifiers *lower-level*,
if we talk about the reference type.

**A requirement for the reference type.** The *lower-level* qualifiers
of a reference type must include the *top-level* qualifiers of the
type refered to.

Oto przykład:

```cpp
{% include_relative cv_ref1.cc %}
```

That requirement allows to overload functions depending on the
reference types (of a function parameter), that differ with qualifiers
for the data refered to.  It's about being able to overload for the
data types refered to.  Here's an example:

```cpp
{% include_relative cv_ref2.cc %}
```

# Expression type: never reference!

**Every expression in C++ is of non-reference type, and so the type of
a function argument is non-reference, even if the expression is a
reference name.  The standard says ([expr.type]), that a compiler
removes the top-level `&` declarator from the expression type before
the expression is further evaluated.**

# Deduction

For every kind of a template parameter, a compiler can deduce
arguments.  We usually want the compiler to deduce arguments of the
type kind.

## The type kind

A template argument of a type kind is deduced for a template parameter
of a type kind.  This deduction is the most complex (in comparison
with the value and template kinds), because it considers:

* the type of a function parameter, that can only be:

  - **regular** (non-pointer and non-reference) for passing by value,

  - **pointer** for passing by pointer (that is just passing by
      value),

  - **reference** for passing by reference;

* the type of a function argument, especially when the argument is:

  - a **function**,

  - an **array**;

* the category of a function argument (discussed in a later topic).

Depending on the function parameter type (regular, pointer, reference)
different deduction rules are used (which follow from the basic rule
without type conversion), where the deduced type can differ from the
function argument type only with the top-level qualifiers and
declarators. **The deduced type is never a reference type, because a
function argument is never of a reference type.**

### A regular type of a function parameter

**Rule.  The deduced template argument is the type of the function
argument with the top-level qualifiers dropped.**

It's about the value of a function argument being copied to a function
parameter (when passing by value).  Deduction doesn't have to care
about the (top-level) type qualifiers, because in the function body we
work with a copy.  In the parameter definition we can put (top-level)
qualifiers to have a compiler watch over this parameter.

Example:

```cpp
{% include_relative arg_type_val1.cc %}
```

Defining a function parameter this way (that looks regular), we can
pass an argument of a pointer type, because the deduced type will be
pointer:

```cpp
{% include_relative arg_type_val2.cc %}
```

### A pointer type of a function parameter

**Rule.  The deduced template argument is the type of the function
argument with the top-level declarator `*` and qualifiers dropped.
Top-level qualifiers for *the type pointed to* are also dropped if
they are present in the type definition of a function parameter.**

Explanation:

* Top-level declarator `*` is dropped, because it's already present in
  the type definition of the function parameter.

* Top-level qualifiers are dropped, because they have no meaning for
  the function that works on a copy of an argument value (just as for
  a function parameter of a regular type).

* If in the type definition of a function parameter we put top-level
  qualifiers for the *type pointed to*, then these qualifiers will be
  dropped in the deduced type.  If we didn't put them, then the
  qualifiers (for the type pointed to) defined by the type of the
  function argument will be propagated to the deduced type, so that a
  parameter can be initialized.

```cpp
{% include_relative arg_type_ptr.cc %}
```

### A reference type of a function parameter

**Rule.  The deduced template argument is the type of the function
argument with those top-level qualifiers dropped that have been put as
top-level in the definition of the data type that a reference
parameter refers to.**

It's about making the initialization of a reference parameter
possible: if the type of a function argument is const (or volatile),
then a reference must refer to the cost (or volatile) data.  Let's
recall that a function argument is never of a reference type.

Przykład:

```cpp
{% include_relative arg_type_ref.cc %}
```

### Passing a function

We can pass a function by:

* reference,

* pointer,

* but not by value.

We can pass a function by *reference* to a function template using the
reference type of a function parameter, i.e., `F &`, where `F` is a
template parameter of the type kind.  The deduced template argument is
the type of the function passed.  Example:

```cpp
{% include_relative foo_ref.cc %}
```

We can pass a function by *pointer* to a function template using a
pointer type of a function parameter, i.e., type `F *`, where `F` is a
template parameter of the type kind.  The deduced template argument is
the type of the function passed.  Example:

```cpp
{% include_relative foo_ptr.cc %}
```

From the C language: a function name can **decay** to a pointer to the
function.  The decay takes place in the example above, where a
function name is an argument of a call.  A function name does not
decay, if the function is passed by reference.

We can pass a function by *pointer* to a function template using a
regular (non-reference and non-pointer) type of a function parameter,
i.e., `F`, where `F` is a template parameter of the type kind.  Then
the deduced template argument is the pointer type to the function
passed, because the function name decays to a pointer.  Let's note
that it's not passing a function by value, because there is no such
thing.  Example:

```cpp
{% include_relative foo_dcy.cc %}
```

### Passing an array

We can pass an array by:

* reference,

* pointer,

* but not by value.

We can pass an array by *reference* to a function template using the
reference type of a function parameter, i.e., `A &`, where `A` is a
template parameter of the type kind.  The deduced template argument is
the type of the array passed.  Example:

```cpp
{% include_relative car_ref.cc %}
```

We can pass an array by *pointer* to a function template using the
pointer type of a function parameter, i.e., `A *`, where `A` is a
template parameter of the type kind.  The deduced template argument is
the type of the array passed.  Example:

```cpp
{% include_relative car_ptr.cc %}
```

If the type of a function parameter in a function template is regular
(non-reference and non-pointer), and the function argument is the
array name, then a poiner to the first array element (and not a
pointer to the array) is passed to the function, because:

* the array decays to the pointer to the first array element,

* the deduced template argument is the pointer type to an array
  element.

Here's an example with the decay:

```cpp
{% include_relative car_dcy.cc %}
```

## Wartościowy argument szablonu

The deduction of a template argument of the value kind is far easier
than of the type kind.  It's even hard to talk about deduction,
because the template argument is extracted (taken) from the type of an
argument accepted by a function that we define as the type of the
function parameter.  In the definition of a function parameter type we
use the template parameter for which an argument will be deduced.

The only types of a function argument, which can be used to deduce a
value template argument, are:

* an array type,

* a template type.

### An array type

Here's an example:

```cpp
{% include_relative carray.cc %}
```

### A template type

The types of the value parameters of both templates must agree.  These
two templates are:

* the function template: the value parameter of this template has an
  argument deduced,

* the type template: this template is used in the definition of the
  function parameter.

For instance, a value parameter `I` must be of type `std::size_t`,
because the value parameter of type template `std::array` is of that
type:

```cpp
{% include_relative array.cc %}
```

# Many function parameters

In the above examples, we used just a single function parameter, and
so a template parameter could have been used in at most one type
definition of a function parameter.  However, there can be any number
of function parameters, and a template parameter can be used in the
type definition of every function parameter.  How are then the
template arguments deduced?

Then the template arguments are deduced independently for every pair
of a parameter and an argument of a function.  For every pair, only
those arguments are deduced, whose parameters are used in the type
definition of a function parameter.  If some argument was deduced more
than once (i.e., for different pairs), then it must be the same,
otherwise deduction fails.

Deduction forbids type conversion.  In the example below, different
arguments are deduced, because the types of function arguments are
different and cannot be converted.  Therefore deduction fails in the
example below:

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
