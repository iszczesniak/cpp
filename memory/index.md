---
title: Memory organization
---

# Introduction

C++ processes *data* of *built-in* types (e.g., `int`, `long double`)
or *user-defined* types (e.g., `struct A`, `class B`, `enum C`, `union
D`).  The C++ standard describes:

* when data is created and destroyed,

* where (i.e., what part of memory, what data structure) data is
  located,

* how data is passed to and returned from a function.

The C++ memory organization has to respect the basic requirements of
an operating system, but the rest is up to C++.

## The basic requirements of an operating system

When we run a *program*, it becomes a *process* of an operating
system, and a *task* a processor is executing.  A process manages its
memory within the limits imposed by the operating system.  An
operating system offers a process two types of memory: *read-only*,
and *read-write*.

The read-only memory stores the code of the program (i.e., the
processor instructions), and the const data known at compile time,
e.g., string literals.  This memory is shared by all processes of the
same program, which can be a substantial saving for a large program
run in a large number (e.g., a web server).

An *unprivileged* task (a *privileged* task is a kernel task, i.e., a
task of an operating system) cannot do anything that could disturb the
operating system and other processes.  For instance, an unprivileged
task cannot write to its read-only memory.  Every process is an
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

C++ strives for time and memory performance, and that is reflected in
the memory organization by, e.g., using pointers (C++ keeps close to
hardware).  Furthermore, C++ also strives for a flexible control over
data management by, e.g., allowing a programmer to allocate data
statically, globally, locally or dynamically.  Finally, the C++ memory
organization is also *deterministic*: we know exactly when and where
the data are *destroyed* (so that they are destroyed as soon as no
longer needed).

C++ is in stark contrast with other languages, such as Java or C#,
where data management is simplified at the cost of degraded
performance, and constrained management of data.  For instance, such
languages allow allocation of data on the heap only, which
deteriorates performance and flexibility, but enables easy
implementation of garbage collection.  Some garbage collectors are
even further inefficient, because they are *nondeterministic*, i.e.,
it is undefined when data are destroyed.

The C++ Standard Committee considered the garbage collection support,
but dropped it for performance reasons.  Nowadays, C++ requires no
garbage collection since it offers advanced container and smart
pointer support, which could be considered a form of garbage
collection.

# Data and their location

The read-write memory stores:

* global and static data in a location of fixed size,

* local data on a stack (more specifically, a stack per thread of the
  process),

* dynamic data on the heap (a.k.a the free-store).

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

Data local to a function or a block scope are created on the stack.
The local data is automatically destroyed when it goes out of scope.
It's not only a great property you can rely on to have your data
destroyed, but also a necessity since the stack has to grow smaller
when a scope ends.

Data created locally are destroyed in the reverse order of their
creation, because the stack is a FILO (first in, last out) structure.

{% highlight c++ %}
{% include_relative local.cc %}
{% endhighlight %}

## The dynamic data

Dynamic data are created on the heap, and should be managed by *smart
pointers*, which in turn use the low-level functionality of *raw
pointers*, most notably the `new` and `delete` operators.

Data created with the `new` operator has to be eventually destroyed by
the `delete` operator to avoid a memory leak.  We cannot destroy the
same data twice, otherwise we get undefined behavior (e.g., a
segmentation fault, bugs).

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

Allocation on the stack is the fastest: it's only necessary to
increase (or decrease, depending on the processor architecture) the
stack pointer (a.k.a. the stack register) by the size of the memory
needed.

A stack can be of fixed size or it can grow automatically: more memory
can be allocated for the stack without the process requesting it
explicitly, if an operating system can do this.  If not, the process
is killed with an error in the case of stack overflow.

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
writes are necessary for an allocation.

An operating system allocates more memory for the heap, when the
process (i.e., the library which allocates memory) requests it.  A
heap can grow to any size, only limited by an operating system.  When
finally an operating system refuses to allocate more memory, the `new`
operator throws `std::bad_alloc`.  Here's an example:

{% highlight c++ %}
{% include_relative heap_test.cc %}
{% endhighlight %}

Data on the stack are packed together according to when the data was
created, and so data that are related are close to each other.  This
is called *data colocation*.  And colocation is good, because the data
that a process (more specifically, some function of the process) needs
at a given time is most likely already in the processor memory cache
(which caches memory pages), speeding up the memory access manyfold.

Data allocated on the heap are less colocated (in comparison with the
stack): they are more likely to be spread all over the heap memory,
which slows down memory access, as quite likely the data is not in the
processor memory cache.

# Function calls

When calling a function we pass an argument by either value or
reference.  Also, a function can return its result by either value or
reference.  There are no other ways of passing an argument or
returning a value.

A function has *parameters*, and we call a function with *arguments*.
A parameter is available inside the function.  A parameter has a type
and a name given in the function declaration or definition.  An
argument is an expression that is part of a call expression.  A
parameter is initialized using an argument.

## Passing arguments

If a function parameter is of a non-reference type, we say that a
function takes an argument by value, or that we pass an argument to a
function by value.  In legacy C++, a nonreference parameter was
initialized by copying the argument value into the parameter.

If a function parameter is of a reference type, we say that a function
takes an argument by reference, or that we pass an argument to a
function by reference.  Initialization makes the parameter a name (an
alias) for the argument data.

The example below shows how we pass arguments by value and by
reference.  Compile the example with the flag
`-fno-elide-constructors` (a flag of the GCC compiler), so that the
compiler does not elide constructors.

{% highlight c++ %}
{% include_relative args.cc %}
{% endhighlight %}

## Returning a result

If the return type is of a non-reference type, we say that a function
returns the result by value.  In modern C++ returing by value is fast,
does not impose any unnecessary overhead, and therefore is
recommended.  It's not what it used to be in the deep past, before C++
was standardized.

Back then returning by value always copied the result twice.  First,
from a local variable of the function to a temporary place on the
stack for the return value.  Second, from the temporary place to the
final place, e.g., a variable to which the result was assigned.

If the return type is of a reference type, we say that a function
returns the result by reference.  The reference should be bound to
data that will exist when the function returns (i.e., the data should
outlive the function).  Containers (e.g., `std::vector`), for
instance, return a reference to dynamically-allocated data in, for
instance, `operator[]` or `front` functions.

The example below shows how to return a result by value and by
reference.  On a modern system with a modern compiler, a result
returned by value is not copied.  To see some legacy C++ behviour,
compile the example with the flag `-fno-elide-constructors`.  Where
and why are objects copied?  That depends on the function call
convention, constructor elision, and return value optimization.

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
can be located with the stack register.  This, however, entailed
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
