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

* The group of managing objects share **a managing data structure**,
  which is allocated dynamically by the first object in the group.

* A managing object has a pointer to the managing data structure of
  its group.

* A reference count (i.e., the size of the group) is a field in the
  managing data structure.

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
`shared_ptr` has the right constructor.  Therefore, we can create a
`shared_ptr` object from a temporary object of type `unique_ptr`,
e.g., returned by a function like this:

{% highlight c++ %}
{% include_relative u2s_example.cc %}
{% endhighlight %}

## Parallel usage

You can copy, move, and destroy `share_ptr` objects thread-safe,
because the operations on the managing data structure are atomic.

However, modification of the managed data should be synchronized in
multithreaded programming, of course.

## Performance

A `shared_ptr` object takes twice as much memory as a raw pointer,
because it has two fields:

* a pointer to the managed data,

* a pointer to the managing data structure.

On top of this, there is the managing data structure allocated, but
it's shared among the managing objects.

A pointer to the managed data could be kept in the managing data
structure, but then getting to the managed data would involve an extra
indirect access, thwarting performance.

## `std::make_shared`

  Instead of writing twice the data type `A` like this:

  `shared_ptr<A> sp(new A);`

  We can use the function `make_shared` and write the type only once
  like this:

  `auto sp = make_shared<A>("A1");`

  There is no performance overhead.

  auto sp = make_shared<A[]>(3);

  Obiekt stworzony przez \code{make_shared} jest przenoszony, a nie
  kopiowany.

  Funkcja \code{std::make_shared} tworzy obiekt zarządzany i
  zarządzający używając jednej alokacji pamięci, przez co jest szybsza
  niż osobne tworzenie tych obiektów.

# Conclusion

* An object of class `shared_ptr<T>` allows for sharing data of type
  `T` that were dynamically allocated.

* The objective: destroy the managed data exactly at the time the data
  is no longer needed.

* A managing object of type `shared_ptr` is twice as large as a raw
  pointer.

* We can easily pass the ownership from `unique_ptr` to `shared_ptr`,
  but not the other way around.

<!-- LocalWords:  -->
