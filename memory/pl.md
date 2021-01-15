---
title: Organizacja pamięci
---

# Wprowadzenie

C++ przetwarza dane typów *wbudowanych* (np. `int`, `long double`)
albo *zdefiniowanych przez użytkownika* (np., `struct A`, `struct B`,
`enum C`, `union D`).  Standard C++ opisuje:

* kiedy dane są tworzone i niszczone,

* gdzie (w którym miejscu pamięci, w jakiej strukturze danych) dane
  się znajdują,

* jak dane są przekazywane do funkcji i jak są zwracane przez funkcję.

C++ musi spełniać podstawowe wymagania systemu operacyjnego dotyczące
organizacji pamięci, a reszta zależy do C++.

## Podstawowe wymagania systemu operacyjnego

Uruchomiony *program* jest *procesem* w systemie operacyjnym i
*zadaniem* wykonywanym przez procesor.  Proces zarządza swoją pamięcią
zgodnie z ograniczeniami systemu operacyjnego.  System operacyjny daje
procesowi do dyspozycji dwa rodzaje pamięci: *tylko do odczytu* oraz
*do zapisu i odczytu*.

Pamięć tylko do odczytu przechowuje kod programu (rozkazy procesora) i
dane stałe programu znane w czasie kompilacji, np. literały
łańcuchowe.  Ta pamięć jest współdzielona przez wszystkie procesy
programu, co znacząco oszczędza pamięć w przypadku dużych programów
uruchamianych w dużej liczbie, np. przglądarek czy serwerów
internetowych.

Zadanie może być uprzywilejowane albo nieuprzywilejowane.  Tylko
zadania jądra systemu operacyjnego są uprzywilejowane.  Procesy są
zadaniami nieuprzywilejowanymi.  *Zadanie nieuprzywilejowane* nie może
naruszyć danych innych zadań, w szczególności nie może pisać do swojej
pamięci tylko do odczytu.

W poniższym przykładzie próbujemy pisać do literału łańcuchowego,
który jest znajduje się w pamięci tylko do odczytu.  Program się
kompiluje, ale proces jest unicestwiony przez system operacyjny
sygnałem SIGSEGV (segment violation).

{% highlight c++ %}
{% include_relative sigsegv.cc %}
{% endhighlight %}

All other data is located in the read-write memory, because it can be
changed by a process.  Every process has its own read-write memory,
even when there are many processes of the same program.

## What is up to C++

C++ strives for time and memory performance, and that is reflected in
the memory organization by, e.g., using pointers (C++ keeps close to
hardware).  Furthermore, C++ also strives for a flexible control over
data management by, e.g., allowing a programmer to allocate an object
statically, globally, locally or dynamically.  Finally, the C++ memory
organization is also *deterministic*: we know exactly when and where
the data are *destroyed* (so that they are destroyed as soon as no
longer needed).

C++ is in stark contrast with other languages, such as Java or C#,
where object management is simplified at the cost of performance, and
the lack of flexible control.  For instance, such languages allow
allocation of objects on the heap only, which deteriorates performance
and flexibility, but enables easy implementation of garbage
collection.  Some garbage collectors are even further inefficient,
because they are *nondeterministic*, i.e., it is undefined when data
are destroyed.

In the past, the C++ Standard Committee considered the garbage
collection support, but dropped it for performance reasons.  Nowadays,
C++ requires no garbage collection since it offers advanced container
and smart pointer support, which could be considered a form of garbage
collection.

# Data and their location

The read-write memory stores:

* global and static data in a location of fixed size,

* local data on a stack (more specifically, a stack per thread of the
  process); a stack can be of fixed size or can grow (i.e., the
  operating system can allocate more memory for it),

* dynamic data on the heap (a.k.a a free-store); a heap can grow.

## The global and static data

Global data are initialized before entering the main function:

{% highlight c++ %}
{% include_relative global.cc %}
{% endhighlight %}

Static data are initialized before its first use:

{% highlight c++ %}
{% include_relative static.cc %}
{% endhighlight %}

In the example above remove `static`, and notice the changes in the
program output.

## The local data

