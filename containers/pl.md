---
title: Kontenery
---

# Wprowadzenie

Lista, tablica asocjacyjna, zbiór i inne typy danych są nazywane
**kontenerami** w C++.  Kontener:

* jest *uogólnioną* strukturą danych,

* przechowuje elementy *dowolnego typu*,

* przechowuje elementy tylko *jednego typu*,

* przechowuje elementy przez wartość, nie referencję,

* przechowuje elementy na stercie,

* może zmieniać rozmiar dynamiczne, czyli w czasie uruchomienia.

Kontener jest uogólniony, bo może przechowywać elementy dowolnego typu
`T`.  Typ kontenera (np. `std::vector<T>`) jest **szablonowy**, więc
możemy przekazać mu *argument szablonu* `T` w czasie kompilacji.

Podczas gdy kontener (obiekt typu kontenera) może być gdziekolwiek w
pamięci, to jego elementy są przechowywane na stercie, bo rozmiar
kontenera może się zmieniać w czasie uruchomienia.

Kontenery są uzupełniane przez iteratory i algorytmy.  Iterator jest
uogólnieniem wskaźnika.  Algorytmy, np. `std::sort`, są uogólnione,
czyli można ich użyć z różnymi konteneramim, ponieważ dostęp do ich
elementów jest zapewniony przez iteratory.

Standardowe kontenery, iteratory i algorytmy pasują do siebie,
ponieważ stosują te same konwencje nazw i semantyki.  Jeżeli chodzi o
konwencję nazw, to na przykład każdy kontener ma funkcje `begin`,
`end`, `size`.  Jeżeli chodzi o konwencję semantyki, to na przykład
otrzymujemy dane iteratora `i` przez wyłuskanie `*i`.

## Historia

Na początku lat dziewięćdziesiątych kontenery były:

* najnowszą technologią, tematem badań naukowych,

* zaimplementowane jako Standard Template Library (STL), przełomowa
  biblioteka Alexandra Stepanova.

Teraz kontenery są:

* nieodzownym narzędziem codziennego użycia,

* częścią biblioteki standardowej.

**Nie ma wymówki, trzeba używać.**

## Typy podstawowych kontenerów

Kontenery sekwencji:

* `std::vector<T>` - wektor,

* `std::list<T>` - lista dwukierunkowa,

* `std::deque<T>` - połączenie wektora i listy dwukierunkowej,

* `std::forward_list<T>` - lista jednokierunkowa,

Kontenery asocjacyjne:

* `std::map<K, V>` - tablica asocjacyjna (aka słownik),

* `std::multimap<K, V>` - tablica asocjacyjna z możliwymi równymi
  kluczami,

* `std::set<T>` - zbiór,

* `std::multiset<T>` - zbiór z możliwymi równymi elementami.

Adaptery:

* `std::stack` - stos,

* `std::queue` - kolejka,

* `std::priority_queue<T>` - kolejka priorytetowa.

Typy kontenerów mogą być zagnieżdżone, czyli `T` też może być
kontenerem.

## Porównanie typów podstawowych kontenerów

### `std::vector<T>`

Wektor zapewnia:

* **swobodny dostęp** do elementów z użyciem operatora swobodnego
  dostępu, czyli operatora `[]` zwanego także operatorem indeksowania,

* **ciągłość pamięci**: wszystkie elementy są przechowywane w pamięci
    obok siebie, z czego wynika że:

  - operator swobodnego dostępu jest maksymalnie szybki, ponieważ
    jedynie zwiększa wskaźnik

  - dostęp do pamięci jest maksymalnie szyki: elementy są
    przechowywane obok siecie, co zwiększa efektywność pamięci
    podręcznej procesora,

  - **usuwanie i wstawianie elementów jest wolne**.

Wektor realokuje elementy, kiedy aktualnie zaalokowana pamięć jest
niewystarczająca, żeby wstawić nowy element na koniec wektora.  Na
początku nowy obszar pamięci jest alokowany.  Następnie elementy
wektora są kopiowane (albo przenoszone, jeżeli typ elementów ma
zaimplementowaną semantykę przeniesiena), a potem nowy element jest
dodawany (przez kopiowanie albo przeniesienie).  Na końcu jest
zwalniana stara pamięć.

Wydajność wektora spada nie tylko wtedy, kiedy elementy są często
dodawane na koniec wektora, ale także wtedy, kiedy elementy są często
wstawiane albo usuwane.  Kiedy element jest wstawiany albo usuwany, to
elementy następujące muszą być kopiowane (albo przenoszone), ponieważ
wektor gwarantuje ciągłość pamięci.

W porównaniu z innymi kontenerami, wektor jest bardzo szybki, jeżeli
realokacja, dodawanie, wstawianie i usuwanie nie są często wykonywane,
np. kiedy tworzymy wektor o zadanym rozmiarze, wypełniamy go
wartościami, a następnie jedynie odwołujemy się do elementów.

### `std::list<T>`

