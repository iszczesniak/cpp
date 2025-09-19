---
title: Containers
---

# Introduction

A list, an associative map, a set, and other data structures, are
called **containers** in C++.  A container:

* is a *generic* data structure,

* stores elements of *any, but only one type*,

* stores elements *by value*, not by reference,

* stores elements at the *heap*,

* can grow or shrink dynamically (i.e., at run-time).

A container is generic, because it can store data of any type `T`.  A
container type (e.g., `std::vector<T>`) is **templated**, because we
have to give a *template argument* `T` at compile-type.

While the container itself (i.e., the object of the container type)
can be anywhere in memory, the elements have to be stored at the heap,
because the size of the container can change at run-time.

Containers are complemented by iterators and algorithms.  The iterator
is a generalization of a pointer.  Algorithms, such as `std::sort`,
are generalized in that they can be used with various containers,
because access to the container elements is provided with iterators.

Standard containers, iterators, and algorithms fit together because of
the naming and semantic convention.  As for the naming convention, for
instance, every container has the `begin`, and `end`, `size`, and
other functions.  As for the semantic convention, for instance, we get
the data of iterator `i` by dereferencing: `*i`.

## History

In the early 90's, containers were:

* a cutting-edge technology, and a hot research topic,

* originally implemented as the STL, the seminal work by Alexander
  Stepanov.

Now containers are:

* an indispensable tool of every-day use,

* a part of the standard library.

**There is no excuse, put them to use.**

## Basic container types

Sequence containers:

* `std::vector<T>` - the vector,

* `std::list<T>` - the doubly-linked list,

* `std::deque<T>` - a container with the traits of the vector and the
  list,

* `std::forward_list<T>` - the singly-linked list,

Associative containers:

* `std::map<K, V>` - the associative array (aka dictionary),

* `std::multimap<K, V>` - the associative array with duplicate keys
  allowed,

* `std::set<T>` - the set,

* `std::multiset<T>` - the set with duplicate elements allowed,

The adapters:

* `std::stack<T>` - the stack,

* `std::queue<T>` - the queue,

* `std::priority_queue<T>` - the priority queue.

Container types can be nested, i.e., `T` can be a container type too.

## Comparison of basic types of containers

### `std::vector<T>`

The vector offers:

* **random access** with the random access operator, i.e., the `[]`
  operator, aka the index operator, or the subscript operator,

* **memory contiguity**: all elements are stored contiguous in memory,
  which implies:

  - the random access operator is as fast as can be, because it only
    has to increase a pointer,

  - the memory access is faster: the elements of the vector are all
    stored compactly together, and so the processor cache is used the
    most effectively,

  - **slow insertion and removal**.

The vector may have to reallocate its elements when the currently
allocated memory is not enough, when we insert a new element at the
end of the vector.  First, new memory has to be allocated.  Next, the
elements are copied or moved, depending on whether the type of the
elements has the move semantics implemented, and then a new element is
added (copied or moved).  Finally, the old memory is released.

The performance of the vector drops not only when elements are
frequently reallocated, but also when elements are frequently inserted
or removed.  When an element is inserted or removed, the elements that
follow have to be moved (or copied) one-by-one, because the vector has
to guarantee the memory contiguity.

In comparison with other containers, the vector performs very well if
the reallocation, insertion and removal do not frequently happen, for
instance, if we build a vector, fill it in, and then random-access the
elements frequently.

### `std::list<T>`

The list does not store its elements contiguously in memory, but
stores them in different locations at the heap, which were allocated
separately.  Then the elements are doubly-linked, which implies:

* **fast insertion and removal**, because elements do not have to be
  reallocated, and neither the elements that follow have to be moved
  one-by-one,

* **iterative access only**, because to access some element, we have
  to get to it through the elements that proceed or follow it.

The list does not offer element random access, even though it could
with a more elaborate implementation.  However, C++ aims at providing
fast and lean tools, and such a bloated list would decrease
performance.  The list of type `std::list` offers the minimal
functionality required, but with superior (time and memory)
performance.

