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

The problem: how to safely (i.e., without the race condition) use the
managed data if, using a weak pointer, we know the data exist.  Even
if we make sure that a weak poiner has not expired yet, we cannot use
a raw pointer, because that raw pointer might dangle just a while
later.  Luckily, `weak_ptr` does not offer a way of getting a raw
pointer with the dereference operator (`operator *`), the member
access through poiner operator (`operator ->`), or the `get` function
just as the unique and shared pointers do.

The solution: *lock* the managed data (snatch the ownership) by
creating a shared pointer from the weak pointer.  We can do it in two
ways:

* call the constructor of `shared_ptr` with a weak pointer, which
  throws an exception if the weak pointer has expired,

* call the `lock` function of the weak pointer, which returns a null
  shared pointer if the weak pointer has expired.

Here's an example:

{% highlight c++ %}
{% include_relative basic.cc %}
{% endhighlight %}

## How it works

The control data structure of the shared pointer group is also used by
the weak pointers, which also belong to the group, but without
claiming ownership.

Just as a shared pointer, a weak pointer has a raw pointer to the
control data structure.

A managing structure not only has a reference count, but also a *weak
count*, which keeps the number of weak pointers.

We know that the managed data is destroyed, when the reference count
reaches zero.

The control data structure is destroyed when both the reference count
and the weak count reach zero.

# The implementation of the motivating example

Here's the implementation:

{% highlight c++ %}
{% include_relative factory.cc %}
{% endhighlight %}

## Performance

A weak pointer takes twice as much memory as a raw pointer, because it
has:

* the raw pointer to the managed data,

* the raw pointer to the control data structure.

What do we need the raw pointer to the managed data for if we cannot
access it directly?  Beause it will be needed to produce a shared
pointer.

As for a shared pointer, the same applies to a raw pointer: the raw
pointer to the managed data could be a part of the control data
structure, but getting to the managed data would be slower, because an
extra indirect access would be needed.

# Conclusion

* A weak pointer tracks the managed data without claiming the
  ownership.

* We *always* produce a weak pointer from a shared pointer.

* We can produce a shared pointer from a weak pointer if possible,
  i.e., if the managed data exist.

* A weak pointer never destroys the managed data.

# Quiz

* What do we need type `weak_ptr` for?

* What's the difference between `shared_ptr` and `weak_ptr`?

* Can we create an object of type `weak_ptr` based on an object of
  type `unique_ptr`?

<!-- LocalWords: inlined multithreaded -->
<!-- LocalWords: performant rvalue suboptimal -->
