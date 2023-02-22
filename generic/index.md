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
`vector`).  We can change type `vector` to `array` (with `#include
<array>` added) or `deque` (with `#include <deque>` added).  At
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
a lengthy error message hard to decipher.  The problem is the list
iterator is not random access, i.e., we cannot increase the iterator
by an arbitrary number: `list{3, 2, 1}.end() - 2` does not compile.
Iterator is random access if the structure has the random access
operator `operator[]`, and `list` doesn't have it.



<!-- LocalWords: lvalue lvalues rvalue -->