### `std::deque<T>`

The deque (the double ended queue, pronounced as "deck", as in "deck
of cards") offers a trade-off between functionality and efficiency.
Use the deque if you need random-access, and frequently insert or
erase elements at the front or the back.  It offers:

* **const-time random access** - like the vector,

* **const-time insertion and removal at the front and the back** -
    like the list.

How come?  Well, we'd be remiss not to mention that:

* the random access, even though of const time (doesn't depend on the
  size of the container), is not as fast as for the vector,

* insertion or removal, except for the front and the back, is of
  linear time, while for the list is of const time.

The deque is implemented without the guarantee of memory contiguity,
as a list of equal-size arrays.  Random access is less efficient in
comparison with the vector because finding an address of an element
requires more arithmetic.  Insertion or erasure, except for the front
and the back, is of linear time because the elements "on the right"
have to be "reorganized".

Use the deque only when the vector and the list won't do.

### `std::forward_list<T>`

Sometimes `std::list` is more than we need from a list.  Sometimes we
need to forward-iterate only, and can do without the capability to
backward-iterate that is offered by `std::list`, the capability that
we pay for with performance.

Type `std::forward_list` is even leaner and more performant than
`std::list`, because it is a singly linked list: we can iterate
forward, but not backward.

### `std::set`, and `std::multiset`

The set stores **unique** elements, and the multiset allows for
multiple elements of an equal value.  Both container types store the
elements **sorted**.  By default the order is ascending, but we can
establish any order with a callable.

Interestingly, we cannot modify the elements, because that would
destroy the order of elements, and make the container inconsistent.
For this reason, the type of the elements stored is made const, even
if the template argument was non-const.

If we want to modify an element, then we have to remove the element
first, and insert a new element with a different value next.

```cpp
{% include_relative set.cc %}
```

# Iterators

Iterators are the glue between the containers, and the algorithms.
Function `std::sort` can be used with various containers through
iterators.  Iterators provide access to the container elements, so
that we do not care about the type of a container (the container type
was abstracted away).

An iterator is a generalization of a pointer.  We could say that a
pointer is the iterator of a C-style array.  We can initialize the
pointer, compare it to some other pointer, dereference it to get to
the element it points to, and also increment it.  Furthermore, we can
random access any element in the C-style array if we increase (with
the + operator) the pointer to the element number 0 by the value of
the index as in here:

```cpp
{% include_relative pointer.cc %}
```

Iterator types are user-defined, e.g., of a structure type.  Iterators
are wrappers around pointers, where the operators (defined for that
type) implement the required functionality.  For instance, if in the
example above we replace the C-style array with a deque, the rest of
the code can remain untouched:

```cpp
{% include_relative iterator_intro.cc %}
```

Iterators of the standard library are very small and very efficient.
They typically store only a single pointer.  Therefore we are free to
use them by value, and copy them.  We could use iterators by reference
too, but that would be just awkward, just as awkward would be using
pointers by reference.

For a given container type `T`, there are always at least two iterator
types defined:

* non-const iterator type: `T::iterator`,

* const iterator type: `T::const_iterator`.

You cannot modify elements of a container with a const iterator.  For
better code, always use the const iterator if you do not modify the
elements.

## Functions `begin`, `end`

We know where the elements of a container are with the `begin`, and
`end` functions.  The `begin` function returns an iterator to the
first element.  The `end` function returns a *past-the-end* iterator
which you would get if you incremented an iterator to the last
element: we could say the `end` function returns an iterator to an
**imaginary** element (imaginary, because that element does not exist)
that would follow the last element.  If a container has no elements,
the iterators returned by `begin` and `end` equal.

The `begin` and `end` functions return non-const iterators for a
non-const container, and const iterators for a const container.  If we
want to iterate with a const iterator over a non-const container, we
can use the `cbegin` and `cend` functions, which return const
iterators.

The `cbegin` and `cend` are for convenience only, because they are
dispensable.  We can achieve the same functionality by calling the
`begin` and `end` functions for a non-const container when we
reference the container with a const reference, which we can do with
the `std::as_const` function.

Iterators can be categorized into a few basic categories (concepts,
technically speaking), depending on the provided functionality:

* a forward iterator,

* a bidirectional iterator,

* a random-access iterator.

## A forward iterator

A forward iterator provides only the two most basic operations: `*i`,
`++i`.  The iterator of `std::forward_list` is a forward iterator.
Here's an example:

```cpp
{% include_relative iterator_forward.cc %}
```

## A bidirectional iterator

A bidirectional iterator is a forward iterator with an extra operation
defined: `--i`, i.e., move back by one element.  The iterator of
`std::list` is a bidirectional iterator.  For example:

```cpp
{% include_relative iterator_bidirectional.cc %}
```

## A random-access iterator

A random-access iterator allows for increasing or decreasing the
iterator value by any integer, as we've done in the example above with
the deque.  The iterator of the vector is a random-access iterator.  A
pointer is a random-access iterator too.

# Forward-iterating over the elements of a container

We can forward-iterate over the elements of a container (or, more
broadly, a range, that includes the C-style array) in two ways: the
old, and the new.

## Iterating the old way

As shown in the example below, you can forward-iterate over the
elements of a container the old way, which is a bit tedious, because
we have to initialize the *iteration variable* `i`, write the loop
condition, and then increment the variable.  This loop is also
error-prone, as it's easy to mistakenly write '--i' instead of '++i',
or `begin` instead of `end`.

```cpp
{% include_relative iterate_old.cc %}
```

Likewise for C-style arrays:

```cpp
{% include_relative iterate_old_ca.cc %}
```

## Iterating the new way

Since C++11, we can iterate the new way, using the *range-based* (aka
for-each) syntax of the for loop.  The semantics is the same as for
the old way.  The range-based loop is less error-prone, because we
have to write less.

The syntax is:

```cpp
for(declaration: expression) statement
```

Where:

* `declaration` declares the variable that is initialized with the
  container elements (or more precisely, the range elements) in every
  iteration of the loop.  We refer to this variable as the *declared
  variable*.

* `expression` is the *range expression*.  Most often, we put the
  container here.  Having the range expression, we can get the values
  of the begin and end iterators.

* `statement` is the statement executed in every iteration of the
  loop.  In that statement we use the declared variable.

An example:

```cpp
{% include_relative iterate_new.cc %}
```

## How iteration the new way works

The new range-based loop is translated by a compiler to a regular
loop, where the iteration variable is of an iterator type.  The
iteration variable is initialized with a value returned by the `begin`
function.  The loop continues if the value of the iterator is not
equal to the value returned by the `end` function.  In every iteration
of the loop, the **declared variable** is initialized by the
dereferenced **iteration variable**.  After an iteration, the iterator
is incremented.

To use the range-based loops, we need to make sure that:

* we can call the `begin` and `end` functions for the range
  expression,

* the type of the values returned by the `begin` and `end` functions
  should have the following defined:

  - the `!=` comparison operator,

  - the dereference operator, i.e., `*`,

  - the prefix increment operator, i.e., `++`.

Here is an example how we can use that functionality:

```cpp
{% include_relative range.cc %}
```

# Containers and element management

We can copy or move an element into a container.  We can also move it
from a container, except for the associative containers, for which we
can extract an element.  We can also **emplace** an element in a
container.

Containers have the move semantics implemented.  An example:

```cpp
{% include_relative container_move.cc %}
```

## Move semantics for element types

We can move elements into containers: it's enough to make sure that
the element we insert is used in an rvalue.  We can also move from an
element of a sequence container.  Example:

```cpp
{% include_relative element_move.cc %}
```

## Extract

We cannot move an element from an *associative container*, because we
cannot modify that element, even if we are using a non-const iterator,
as the type of the element is const.  We shouldn't even move, because
the object after moving its value would remain in the container, but
in an undefined state, which would make the container inconsistent.
Instead of moving the value of an object, we should **extract** the
object.  Extraction is supported only by the associative containers,
because it's needed only there.

Extraction is implemented by *unlinking* the element from the
container.  As the result of the extraction, we get a *node handle*
(an object of a move-only type) which owns the extracted element: when
a node handle is destroyed while still holding the element, that
element is destroyed too.  The node handle can be implemented with the
unique smart pointer, i.e., `std::unique_ptr`.

Having a node handle, we can insert the element into a different
container of the same type as the container from which the element was
extracted.  The element remains untouched (still in the same place
with the same value) when it's extracted and inserted; the ownership
of the element changes from one container to the other passing through
a node handle.

Having a node handle, we can access the owned element with the `value`
function, and move it (move its value) somewhere, e.g., to a different
container of a different type.  When the node handle is destroyed, it
will destroy the element from which we moved.

An example:

```cpp
{% include_relative extract.cc %}
```

## Insertion

We insert an element by passing it to a function (e.g., `insert` or
`push_front`) of a container.  If the element is an object, then it's
eligible for moving if we pass it as an rvalue, and copied otherwise.
Copying is needed when we want to keep the source element intact.
Moving is faster, and so preferred over copying, if the source won't
be needed later.

The container inserts (by copying or moving the value of the passed
element) either with the constructor or the assignment operator
depending on whether the target object already exists.  If it doesn't
but the memory has already been allocated (e.g., as in a vector), then
the target object is constructed in place (using the placement `new`
operator).

## Emplacement

Emplacement creates an object based on the arguments we provide, as
opposed to insertion that expects a ready object.  An emplacement
function passes (*forwards*, technically speaking) its arguments to
the constructor of the object to emplace.  The container knows the
**target place** (i.e., the place in memory) for the object, because
it manages the memory for its elements.

If the target place doesn't already store an object (e.g., the place
for the first element of an empty vector), the container creates an
object in that place.  If the target place already stores an object,
the container assignes to it a temporary object created with the
forwarded arguments, so that the temporary value is eligible for
moving into the object in the target place.  Alternatively, I'd
reckon, the target object could be destroyed, and a new one could be
created in its place, but that ain't so, and I wish I knew why.

