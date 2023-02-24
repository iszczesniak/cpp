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

Generic programming in C++ is supported by templates and overloading.
With templates we can use and implement without the loss of
efficiency:

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
`#include <array>` added) or `deque` (with `#include <deque>` added).
At compile-time, the `sort` function template is instantiated
(compile-tailored) for the type of the structure, and the type of the
structure elements used.

**Generic programming** can operate on data that are not objects,
e.g., C-style arrays, and so it is more general than object-oriented
programming (that works with objects only).  We can change the above
example, so that it works not only with containers (which are
objects), but with C-style arrays too: we replace the calls to member
functions `begin` and `end` with non-member function templates
`std::begin` and `std::end`:

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

But that example doesn't work for type `list`.  The compiler produces
a lengthy error message that's hard to decipher.  The problem is the
list iterator is not random access, i.e., we cannot increase the
iterator by an arbitrary number: `list{3, 2, 1}.end() + 2` does not
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
albeit the code might be harder to write.

In the simple examples below we check whether the abstraction
mechanisms introduce any performance overhead.  Each of these programs
writes to the standard output numbers 1 and 2.  We are interested in
the assembly code.

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

<!-- LocalWords: lvalue lvalues rvalue -->
