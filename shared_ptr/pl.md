---
title: std::shared_ptr
---

# Wprowadzenie

Kiedy dynamicznie tworzymy dane (albo jakikolwiek inne zasoby) i
używamy ich w innych wątkach albo częściach kodu, to pojawia się
problem kiedy zniszczyć dane.  Jeżeli:

* nie zniszczymy danych, to mamy wyciek pamięci,

* zniszczymy dane zbyt wcześnie, to mamy zjawisko hazardu: dyndający
  wskaźnik i niezdefiniowane zachowanie, bo inne wątki czy części
  pamięci ciągle używają danych,

* zniszczymy dane zbyt późno, to mamy spadek wydajności, ponieważ
  pozwalamy niepotrzebnym danym tkwić w pamięci.

Dlatego powinniśmy niszczyć dane we właściwym momencie, czyli wtedy,
kiedy nie są one już potrzebne.  Niestety, ten właściwy moment jest
trudny do określenia, ponieważ może on zależeć od:

* danych (ich pewnych wartości),

* przebiegu w czasie innych wątków (tego co i kiedy robią).

Rozwiązaniem problemu jest *semantyka współdzielonej własności*:

* współdzielonej, ponieważ dane są zarządzane przez grupę,

* własności, ponieważ dane są niszczone, kiedy grupa staje się pusta.

W Javie i C#, referencja ma semantykę współdzielonej własności.

# `std::shared_ptr`

* `#include <memory>`

* The smart pointer type that implements the shared-ownership
  semantics.

* The objects of this type are the **managing objects**, and the data
  allocated dynamically is the **managed data**.

* It's a template class: the template argument is the type of the
  manged data.

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

* The group of managing objects share **a control data structure**,
  which is allocated dynamically by the first object in the group.

* A managing object has a pointer to the control data structure of its
  group.

* A reference count (i.e., the size of the group) is a field in the
  control data structure.

* When a managing object is copied, the reference count is
  incremented.

* When a managing object is destroyed, the reference count is
  decremented.

* When the reference count reaches 0, the managed data is destroyed.

## From `unique_ptr` to `shared_ptr`

We can move the ownership from `unique_ptr` to `shared_ptr` like that
alright:

{% highlight c++ %}
{% include_relative u2s.cc %}
{% endhighlight %}

But it's downright better done this way:

{% highlight c++ %}
{% include_relative u2s_better.cc %}
{% endhighlight %}

We can move the ownership from an rvalue of type `unique_ptr`, because
`shared_ptr` has the constructor which takes by rvalue reference an
object of type `std::unique_ptr`.  Therefore, we can create a
`shared_ptr` object from a temporary object of type `unique_ptr`,
e.g., returned by a function like this:

{% highlight c++ %}
{% include_relative u2s_example.cc %}
{% endhighlight %}

## Performance

A `shared_ptr` object takes twice as much memory as a raw pointer,
because it has two fields:

* a pointer to the managed data,

* a pointer to the control data structure.

On top of this, there is the memory taken by the control data
structure allocated, but it's not a big deal, because it's shared
among the managing objects.

A pointer to the managed data could be kept in the control data
structure, but then getting to the managed data would involve an extra
indirect access, thwarting performance.

## `std::make_shared`

When creating the managed data and the managing object, we can write
the type of the managed data twice (and perhaps introduce bugs):

{% highlight c++ %}
{% include_relative make_shared.cc %}
{% endhighlight %}

But we can use function `make_shared` and write the type only once
like this (which is less error-prone):

{% highlight c++ %}
{% include_relative make_shared2.cc %}
{% endhighlight %}

Function template `make_shared` takes the type of the data to manage
as its template argument.

Similar to function `make_unique`, function `make_shared` creates the
managed data and the managing object, and then returns the managing
object.  There is no performance overhead, since the function will
most likely be inlined, and the constructors elided when returning the
managing object.

Interestingly, `make_shared` allocates *in one piece* (i.e., with one
memory allocation) the memory for the managed data and the control
data structure, and then creates *in place* (i.e., without allocating
memory) the managed data and the control data structure, which is
faster than allocating memory separately for the managed data and the
control data structure.

# Conclusion

* An object of class `shared_ptr<T>` allows for sharing data of type
  `T` that were dynamically allocated.

* The objective: destroy the managed data exactly at the time the data
  is no longer needed.

* A managing object of type `shared_ptr` is twice as large as a raw
  pointer.

* We can easily pass the ownership from `unique_ptr` to `shared_ptr`,
  but not the other way around.

# Quiz

* What's the difference between `unique_ptr` and `shared_ptr`?

* What do we need a control data structure for?

* Does the type of the managed data need to have some properties in
  order to be managed?

{% include rid %}

<!-- LocalWords: inlined multithreaded -->
<!-- LocalWords: performant rvalue suboptimal -->
