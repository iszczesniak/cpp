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

Pozwalają na dostęp do elementów kontenera.
Implementacja: wskaźniki obudowane w klasy.
Do funkcji przekazujemy przez wartość, nie referencję.
Dla kontenera T, iterator to: \code{T::iterator}.
Iterator ``const'' obiektów stałych: \code{T::const\_iterator}.
Używaj iteratora ``const'', jeżeli nie modyfikujesz kontenera.
Required operations for any iterator: `*i`, `++i`
Podstawowe funkcje: \code{T::begin()}, \code{T::end()}.
Różne funkcje (\code{find}, \code{insert}) zwracają iteratory.

## Reverse iterators

  \item Pozwalają na iterację od końca po elementach kontenera.
  \item Typ: \code{T::reverse\_iterator} i \code{T::const\_reverse\_iterator}
  \item Skomplikowane, bardzo trudne w użyciu i...
  \item dlatego nie mają większego znaczenia praktycznego.
  \item Przestroga: \red{lepiej nie używać!}
  \end{itemize}

# Iterating over the elements of a container

## Iterating the old way

{% highlight c++ %}
{% include_relative iterate_old.cc %}
{% endhighlight %}

## Iterating the new way

{% highlight c++ %}
{% include_relative iterate_new.cc %}
{% endhighlight %}

## How iteration the new way works

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

# Quasi-containers

## `std::pair`

  \begin{itemize}
  \item \code{\#include <utility>}
  \item Para p obiektów typów A i B: \code{std::pair<A, B> p;}
  \item p.first - pierwszy element, p.second - drugi element
  \item Globalna funkcja szablonowa \code{std::make\_pair} pozwala na
    tworzenie pary bez podania typów, kompilator wywnioskuje typy
    sam:\\ \code{std::make\_pair(1, "test");}
  \item Funkcja \code{tie} pozwala na wygodne przypisanie wartości z
    pary do osobnych zmiennych:\\ \code{std::tie(f, s) = p;}
  \item Przeniesienie pary polega na przeniesieniu każdego z obiektów
    składowych.
  \item Ma zdefiniowane globalne operatory: \code{!= < == > <= >=}
  \end{itemize}

## `std::tuple`

## `std::array`

## `std::optional`

# Conclusion

* Don't implement the basic data structures, because they are already
  there.

* Use the containers, and get better at using them.  Their
  functionality is quite rich.

* With the containers, you can build complex data structures.

* With the containers use the standard algorithms, because your own
  algorithm implementations will most likely perform far worse.

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
