---
title: Templates
---

# Templates

A template can be of a:

* function,

* class, struct, union,

* member (a member function, a member field),

* type alias,

* variable.

A template declaration or definition begins with the `template`
keyword, and it has this syntax:

```cpp
template <parameter list>
```

We say a template is *parametrized*, because it has parameters that we
call **template parameters**.  A template parameter is defined in the
parameter list (`parameter list` above) and has a name, that we then
use in the template declaration or definition.

When we use a template (e.g., we call a function defined with a
template), then after the template name we can provide **template
arguments** in `<>`.  **Instantiation** of a template **substitutes**
a template argument for a template parameter.  We also say that a
parameter accepts an argument.

The terms of a template parameter and a template argument are
analogous to the terms of a **function parameter** and a **function
argument**, but this analogy is only skin-deep.  Initialization of a
function parameter with a function argument has many details (e.g.,
type conversion, reference initialization), that do not apply to
substitution.  Substitution only checks whether the argument is valid,
i.e., that it is a type, a value or a type template, as stipulated by
the **parameter kind**.  Bottom line: **substitution is not
initialization**.

# Template parameters

Template parameters are defined in a parameter list, where they are
comma-separated.  A parameter is defined by a kind and an optional
name.  There are three kinds: type, value, and template.  The example
below has three parameters: `T` of the type kind, an unnamed parameter
of the value kind, and `C` of the template kind.

```cpp
template <typename T, int, template<typename> typename C>
```

## Type parameter

The template parameter of the type kind in short we can call the type
template parameter.  It's the most common kind.  We define a type
parameter with `typename T`, where `typename` says it's a type
parameter, and `T` is the name of the parameter.  We can also define
equivalently a type parameter with `class T`, but `typename T` is
preferred in modern C++.

Instantiation can substitute `T` with any concrete type: a built-in
type (e.g., `int`), a user-defined type (e.g., `A`), a template type
(e.g., `vector<int>`), even `void`.  Concrete, meaning not a type
template.  `T` doesn't have to meet any requirements, e.g., inheriting
from an interface class.  The requirements on type `T` follow from how
we use the type in the template definition, i.e., whether we, e.g.,:

* default-construct a value of type `T`,

* add, using `operator+`, the values of type `T`,

* dereference, using `operator&`, a value of type `T`,

* pass to some function, e.g., `push_back`, a value of type `T`,

* output to `std::ostream` a value of type `T` using `operator<<`.

This is an example of a function template with a type parameter, where
the compiler is able to **deduce the template argument**, so that we
do not have to provide it explictly when calling the function:

```cpp
{% include_relative print1.cc %}
```

## Value parameter

Also known as the non-type parameter.  A parameter of this kind we
define with `some_type I`, where `some_type` is a type, e.g., `int`.
Type `some_type` cannot be any, only some types allowed, with integer
types being the most popular.  Instantiation substitutes the parameter
name with a value of type `some_type`, e.g., `1` for a template
parameter defined as `int I`.

An example definition of a value template parameter:

```cpp
template <int N>
```

This is an example of a function template with a value parameter `N`
whose argument must be explicitly provided because a compiler is
unable to deduce it:

```cpp
{% include_relative print2.cc %}
```

Here we have two overloads of function templates (overloads because
they have the same name).  The second template has a value parameter
`N` and a type parameter `T` whose argument can be deduced:

```cpp
{% include_relative print3.cc %}
```

This is an example of a recursive function template, where the
recursion is terminated by the compile-time conditional statement `if
constexpr`:

```cpp
{% include_relative print4.cc %}
```

Among the allowed types for value parameters are function pointers and
references:

```cpp
{% include_relative callback.cc %}
```

## Template parameter

A template paramter of the template kind accepts (as its argument) a
type template of the required interface.  It's also known as the
*template template parameter*.  The definition of the template
parameter `T` defines (with the parameter list `parameter-list`) the
interface of the acceptable type templates:

```cpp
template <parameter-list> typename T
```

Here we use parameter `T`:

```cpp
template <template <parameter-list> typename T>
```

In this example, the template parameter `C` accepts only a template
type that, in turn, accepts a type argument and the value argument:

```cpp
{% include_relative template1.cc %}
```

A compiler (Clang, GCC) replaces `__PRETTY_FUNCTION__` with the
function name and the template arguments, so that we can examine how
the function template was instantiated.

A template parameter allows to deduce the arguments of the
instantiated template type:

```cpp
{% include_relative template2.cc %}
```

A template parameter breaks circular dependency between template
types:

```cpp
{% include_relative circular.cc %}
```

# Template arguments

Arguments can be:

* deduced by a compiler (most frequenlty used),

* explicitly given by a programmer (sometimes indispensable),

* defaulted by a programmer (sometimes useful).

This example demonstrates the above functionality:

```cpp
{% include_relative intro.cc %}
```

Before we get to deduction, first we discuss the explicit and default
template arguments.

<!-- LocalWords: lvalue lvalues rvalue -->
