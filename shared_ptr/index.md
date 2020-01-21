---
title: std::shared_ptr
---

# Introduction

When we dynamically create some data (or any other resource) and use
them in other threads or parts of code, we run into the problem when
to destroy the data.  If we:

* don't destroy the data, we get a memory leak,

* destroy the data too soon, we get a race condition: a dangling
  pointer and undefined behavior, because other threads or parts of
  code still use the data,

* destroy the data too late, we get suboptimal performance, because we
  let the dispensable data linger in memory.

Therefore we should destroy the data at the right time, i.e., when
they are no longer needed.  However, this right time is hard to
pinpoint with raw pointers, because it may depend on:

* the data (i.e., their specific values),

* the timing of other threads.

The solution to the problem is the *shared-ownership semantics*:

* shared, because the data are managed by a group,

* ownership, because the data are destoryed when the group becomes
  empty.

In Java or C#, a reference has the shared-ownership semantics.

# `std::shared_ptr`

* `#include <memory>`

* The smart pointer type that implements the shared-ownership
  semantics.

* The objects of this type are the **managing objects**, and the data
  allocated dynamically is the **managed data**.

* It's a template class that implements the shared-ownership
  semantics.  The template argument is the type of the manged data.

* The opposite of `std::unique_ptr`.

* Objects of this class can be copied and moved.

* A managing object that takes the ownership of the managed data
  creates a group of managing objects.  Initially, this group has only
  one managing object.

* When we copy a managing object, we create another managing object,
  which belongs to the same group of managing objects.

* The managed data is destroyed, when the last managing object is
  destroyed.

* The managed data don't know they are managed: the type of the data
  doesn't have to be prepared to be managed, e.g., derived from some
  base class.

* As performant in terms of memory and time, as the same functionality
  implemented "manually" with raw pointers.

* An object of this class takes twice as much memory as the raw
  pointer.

# Details

## Usage

The example below shows the basic usage.

{% highlight c++ %}
{% include_relative basic.cc %}
{% endhighlight %}

## How it works

* The group of managing objects share **a managing structure**, which
  is allocated dynamically by the first object in the group.

* A managing object has a pointer to the managing structure of its
  group.

* A reference count (i.e., the size of the group) is a field in the
  managing structure.

* When a managing object is copied, the reference count is
  incremented.

* When a managing object is destroyed, the reference count is
  decremented.

* When the reference count reaches 0, the managed data is destroyed.

# From `unique_ptr` to `shared_ptr`

We can move the ownershipd from `unique_ptr` to `shared_ptr` like
that:

{% highlight c++ %}
{% include_relative u2s.cc %}
{% endhighlight %}

But it's better done this way:

{% highlight c++ %}
{% include_relative u2s_better.cc %}
{% endhighlight %}

We can move the ownership from an rvalue of type `unique_ptr`, because
`shared_ptr` has such a constructor.  Therefore, we can create a
`shared_ptr` object from a temporary object of type `unique_ptr`
returned by functions like this:

{% highlight c++ %}
{% include_relative u2s_example.cc %}
{% endhighlight %}

# Parallel usage

  \begin{itemize}
    \item Klasa częściowo jest bezpieczna w programowaniu
      współbieżnym.
    \item Jeżeli wątek ma swoją kopię \code{shared_ptr}, to może jej
      swobodnie używać bez synchronizacji, włącznie z jej
      przenoszeniem i tworzeniem kopii.
    \item Jeżeli wątki używają tego samego obiektu \code{shared_ptr},
      to muszą synchronizować działania, jeżeli obiekt jest zmieniany.
  \end{itemize}

\end{frame}

# Performance

  \item Obiekt \code{shared_ptr} zajmuje dwa razy więcej pamięci niż
    surowy wskaźnik, bo zawiera dwa pola:
    \begin{itemize}
    \item wskaźnik na zarządzany obiekt,
    \item wskaźnik na strukturę zarządającą.
    \end{itemize}

\item Dodatkowo jest dynamicznie alokowana pamięć na strukturę
    zarządzającą.

\item Wskaźnik na zarządzany obiekt mógłby być częścią struktury
    zarządzającej, ale wtedy odwołanie do obiektu zarządzanego byłoby
    wolniejsze.
  
## `std::make_shared`

  Zamiast pisać typ A dwa razy w sposobie na piechotę:

  \code{shared_ptr<A> sp(new A("A1"));}

  Możemy napisać typ A tylko raz używając funkcji \code{make_shared}:
  
  \code{auto sp = make_shared<A>("A1");}

  Obiekt stworzony przez \code{make_shared} jest przenoszony, a nie
  kopiowany.

  ZALETA \#1: tworzenie obiektu zarządzanego i zarządzającego odbywa
  się w jedyn kroku, co jest bezpieczne pod względem obsługi wyjątków.

  \vspace{0.25 cm}

  ZALETA \#2: Funkcja \code{std::make_shared} tworzy obiekt zarządzany i
  zarządzający używając jednej alokacji pamięci, przez co jest szybsza
  niż osobne tworzenie tych obiektów.

\end{frame}

# Conclusion

\item Klasa \code{shared_ptr<T>} pozwala na łatwe współdzielenie
    obiektów, które były stworzone dynamicznie.

\item Główne zadanie: zniszczyć obiekt zarządzany, kiedy nie jest
    już potrzebny.

\item Obiekty klasy \code{shared_ptr<T>} są dwa razy większe niż
    surowy wskaźnik.

\item Można łatwo tworzyć obiekty \code{shared_ptr<T>} z
    \code{unique_ptr<T>}.

<!-- LocalWords:  -->