We emplace by calling an emplacement function of a container.
Containers have various functions for emplacing with slight semantic
differences, e.g., `std::vector` has `emplace`, `std::list` has
`emplace_front`, and `std::forward_list` has `emplace_after`.

Emplacement works similar to insertion in that the elements that
follow are "pushed to the right".  Therefore emplacement entails the
same performance issues as the insertion does.

```cpp
{% include_relative emplace.cc %}
```

# Conclusion

* Don't implement the basic data structures, because they are already
  there.

* Use the containers, and get better at using them.  Their
  functionality is quite rich.

* With the containers, you can build complex data structures.

* With the containers use the standard algorithms, because your own
  algorithm implementations will most likely perform far worse.

# Quiz

* What are the prominent differences between container types?

* Why can't we modify the set elements?

* How does emplacement work?

{% include rid %}

<!-- LocalWords: cbegin -->
<!-- LocalWords: cend -->
<!-- LocalWords: const -->
<!-- LocalWords: deque -->
<!-- LocalWords: dereference -->
<!-- LocalWords: dereferenced -->
<!-- LocalWords: dereferencing -->
<!-- LocalWords: emplace -->
<!-- LocalWords: emplaced -->
<!-- LocalWords: emplacing -->
<!-- LocalWords: rvalue -->
<!-- LocalWords: multiset -->
<!-- LocalWords: performant -->
<!-- LocalWords: Stepanov -->
<!-- LocalWords: STL -->
<!-- LocalWords: templated -->
<!-- LocalWords: unlinking -->
