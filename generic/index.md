---
title: Generic programming
---

# Introduction

*Alexander Stepanov*, one of the founding fathers of generic
programming, wrote in his book "From Mathematics to Generic
Programming":

> Generic programming is an approach to programming that focuses on
> designing algorithms and data structures so that they work in the
> *most general setting without the loss of efficiency*.

Key are:

* **the most general setting**: it's not only about being able to
  choose the type we work with (e.g., `int` or `double`), but also the
  data structure (e.g., `std::vector` or `std::list`),

* **no loss of efficiency**: we don't want our program to run slower
  or take more memory because it was generically written; we want our
  code to run as fast as when it's meticulously manually crafted.

## The most general setting

Generic programming in C++ is supported by templates.  With templates
we can use and implement without the loss of efficiency:

* generic data structures, most notably the containers of the standard
  library, e.g., `std::vector`,

* generic algorithms, most notably the algorithms of the standard
  library, e.g., `std::sort`.

The example below shows how we can use containers and algorithms of
the standard library.  This example needs a C++17 compiler.

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

In the above example we can change the type of the sorted numbers from
`int` to `double`: it's enough to change type `vector` to
`vector<double>` (i.e., to give argument `double` to template type
`vector`).  We can change type `vector` to `array` (with
`#include <array>` added) or `deque` (with `#include <deque>` added).  At
compile-time, the `sort` function template is instantiated
(compile-tailored) for the type of the structure, and the type of the
strcture elements used.

**Generic programming** can operate on data that are not objects,
e.g., C-style arrays, and so it is more general than object-oriented
programming (that works with objects only).  We can change the above
example, so that it works not only with containers (which are
objects), but on with C-style arrays too: we replace the calls to
member functions `begin` and `end` with non-member function templates
`std::begin` and `std::end`:

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

But that example doesn't work for type `list`.  The compiler produces
a lengthy error message that's hard to decipher.  The problem is the
list iterator is not random access, i.e., we cannot increase the
iterator by an arbitrary number: `list{3, 2, 1}.end() - 2` does not
compile.  Iterator is random access if the structure has the random
access operator `operator[]`, and `list` doesn't have it.

The real problem is the poor diagnostics.  We should have received an
error message that function `sort` expects random access iterators.
C++20 introduced concepts that would allow for proper error messages,
but that functionality has yet to be implemented in the standard
library implementations (e.g., GCC).

## No loss of efficiency

For the C++ Standard Committee, the time and memory efficiency is the
priority, and the ease of language use comes second.  Therefore the
program that uses the abstraction mechanisms (e.g., templates) must
work as fast as possible (i.e., as fast as the hand-crafted code),
albeit the code might be difficult to write.

In the simple examples below we check whether the abstraction
mechanisms introduced any performance overhead.  Each of these
programs writes to the standard output numbers 1 and 2.  We are
interested in the assembly code.

This is the baseline code, i.e., to this code we compare the others
(`test_baseline.cc`):

{% highlight c++ %}
{% include_relative test_baseline.cc %}
{% endhighlight %}

This example uses templates (`test_template.cc`):

{% highlight c++ %}
{% include_relative test_template.cc %}
{% endhighlight %}

We compile both examples to the assembly code (we can use the Compiler
Explorer too) and we look for differences (`c++filt` can come useful
too):

```
g++ -O2 -std=c++17 -S test_baseline.cc test_template.cc
meld test_baseline.s test_template.s
```

There are no differences.  Using a function template does not
deteriorate performance: the second example is as fast as the baseline
example.

In that example, as the assembly language shows, the parameters of a
template function are not initialized (copied, specifically) based on
the call arguments, even though they are passed by value.  In the C
language, a function that accepts arguments by value (neither by
pointer, nor by reference as it doesn't exist in C) always has its
parameters initialized based on call arguments, and that brings
performance down.

A regular (non-template) function can be inlined too:

{% highlight c++ %}
{% include_relative test_function.cc %}
{% endhighlight %}

A tuple (`std::tuple`) also doesn't introduce overhead.  Type `tuple`
is a templated structure, so it has a constructor and destructor but
they are empty.  Here's an example:

{% highlight c++ %}
{% include_relative test_tuple.cc %}
{% endhighlight %}

Even iterating over the elements of `std::array` doesn't introduce any
overhead:

{% highlight c++ %}
{% include_relative test_foray.cc %}
{% endhighlight %}

Instantiation allows for better optimization:

{% highlight c++ %}
{% include_relative divide.cc %}
{% endhighlight %}

# Object vs generic programming

C++ is multiparadigm: object-oriented, structural, procedural,
functional and generic.  Generic and object programming are
complementary, not mutually exclusive.

We implement complex types as a structure, and their specific
operations as member functions -- that's a typical example of
object-oriented programming.  Operations (algorithms) are best
implemented as non-member functions (aka free-standing, global or
namespace functions), so that they can be overloaded for any type, not
only class types -- and that's a typical example of generic
programming.

We often need to implement different functionality for different
types.  Generic programming and object-oriented programming use
polymorphism to this end, but of different kind:

* In **generic programming** we use non-member functions and their
  abstraction mechanisms: overloading and templates.  In
  *compile-time*, for the given call expression, the compiler chooses
  a function template or an overload depending on the type and
  category of call arguments.  This way of choosing an implementation
  is called **static polymorphism** (aka *compile-time polymorphism*).
  *Static polymorphism does not introduce overhead at run-time.*

* In **object-oriented programming** we use the interface of a base
  class and virtual functions.  In *run-time*, when calling a virtual
  function for a given object, an implementation of a virtual function
  is chosen depending on the type of the object.  This way of choosing
  an implementation is called **dynamic polymorphism** (aka *run-time
  polymorphism*). *Dynamic polymorphism introduces performance
  overhead because calling a virtual function requires an indirect
  call using a virtual function table.*

Generic programming works with any types, while object-oriented
programming for class types only, e.g., `1.foo()` would not compile.

## An example of static polymorphism

In the example below we use static polymorphism implemented with
function overloading.  These overloads have some identical code
(`std::cout << "Function foo:";` and `std::cout << std::endl`), and
some extra code depending on the parameter type (e.g., `std::cout <<
i;` for integers).

{% highlight c++ %}
{% include_relative generic1.cc %}
{% endhighlight %}

Below we use a function template, where the identical code from the
example above appears once.  The function template uses operator `<<`
that is overloaded for various types.  We still rely on overloading,
as in the example above, but for the `operator <<` only, which we
could use in other parts of code.  We could say that function `foo`
now is generic.

{% highlight c++ %}
{% include_relative generic2.cc %}
{% endhighlight %}

## An example of object-oriented programming

The same functionality we could implement using dynamic programming.
However, the assembly code is much more complicated, because of the
call to a virtual function.

# Conclusion

Generic programming:

* shortens and better organizes the source code,

* offers static polymorphism,

* rules in the standard library.

# Quiz

* Does the generic programming in C++ suffers from performance loss?

* What's the difference between the static and dynamic polymorphism?

* What data types can we use in generic programming?

<!-- LocalWords: lvalue lvalues rvalue -->
