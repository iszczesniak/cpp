---
title: Memory organization
---

# Introduction

C++ processes *data* of *built-in* types (e.g., `int`, `long double`)
or *user-defined* types (e.g., `struct A`, `class B`, `enum C`, `union
D`).  The C++ standard describes:

* when data is created and destroyed,

* where (i.e., what part of memory, what data structure) data is
  located.

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

In the following example we try to write to the read-only memory --
please uncomment some lines.  The code compiles, but is killed by the
operating system with the SIGSEGV (segment violation) signal.

```cpp
{% include_relative sigsegv.cc %}
```

We can check the location of the variables with the command below.
Notice the 'r' in the output for the read-only memory:

```
nm ./sigsegv | c++filt | grep test
```

All other data is located in the read-write memory, because it can be
changed by a process.  Every process has its own read-write memory,
even when there are many processes of the same program.

## What is up to C++

C++ strives for time and memory performance, and that is reflected in
the memory organization by, e.g., using pointers (C++ keeps close to
hardware).  Furthermore, C++ also strives for a flexible control over
data management by, e.g., allowing a programmer to allocate data
globally, statically, locally or dynamically.  Finally, the C++ memory
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

Global data are initialized before entering the `main` function, and
are available everywhere in the program:

```cpp
{% include_relative global.cc %}
```

Static data are initialized before its first use, and are local to a
function (i.e., unavailable elsewhere):

```cpp
{% include_relative static.cc %}
```

In the example above remove `static`, and notice the changes in the
program output.

The global and static variables seem very similar in that they keep
data between calls to a function.  However, there are two reasons for
using a static over a global variable:

* a static variable is initialized only when needed (when we call a
  function), while a global variable is always initialized, which may
  be a performance hit if the variable is unused,

* keep the code tidy and less error-prone.

## The local data

Data local to a function or a block scope are created on the stack.
The local data is automatically destroyed when it goes out of scope.
It's not only a great property you can rely on to have your data
destroyed, but also a necessity since the stack has to grow smaller
when a scope ends.

Data created locally are destroyed in the reverse order of their
creation, because the stack is a FILO (first in, last out) structure.

```cpp
{% include_relative local.cc %}
```

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

```cpp
{% include_relative dynamic.cc %}
```

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

```cpp
{% include_relative stack_test.cc %}
```

Allocation on the heap is slow, because it's a complex data structure
which not only allocates and deallocates memory of an arbitrary size,
but also deals with defragmentation, and so several memory reads and
writes are necessary for an allocation.

An operating system allocates more memory for the heap, when the
process (i.e., the library which allocates memory) requests it.  A
heap can grow to any size, only limited by an operating system.  When
finally an operating system refuses to allocate more memory, the `new`
operator throws `std::bad_alloc`.  Here's an example:

```cpp
{% include_relative heap_test.cc %}
```

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
reference.  Compile the example with the flags
`-fno-elide-constructors -std=c++14` (a flag of the GCC compiler), so
that the compiler does not elide constructors.  If you compile your
code with C++17 (e.g., with `-std=c++17` in GCC) or higher, your
request to disable constructor elision may be ignored by the compiler,
because constructor elision in some cases is mandatory since C++17.

```cpp
{% include_relative args.cc %}
```

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
returned by value is not copied.  To see the legacy C++ behviour,
compile the example with the flag `-fno-elide-constructors
-std=c++14`.  Where and why are objects copied?  That depends on the
function call convention, constructor elision, and return value
optimization.

```cpp
{% include_relative return.cc %}
```

# Function call convention

The *call convention* are the technical details on how exactly a
function is called, which depend on the platform (the system
architecture, the operating system, and the compiler).  C++ does not
specify a call convention, but some C++ functionality (like the
constructor elision and the return value optimization) follows from a
typical call convention.

A regular C++ programmer doesn't have to know such details, but
mentioning them is worthwhile to understand that C++ is a part of
computer systems that evolve.  In that evolotion, C++ must be binary
compatible with C (so that C++ can call C functions), where new C++
functionality can be implemented on supported platforms.