All data local to a function or a block scope is allocated on the
stack.  The local data is automatically destroyed when it goes out of
scope.  It's not only a great property you can rely on to have your
data destroyed, but also a necessity since the stack has to be cleaned
up when the scope ends.

Data created locally are destroyed in the reverse order of their
creation, because the stack is a FILO (first in, last out) structure.

{% highlight c++ %}
{% include_relative local.cc %}
{% endhighlight %}

## The dynamic data

Dynamic data are created on the heap, and should be managed by *smart
pointers*, which in turn use the low-level functionality of the `new`
and `delete` operators provided for *raw pointers*.

Data created with the `new` operator has to be eventually destroyed by
the `delete` operator, otherwise we get a memory leak.  We cannot
destroy the same data twice, otherwise we get undefined behavior
(e.g., a segmentation fault, bugs).

A programmer should use the smart pointers, which is error-safe but
hard.  In contrast, using raw pointers is error-prone (often resulting
in vexing heisenbugs) but easy.  Since smart pointers are the C++11
functionality, modern code uses the smart pointers, and the legacy
code the raw pointers.

The following example uses the low-level `new` and `delete` operators,
which is not recommended, but suitable to demonstrate the dynamic
allocation.

{% highlight c++ %}
{% include_relative dynamic.cc %}
{% endhighlight %}

## Local vs dynamic data

Allocation on the stack is fast: it's only necessary to increase (or
decrease, depending on the system architecture) the stack pointer
(a.k.a. the stack register) by the size of the data needed.  *No
memory allocation is faster.* If an operating system supports it, the
stack can have more memory allocated automatically when needed, i.e.,
without the process requesting is explicitly.

The following code tests how big a stack is, and whether an operating
system automatically allocates more memory for the stack.  A function
calls itself and prints the number of how many times the function was
recursively called.  If we see small numbers (below a million) when
the process is terminated, the operating system does not automatically
allocate more memory for the stack.  If we see large numbers (above a
million or far more), then the operating system most likely
automatically allocates more memory for the stack.

{% highlight c++ %}
{% include_relative stack_test.cc %}
{% endhighlight %}

Allocation on the heap is slow, because it's a complex data structure
which not only allocates and deallocates memory of an arbitrary size,
but also deals with defragmentation, and so several memory reads and
writes are necessary for an allocation.  An operating system allocates
more memory for the heap, when the process (i.e., the library, which
allocates memory) requests it.

Data located on the stack is packed together according to when the
data was created, and so data that are related are close to each
other.  This is called *localization*.  And localization is good,
because the data that a process needs is most likely already in the
processor memory cache (which caches memory pages), speeding up the
memory access manyfold.  Data allocated on the heap are less
localized, i.e., they are more likely to be spread all over the heap
memory, which slows down the memory access, as quite likely the data
is not in the processor memory cache.

# Function calls

When calling a function we pass an argument by either value or
reference.  Also, a function can return its result by either value or
reference.

## Passing arguments

In C++ arguments are always passed either *by value* or *by
reference*.

If a parameter of a function is of a non-reference type, we say that a
function takes an argument by value, or that we pass an argument to a
function by value.  The argument (i.e., the argument expression) is
used to initialize the parameter, which in the legacy C++ always
entailed copying the data from the argument to the parameter.

If a parameter of a function is of a reference type, we say that a
function takes an argument by reference, or that we pass an argument
to a function by reference.  The reference parameter is initialized by
the argument expression.  The parameter becomes a name (an alias) for
the data of the argument expression.

This example shows how we pass arguments by value and by reference.
Compile the example with the flag `-fno-elide-constructors`.

{% highlight c++ %}
{% include_relative args.cc %}
{% endhighlight %}

## Returning values

A function can return a result either by value or reference.

If the return type is of a non-reference type, we say that a function
returns the result by value.  In the deep past (before C++ was
standardized) that always entailed copying the result (i.e., the data
local to the function) from one location on the stack to a temporary
on the stack, and then to its final location, e.g., a variable.

