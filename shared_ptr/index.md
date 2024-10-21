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

* ownership, because the data are destroyed when the group becomes
  empty.

In Java or C#, a reference has the shared-ownership semantics.

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

```cpp
{% include_relative basic.cc %}
```

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

```cpp
{% include_relative u2s.cc %}
```

But it's downright better done this way:

```cpp
{% include_relative u2s_better.cc %}
```

We can move the ownership from an rvalue of type `unique_ptr`, because
`shared_ptr` has the constructor which takes by rvalue reference an
object of type `std::unique_ptr`.  Therefore, we can create a
`shared_ptr` object from a temporary object of type `unique_ptr`,
e.g., returned by a function like this:

```cpp
{% include_relative u2s_example.cc %}
```

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

```cpp
{% include_relative make_shared.cc %}
```

But we can use function `make_shared` and write the type only once
like this (which is less error-prone):

```cpp
{% include_relative make_shared2.cc %}
```

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
faster than two separate memory allocations.

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