There are many call conventions that depend mostly on the processor
capabilities.  Typically, a call convention requires that the caller
of the function (i.e., the code that calls the function):

* creates the function parameters on the stack,

* allocates memory for the return value.

Parameters are created on the stack because a processor might be
unable to store them (in registers).  The caller allocates memory for
the return value because it may not fit in a processor, yet it should
be available to the caller once the function returns.

Small data may be passed or returned in processor registers.  For
instance, a function can take an argument or return as a result an
integer in a register, e.g., EAX for x86, Linux, and GCC.

In the legacy call convention, a function returned its result in a
temporary place at the top of the stack, which was easy to locate with
the stack register -- that was an advantage.  A disadvantage it was to
copy the result from the temporary place to its destination, e.g., a
variable that was assigned the result.

The modern call convention allows the place for the return value be
allocated anywhere in memory (not only on the stack, but also on the
heap, or in the memory for the global and static data), and passing to
a function the address of the place, so that the function can create
the return value at the place pointed.  We don't need a temporary
place anymore.  For instance, for x86, Linux, and GCC, the address is
passed to a function on the stack last, while to a constructor in the
RDI register.

The following example demonstrates that a result can be returned
anywhere (as the modern call convention allows), and not only on the
stack (as the legacy convention stipulated).  In the example the
function returns an object directly in the place of memory for global
and static data, without copying the object using a temporary place
required by the legacy call convention.

```cpp
{% include_relative mcc.cc %}
```

# Constructor elision

C++ elides (avoids) the copy constructor, and the *move* constructor
for temporary or local objects that will soon be destroyed.
Constructor elision (for the copy and move constructors only) is
possible, because the temporary and the local object is created in its
destination.

This example that demonstrates the constructor elision.  Compile the
example with, then without the flag `-fno-elide-constructors`.  Notice
the differences at run-time.

```cpp
{% include_relative elide.cc %}
```

Compile the various previous examples of passing arguments to and
returning results from functions but without disabling the constructor
elision.  Notice that with constructor elision, objects are not copied
(nor moved) unnecessarily.

When a temporary is passed by value as an argument, that temporary is
created directly (i.e., with the constructor elided) in the location
of the function parameter.

# Return by value

A result can be returned by a function directly in its destination,
e.g., a variable to which the result is assigned.  The idea is to
create the result in its destination, so that it doesn't have to be
copied or moved there, i.e., to elide constructors.  **When returning
by value, constructor elision requires the modern call convention.**

This functionality is a C++17 feature, but prior to C++17 it was known
as the return value optimization (RVO), because it was an optional
feature of a compiler optimizer.  Since C++17, the copy and move
constructors can be unavailable if they are elided, and therefore the
following code is valid for C++17 (GCC option `-std=c++17`), but not
for C++14 (GCC option `-std=c++14`):

```cpp
{% include_relative rvo_or_not.cc %}
```

This functionality not always can take place, because of technical
reasons.  First, because we return data, which has to be created prior
to deciding which data exactly to return:

```cpp
{% include_relative rvo_no1.cc %}
```

Second, because we try to return a function parameter, which was
created by the caller, not the function, and so the function cannot
create the parameter in the location for the return value:

```cpp
{% include_relative rvo_no2.cc %}
```

Finally, because we try to return global or static data, which has to
be available after the function returns, and so the function can only
copy the result from the global or static data:

```cpp
{% include_relative rvo_no3.cc %}
```

# Conclusion

* Data can be allocated globally, statically, locally or dynamically.

* Allocating memory on the stack is ultra fast, while on the heap is
  much slower.

* Don't use the dynamically-allocated data, if local data is good
  enough.

* Nowadays passing parameters or returning results by value is
  efficient, because the value is not copied (nor moved)
  unnecessarily.

# Quiz

* Is memory allocation on the stack faster than on the heap?

* Where can we allocate objects?

* What is the return value optimization?

{% include rid %}

<!-- LocalWords: enum sigsegv heisenbugs -->
<!-- LocalWords: deallocates defragmentation manyfold args -->
<!-- LocalWords: EAX RDI RVO SIGSEGV -->
