---
title: Templates
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
  or take more memory, because it was generically programmed; we want
  our code to run as fast as when it's meticulously manually crafted.

Generic programming in C++ is supported by templates.  With templates
we can use and implement without the loss of efficiency:

* generic data structures, most notably the containers of the standard
  library, e.g., `std::vector`,

* generic algorithms, most notably the algorithms of the standard
  library, e.g., `std::sort`.

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

# Performance

<!-- LocalWords: lvalue lvalues rvalue -->
