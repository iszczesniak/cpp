---
title: Memory model
---

# Introduction

C++ processes *data* of *built-in* types (e.g., `int`, `long double`)
or *user-defined* types (e.g., `struct A`, `class B`, `enum C`, `union
D`).  The memory model of C++ describes:

* when data is created and destroyed,

* where (i.e., what part of memory, what data structure) data is
  located,

* how data is passed to and returned from a function (which is called
  the call convention).

The memory model of C++ has to respect the basic requirements of an
operating system, but the rest is up to C++.

## The basic requirements of an operating system

When we run a *program*, it becomes a *process* in an operating
system, and a *task* a processor is executing.  A process manages its
memory within the limits imposed by the operating system.  An
operating system offers a process two types of memory: *read-only*,
and *read-write*.

The read-only memory stores the code of the program (i.e., the
processor instructions), and the static data (e.g., string literals).
This memory is shared by all processes of the same program, which can
be a substantial saving for a large program run in a large number
(e.g., Google Chrome).

An *unprivileged* task (a *privileged* task is a kernel task, i.e., a
task of an operating system) cannot do anything that could disturb the
operating system and other processes.  For instance, an unprivileged
task cannot write to its read-only memory.  Every processes is an
unprivileged task.

In the following example we try to write to the read-only memory.  The
code compiles, but is killed by the operating system with the SIGSEGV
(segment violation) signal.

{% highlight c++ %}
{% include_relative sigsegv.cc %}
{% endhighlight %}

All other data is located in the read-write memory, because it can be
changed by a process.  Every process has its own read-write memory,
even when there are many processes of the same program.

## What is up to C++

The C++ standard describes how data are managed in the read-write
memory.  C++ strives for time and memory performance, and that is
reflected in the memory model by, e.g., using pointers (keeping close
to hardware).  Furhermore, C++ also strives for a flexible control
over data management by, e.g., allowing a programmer to allocate an
object statically, globally, locally or dynamically.  Finally, the
memory model of C++ is also *deterministic*: we know exactly when and
where the data are *destroyed* (so that they are immediatelly
destroyed when necessary).

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
and smart pointer support, so that data are automatically destroyed
when necessary (which could be considered a form of garbage
collection).

# Data and their location

The read-write memory stores:

* global and static data in a location of fixed size,

* local data at a stack (more specifically, a stack per thread of the
  process); a stack can be of fixed size or can grow (i.e., the
  operating system can allocate more memory for it),

* dynamic data at the heap (a.k.a a free-store); a heap can grow.

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
destroy the same data twice, otherwise we get undefined behaviour
(e.g., a segmentation fault, bugs).

For regular use, a programmer should use the smart pointers, which are
error-safe but hard to use.  In contrast, raw pointers are error-prone
but easy to use.  Since smart pointers are C++11 functionality, modern
code uses the smart pointers, and the legacy code the raw pointers.

The following example uses the low-level `new` and `delete` operators,
which is not recommended, but suitable to demonstrate the dynamic
allocation.

{% highlight c++ %}
{% include_relative dynamic.cc %}
{% endhighlight %}

## Local vs dynamic data

Allocation on the stack is fast: it's only necessary to increase (or
decrease, depending on the processor type) the stack pointer
(a.k.a. the stack register) by the size of the data needed.  *No
memory allocation is faster.* If an operating system supports is, the
stack can have more memory allocated automatically when needed, i.e.,
without the process requesting is explicitly.

The following code tests how big a stack is, and whether an operating
system automaticall allocates more memory for the stack.  A function
calls itself and prints the number of how many times the function was
recursivelly called.  If we see small numbers (below a million) when
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
other.  This is called localization.  And localization is good,
becasue the data that a process needs is most likely already in the
processor memory cache (which caches memory pages), speeding up the
memory access manyfold.  Data allocated on the heap are usually not
localized, i.e., they are spead all over the heap memory, which slows
down memory access, as most likely the data is not in the processor
memory cache.

# Function calls

When calling a function we pass an argument by either value or
reference.  Also, a function can return its result by either value or
reference.

## Passing arguments

In C++ arguments are always passed *by value* or *by reference*.

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
returns the result by value.  In the deep past that always entailed
copying the result from one location at the stack to a temporary on
the stack, and then usually to its final resting place, e.g., a
variable.

If the return type is of a reference type, we say that a function
returns by reference.  The reference should be bound to data that will
exist when the function returns (i.e., the data should outlive the
function).  Containters (e.g., `std::vector`), for instance, return a
reference to dynamically-allocated data in, for instance, `operator[]`
or `front` functions.

This example shows how to return a result by value and by reference.
Compile the example with the flag `-fno-elide-constructors`.

{% highlight c++ %}
{% include_relative return.cc %}
{% endhighlight %}

# Constructor elision

Since C++11, C++ elides (avoids) constructors (i.e., the copy
constructor, and the *move* constructor) for temporary or local
objects that would soon be destroyed.  Instead of creating a
temporary, an object is created in the final location where it would
end up.

This is a simple example that demonstrates a constructor elision.
Compile the example with, then without the flag
`-fno-elide-constructors`.  Notice the differences at run-time.

{% highlight c++ %}
{% include_relative elide.cc %}
{% endhighlight %}

Compile the examples of passing arguments and returning values from
functions but without disabling the constructor elision.  Notice the
differences.

Prior to C++11, return value optimization (RVO) tried to elide
constructors for data returned from functions by value.

# Conclusion

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->
