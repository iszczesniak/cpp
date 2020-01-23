---
title: std::weak_ptr
---

# Introduction

We are guaranteed that the managed data exist as long as at least one
shared pointer to them exists.  This guarantee, however, might be more
than we need.  We might want something less: the ability to check
whether the managed data still exist, and use them safely if needed.
We might say that we want to *track the managed data* without claiming
an ownership, i.e., without requiring them to exist.

In C++, this functionality is provided by the **weak pointer**,
implemented by class template `std::weak_ptr`.  The weak pointer
functionality is coupled with the shared pointer, because the weak
pointer kind of shares the data, but not fully.  It's best to
illustrate this functionality with an example.

# Motivating example

We need a factory function, which returns a shared pointer to some
(possibly large) data.  The function should:

* create the data anew if they do not exist,

* reuse the already created data if they exist.

The factory function should track the created data without claiming
the ownership, and reuse them if needed.  Whether the data still
exists depends on the callers of the function, i.e., whether they keep
or destroy their shared pointers.

For this job we need weak pointers.  We cover some basics before we
give the implementation.

# Details

## `std::weak_ptr`

* `#include <memory>`

* A C++11 class template, where the template argument is the type of
  the tracked data.

* A weak pointer can be copied and moved, but it's not that important
  as for the unique and shared pointers.

* A weak pointer is created from a shared pointer.

* A weak pointer never destroys its managed data.

* We can produce a shared pointer from a weak pointer, if the managed
  data still exist.

* The managed data do not know they are managed, i.e., the type of the
  managed data doesn't have to be prepared in some special way, like
  deriving from some base class.

## Usage

The example below shows the basic usage:

{% highlight c++ %}
{% include_relative basic.cc %}
{% endhighlight %}

## Producing the shared poiner from a weak pointer

PROBLEM: Jak bezpiecznie użyć (bez hazadru), skoro \code{weak_ptr} nie
daje nam gwarancji, że obiekt nie zostanie zniszczony?  Taką gwarancję
daje nam \code{shared_ptr}.

Przecież bezpośrednio po uzyskaniu surowego wskaźnika obiekt może być
zniszczony.

ROZWIĄZANIE: tworzenie \code{shared_ptr} na podstawie

Robimy to tak (może rzucić wyjątek):

\code{shared_ptr<A> sp(wp);}

  \vspace{0.25 cm}

  Albo tak (obiekt sp może być \code{nullptr}):\\
  \code{shared_ptr<A> sp = wp.lock();}

## How it works

  \item Grupa obiektów \code{shared_ptr} i \code{weak_ptr} współdzielą
    jedną strukturę zarządzającą, alokowaną dynamicznie.

  \item Każdy obiekt \code{shared_ptr} i \code{weak_ptr} posiada
    wskaźnik na strukturę zarządzającą.

  \item Częścią struktury zarządzającej jest licznik odwołań tylko
    obiektów \code{shared_ptr}.

  \item Inną częścią struktury zarządzającej jest licznik odwołań
    obiektów \code{shared_ptr} i \code{weak_ptr}.

  \item Kiedy licznik odwołań \code{shared_ptr} wyniesie 0, obiekt
    zarządzany jest niszczony.

  \item Kiedy licznik odwołań \code{shared_ptr} i \code{weak_ptr}
    wyniesie 0, struktura zarządzająca jest niszczona.

# The implementation of the motivating example

Here's the implementation:

{% highlight c++ %}
{% include_relative factory.cc %}
{% endhighlight %}

## Parallel usage

Just as for a shared pointer, you can create, copy, move and destroy a
weak pointer, and also create a shared pointer from a weak pointer,
thread-safe.  However, writing to the managed data requires
synchronization between threads.

## Performance

\item Obiekt \code{weak_ptr} zajmuje dwa razy więcej pamięci niż
    surowy wskaźnik, bo zawiera dwa pola:
    \begin{itemize}
    \item wskaźnik na zarządzany obiekt,
    \item wskaźnik na strukturę zarządającą.
    \end{itemize}

\item Po co wskaźnik na zarządzany obiekt, skoro i tak użytkownik
    nie ma do niego dostępu?  Bo potrzebny jest przy tworzeniu obiektu
    \code{shared_ptr}.

\item Wskaźnik na zarządzany obiekt mógłby być częścią struktury
    zarządzającej, ale wtedy dla obiektów \code{shared_ptr} odwołanie
    do obiektu zarządzanego byłoby wolniejsze (bo byłoby dodatkowo
    pośrednie).

# Conclusion

* A weak pointer tracks the managed data without claiming the
  ownership.

* We *always* produce a weak pointer from a shared pointer.

* We can produce a shared pointer from a weak pointer if possible,
  i.e., if the managed data exist.

* A weak pointer never destroys the managed data.

<!-- LocalWords: inlined multithreaded -->
<!-- LocalWords: performant rvalue suboptimal -->