Lista nie przechowuje elementów w ciągłej pamięci, ale w różnych
miejscach na stercie, które były osobno alokowane.  Lista jest
dwukierunkowa (ang. doubly-linked), więc:

* **wstawianie i usuwanie elementów jest szybkie**, ponieważ elementy
  nie muszą być realokowane, kopiowane czy przenoszone,

* **dostęp do elementów jest tylko iteracyjny**: żeby dostać się
  elementy, to musimy przejść przez elementy poprzedzające albo
  następujące.

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

### `std::set`, and `std::multiset`

The set stores **unique** elements, and the multiset allows for
multiple elements of an equal value.  Both container types store the
elements **sorted**.  By default the order is ascending, but we can
establish any order with a callable.

Interestingly, we cannot modify the elements, because that would
destroy the order of elements, and make the container inconsistent.
For this reason, the type of the elements stored is made const, even
if the template parameter was non-const.

If we want to modify an element, then we have to remove the element
first, and insert a new element with a different value next.

{% highlight c++ %}
{% include_relative set.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative pointer.cc %}
{% endhighlight %}

Iterator types are user-defined, e.g., of a structure type.  Iterators
are wrappers around pointers, where the operators (defined for that
type) implement the required functionality.  For instance, if in the
example above we replace the C-style array with a deque, the rest of
the code can remain untouched:

{% highlight c++ %}
{% include_relative iterator_intro.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative iterator_forward.cc %}
{% endhighlight %}

## A bidirectional iterator

A bidirectional iterator is a forward iterator with an extra operation
defined: `--i`, i.e., move back by one element.  The iterator of
`std::list` is a bidirectional iterator.  For example:

{% highlight c++ %}
{% include_relative iterator_bidirectional.cc %}
{% endhighlight %}

## A random-access iterator

A random-access iterator allows for increasing or decreasing the
iterator value by any integer, as we've done in the example above with
the deque.  The iterator of the vector is a random-access iterator.  A
pointer is a random-access iterator too.

# Forward-iterating over the elements of a container

We can forward-iterate over the elements of a container (or, more
broadly, a range) in two ways: the old, and the new.

## Iterating the old way

As shown in the example below, you can forward-iterate over the
elements of a container the old way, which is a bit tedious, because
we have to initialize the *iteration variable* `i`, write the loop
condition, and then increment the variable.  This loop is also
error-prone, as it's easy to mistakenly write '--i' instead of '++i',
or `begin` instead of `end`.

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
  container here.  Having the range expression, we can get the values
  of the begin and end iterators.

* `statement` is the statement executed in every iteration of the
  loop.  In that statement we use the declared variable.

An example:

{% highlight c++ %}
{% include_relative iterate_new.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative range.cc %}
{% endhighlight %}

# Containers and element management

We can copy or move an element into a container.  We can also move it
from a container, except for the associative containers, for which we
can extract an element.  We can also **emplace** an element in a
container.

Containers have the move semantics implemented.  An example:

{% highlight c++ %}
{% include_relative container_move.cc %}
{% endhighlight %}

## Move semantics for element types

We can move elements into containers: it's enough to make sure that
the element we insert is used in an rvalue.  We can also move from an
element of a sequence container.  Example:

{% highlight c++ %}
{% include_relative element_move.cc %}
{% endhighlight %}

## Extract

We cannot move an element from an *associative container*, because we
cannot modify that element, even if we are using a non-const iterator,
as the type of the element is const.  We shouldn't even move, because
the object we would move from would not be part of the container any
longer, as it would have to be in the case of, e.g., a vector.  We
should **extract** the element.  Extraction is supported only by the
associative containers, because it's needed only there.

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

{% highlight c++ %}
{% include_relative extract.cc %}
{% endhighlight %}

## Emplace

An element can be copied, moved, or *emplaced* into a container.
Copying is needed when we want to keep the source element intact.
Moving is faster, and so preferred over copying, if the source won't be
needed later.  In both copying and moving, we create an object
ourselves, and then pass it to a container.  Emplacing creates an
object based on the arguments we provide.

Emplacing is the fastest: a container tries to create the element in
the required place: the element is created *in-place*, i.e., in the
place (memory location) required by the container.  No copying, no
moving... if all goes well.

An emplace function takes the arguments of an element constructor, and
passes them (forwards, technically speaking) to the constructor when
it's known where (i.e., the place is known) the element should be
constructed.

We emplace by calling an `emplace` function of a container.
Containers have other functions for emplacing with slight semantic
differences, e.g., `std::list` has `emplace_front`, and
`std::forward_list` has `emplace_after`.

Emplacement works similar to insertion in that the elements that
follow are "pushed to the right".  Therefore emplacement entails the
same performance issues as the insertion does.

A container **tries** to emplace the element.  Tries, because the
place for the element might be already taken by some other element,
e.g., when we emplace at the front of a non-empty vector.  If that
happens, the new element is created in a different memory location,
and then moved into the required place.

{% highlight c++ %}
{% include_relative emplace.cc %}
{% endhighlight %}

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
