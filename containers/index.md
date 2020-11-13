---
title: Containers
---

# Introduction

A list, an associative map, a set, and other data structures, are
called **containers** in C++.  A container:

* is a *generic* data structure,

* stores elements of *any type*,

* stores elements only of a *single type*,

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

## History

In the early 90's, containers were:

* a cutting-edge technology, and a hot research topic,

* originally implemented as the STL.

Now containers are:

* an indispensable tool of every-day use,

* a part of the standard library.

There is no excuse, put them to use.

## Basic container types

Sequence containers:

* `std::vector<T>` - the vector,

* `std::list<T>` - the doubly-linked list,

* `std::deque<T>` - the deque, amalgamation of the vector and the
  doubly-linked list,

* `std::forward_list<T>` - the sinlgy-linked list,

Associative containers:

* `std::map<K, V>` - the associative array (aka dictionary),

* `std::multimap<K, V>` - the associative array with duplicate keys
  allowed,

* `std::set<T>` - the set,

* `std::multiset<T>` - the set with duplicate elements allowed,

The adaptors:

* `std::stack` - the stack,

* `std::queue` - the queue,

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

The vector may have to reallocate the elements when the currently
allocated memory for elements is not enough, as when, e.g., we insert
an element into a vector.  First, new memory has to be allocated.
Next, the elements are copied or moved, depending on whether the type
of the elements has the move semantics implemented.  Finally, the old
memory is released.

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

The deque (pronounced as "deck", as in deck of cards) offers:

* **random access**,

* **fast insertion and removal**.

How come?  Well, insertion and removal are not as fast as in
`std::list`, and random access is not as fast as in `std::vector`.
The deque offers a trade-off between functionality, and efficiency.
Use the deque if you frequently need to random-access, insert and
remove elements.

The deque is implemented with small vectors organized one after
another, but without guaranteeing memory contiguity.  If element
reallocation, insertion or removal is required, then it's limited to
one small vector.  However, random access is less efficient in
comparison with vector, because finding an address of an element
requires more arithmetic.

Use the deque only when the vector and the list won't do.

### `std::forward_list<T>`

Sometimes `std::list` is more than we need from a list.  Sometimes we
need to forward-iterate only, and can do without the capability to
backward-iterate that is offered by `std::list`, the capability that
we pay for with performance.

Type `std::forward_list` is even leaner and more performant than
`std::list`, because it is a singly linked list: we can iterate
forward, but not backward.

# Iterators

* Pozwalają na dostęp do elementów kontenera.
* Implementacja: wskaźniki obudowane w klasy.
* Do funkcji przekazujemy przez wartość, nie referencję.
* Dla kontenera T, iterator to: \code{T::iterator}.
* Iterator ``const'' obiektów stałych: \code{T::const\_iterator}.
* Używaj iteratora ``const'', jeżeli nie modyfikujesz kontenera.
* Required operations for any iterator: `*i`, `++i`
* Podstawowe funkcje: \code{T::begin()}, \code{T::end()}.
* Różne funkcje (\code{find}, \code{insert}) zwracają iteratory.

## Reverse iterators

* Pozwalają na iterację od końca po elementach kontenera.

* Typ: \code{T::reverse\_iterator} i \code{T::const\_reverse\_iterator}

* Skomplikowane, bardzo trudne w użyciu i... dlatego nie mają
  większego znaczenia praktycznego.

* Przestroga: \red{lepiej nie używać!}

# Iterating over the elements of a container

## Forward-iterating the old way

As shown in the example below, you can forward-iterate over the
elements of a container the old way, which is a bit tedious, because
we have to initialize the *iteration variable* `i`, write the loop
condition, and then increment the variable.  This loop is also
error-prone, as it's easy to mistakenly write '--i' instead of '++i',
or `begin` instead of `end`.

The `begin` function returns an iterator to the first element.  The
`end` function returns an iterator which you would get if you
incremented an iterator to the last element: we could say the `end`
function returns an iterator to an **imaginary** element (that element
does not exist) that would follow the last element.  If a container
has no elements, the iterators returned by `begin` and `end` equal.

The `begin` and `end` functions return non-const iterators for a
non-const container, and const iterators for a const container.  If we
want to iterate with a const iterator over a non-const container, we
can use the `cbegin` and `cend` functions.

The `cbegin` and `cend` are for convenience only, because they are
despensible.  We can achieve the same functionality by calling the
`begin` and `end` functions for a non-const container when we
reference the container with a const reference, which we can do with
the `std::as_const` function.

{% highlight c++ %}
{% include_relative iterate_old.cc %}
{% endhighlight %}

## Iterating the new way

Since C++11, we can iterate the new way, using the *range-based* (aka
for-each) syntax of the for loop.  The semantics is the same as for
the old way.  The range-based loop is less error-prone, because we
have to write less.

The syntax is:

{% highlight c++ %}
for(declaration: expression) statement
{% endhighlight %}

Where:

* `declaration` declares the variable that is initialized with the
  container elements (or more precisely, the range elements) in every
  iteration of the loop.  We refer to this variable as the *declared
  variable*.

* `expression` is the *range expression*.  Most often, we put the
  container here.  A range expression has the begin and end iterator
  values.

* `statement` is the statement executed in every iteration of the
  loop.  In that statement we use the declared variable.

An example:

{% highlight c++ %}
{% include_relative iterate_new.cc %}
{% endhighlight %}

## How iteration the new way works

The new range-based loop is translated by a compiler to a regular
loop, where the iteration variable is of an interator type.  The
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

{% highlight c++ %}
{% include_relative range.cc %}
{% endhighlight %}

# Algorithms

Algorytmy dla różnych kontenerów:

* sortowanie elementów (lepszej implementacji nie znajdziecie),
* wyszukiwanie elementów,
* iterowanie po elementach,
* usuwanie i dodawanie elementów.

Działają dla różnych kontenerów, bo kontenery mają ten sam interfejs:

* nazwy typów (np. \code{T::data\_value}),
* nazwy funkcji (np. \code{T::begin()}).

# Containers and move semantics

Containers have the move semantics implemented.

## Move semantics for element types

## Extract 

{% highlight c++ %}
{% include_relative extract.cc %}
{% endhighlight %}

# Conclusion

* Don't implement the basic data structures, because they are already
  there.

* Use the containers, and get better at using them.  Their
  functionality is quite rich.

* With the containers, you can build complex data structures.

* With the containers use the standard algorithms, because your own
  algorithm implementations will most likely perform far worse.

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