If the return type is of a reference type, we say that a function
returns the results by reference.  The reference should be bound to
data that will exist when the function returns (i.e., the data should
outlive the function).  Containers (e.g., `std::vector`), for
instance, return a reference to dynamically-allocated data in, for
instance, `operator[]` or `front` functions.

This example shows how to return results by value and by reference.
Compile the example with the flag `-fno-elide-constructors`.

{% highlight c++ %}
{% include_relative return.cc %}
{% endhighlight %}

# Function call convention

The technical details on how exactly a function is called is known as
the *call convention*, which depends on the system architecture, the
operating system, and the compiler.  C++ does not specify a call
convention, but some C++ functionality (like the constructor elision
and the return value optimization) follows from a typical call
convention.

Typically, a call convention requires that the caller of the function
(i.e., the code that calls the function):

* creates the function parameters on the stack,

* allocates memory for the return value on the stack.

Small data may be passed or returned in processor registers.  For
instance, if a function returns an integer, the return value can be
returned in a register, e.g., EAX for x86, Linux, and GCC.

Legacy call conventions required the memory for the return value be
the last data on the stack before a function was called, so that it
could located with the pointer register.  This, however, entailed
copying of the return value from that temporary (the last on the
stack) location to its final destination, e.g., a local variable.

Modern call conventions allow the memory for the return value be
allocated anywhere in memory (on the stack, on the heap, or in the
fixed-size memory for the static and global data), and the address be
passed to a function in a processor register (e.g., RDI for x86,
Linux, and GCC), so that the function can create the return value in
the pointed location.

The following example demonstrates that the return value can be
created anywhere (as the modern call convention allows), and not only
on the stack (as the legacy call convention stipulated).  In the
example a function returns an object which is created directly in the
memory location for global and static data, without copying the object
from the stack as the legacy call convention would require.

{% highlight c++ %}
{% include_relative mcc.cc %}
{% endhighlight %}

# Constructor elision

C++ elides (avoids) constructors (specifically, two constructors: the
copy constructor, and the *move* constructor) for temporary or local
objects that would soon be destroyed.  Instead of creating a
temporary, the object is created in the final location where it would
end up.

This example that demonstrates the constructor elision.  Compile the
example with, then without the flag `-fno-elide-constructors`.  Notice
the differences at run-time.

{% highlight c++ %}
{% include_relative elide.cc %}
{% endhighlight %}

Compile the previous examples of passing arguments to and returning
results from functions but without disabling the constructor elision.
Notice that with constructor elision, objects are not copied
unnecessarily.

When a temporary is passed by value as an argument, that temporary is
created directly (i.e., with the constructor elided) in the location
of the function parameter.

# Return value optimization

When a result is returned by value from a function, it can be created
directly (i.e., with the constructor elided) in the location for the
return value.  This is known as the return value optimization (RVO).

RVO not always can take place, because of technical reasons.  First,
because we return data, which has to be created prior to deciding
which data exactly to return:

{% highlight c++ %}
{% include_relative rvo_no1.cc %}
{% endhighlight %}

Second, because we try to return a function parameter, which was
created by the caller, not the function, and so the function cannot
create the parameter in the location for the return value:

{% highlight c++ %}
{% include_relative rvo_no2.cc %}
{% endhighlight %}

Finally, because we try to return static or global data, which has to
be available after the function returns, and so the function can only
copy the result from the static or global data:

{% highlight c++ %}
{% include_relative rvo_no3.cc %}
{% endhighlight %}

# Conclusion

Data can be allocated statically, globally, locally or dynamically.

Allocating memory for local data (on the stack) is ultra fast, while
for dynamic data (on the heap) is much slower.

Don't use the dynamically-allocated data, if local data is good
enough.

Passing parameters or return results by value is not that bad, because
most likely their copying or moving will be elided.

# Quiz

* Is memory allocation on the stack faster than on the heap?

* Where can we allocate objects?

* What is the return value optimization?

{% include rid %}

<!-- LocalWords: enum  sigsegv endhighlight heisenbugs -->
<!-- LocalWords: deallocates defragmentation manyfold args -->
<!-- LocalWords: EAX RDI RVO SIGSEGV -->
