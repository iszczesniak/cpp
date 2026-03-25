---
title: Memory organization
---

# Introduction

C++ processes *data* of *fundamental types* (aka *built-in* types,
e.g., `int`, `long double`) or *user-defined* types (e.g., `struct A`,
`class B`, `enum C`, `union D`).  The C++ standard describes:

* when data is created and destroyed,

* where (i.e., what part of memory, what data structure) data is
  located.

The C++ memory organization has to respect the basic requirements of
an operating system, but the rest is up to C++.

## Basic requirements of an operating system

When we run a *program*, it becomes a *process* of an operating
system, and a *task* a processor is executing.  A process manages its
memory within the limits imposed by the operating system.  An
operating system offers a process two types of memory: *read-only* and
*read-write*.

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

## Move semantics, mentioned in passing

We need to mention here the *move semantics*, something that we'll
look into later.  For now, it's enough to know that *moving* sometimes
replaces *copying*.  A value is copied when copy-construcing (or
copy-assigning to) some other (target) object by using the copy
constructor (or the copy-assignment operator).  A value is moved when
move-construcing (or move-assigning to) some other (target) object by
using the move constructor (or the move-assignment operator).

In the examples that follow we use structure `A` that lets us see when
an object is constructed, copied, moved, accessed (by calling function
`hello`) and destroyed.  Please note (take a look at the file
`GNUmakefile`) that file `A.cpp` is separately compiled, and then
linked with the examples.

Here's the declaration (file `A.hpp`):

```cpp
{% include_relative A.hpp %}
```

Here's the definition (file `A.cpp`):

```cpp
{% include_relative A.cpp %}
```

# Data and their location

The read-write memory stores:

* global and static data in a location of fixed size,

* local data on a stack (more specifically, a stack per thread of the
  process),

* dynamic data on the heap (a.k.a the free-store).

## Global and static data

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

## Local data

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

## Dynamic data

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

## Emplacement

The placement `new` operator creates an object (or a value of some
non-class type) "in place", i.e., in the place pointed to with a
pointer that we pass in parentheses right after `new`.  That version
of the operator does not allocate memory, so it has nothing to do with
the dynamic data.  This operation is called **emplacement**.

```cpp
{% include_relative placement.cc %}
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
is called *data collocation*.  And collocation is good, because the
data that a process (more specifically, some function of the process)
needs at a given time is most likely already in the processor memory
cache (which caches memory pages), speeding up the memory access
manyfold.

Data allocated on the heap are less collocated (in comparison with the
stack): they are more likely to be spread all over the heap memory,
which slows down memory access, as quite likely the data is not in the
processor memory cache.

# Function calls

A function accepts an argument by either value or reference.  Also, a
function returns its result by either value or reference.  There are
no other ways of accepting an argument or returning a value.

A function can have *parameters*, and then we call a function with
*arguments*.  A function parameter is local to a function body, like a
local variable.  A parameter has a type and a name given in the
function declaration or definition.  An argument is an expression that
is part of a call expression.

A parameter is initialized with an argument.  A result is initialized
with the expression of the return instruction.

## Accepting arguments

If a function parameter is of a non-reference type, we say that a
function accepts (or takes) an argument by value, or that we pass an
argument to a function by value.  In legacy C++, a nonreference
parameter was initialized always by copying the argument value into
the parameter.  In modern C++, that copying might be gone (because of
the temporary materialization) or replaced with *moving*.

If a function parameter is of a reference type, we say that a function
accepts an argument by reference, or that we pass an argument to a
function by reference.  Initialization makes the parameter a name (an
alias) for the argument data.

The example below shows how to accept an argument either by value or
by reference.

```cpp
{% include_relative args.cc %}
```

## Returning a result

If the return type is a non-reference type, we say that a function
returns the result by value.  If the return type is a reference type,
we say that a function returns the result by reference.  The reference
should be initialized with data that will exist when the function
returns (i.e., the data should outlive the function).  For instance,
containers (e.g., `std::vector`) offer functions (e.g., `operator[]`
or `front`) that return references to dynamically-allocated data.

The example below shows how to return a result either by value or by
reference.

```cpp
{% include_relative return.cc %}
```

# Returning by value

In modern C++, returing by value is fast, does not impose any
unnecessary overhead, and therefore is recommended.  It's not what it
used to be in the deep past, before C++ was standardized.  Back then
returning by value always copied the result twice.  First, from a
local variable of the function to a temporary place on the stack for
the return value.  Second, from the temporary place to the
destination, e.g., a variable that was initialized with the result.

To understand how returning by value became efficient, and to be aware
of exceptions, we need to understand the call conventions, the
constructor elision, and the temporary materialization.

## Function call convention

The *call convention* are the technical details on how exactly a
function is called, which depend on the platform (the system
architecture, the operating system, and the compiler).  C++ does not
specify a call convention (that's the operating system business), but
some C++ functionality (like the constructor elision) depends on a
call convention.

A regular C++ programmer maybe doesn't have to know such details, but
knowing them is worthwhile not only to use C++ better, but also to
understand that C++ is a part of computer systems that evolve.  In
that evolotion, C++ must be binary compatible with C (so that C++ can
call C functions, most notably of the operating system), yet capable
to implement new C++ functionality (like the constructor elision).

There are many call conventions that depend mostly on the processor
capabilities.  Typically, a call convention requires that the caller
of the function (i.e., the code that calls the function):

* creates the function parameters on the stack,

* allocates memory for the return value.

Parameters are created on the stack because a processor might be
unable to store them (in registers).  The caller allocates memory for
the return value because it may not fit in a processor, yet it should
be available to the caller once the function returns.

Small data may be accepted or returned in processor registers, e.g, an
integer in EAX for x86, Linux, and GCC.

We differentiate between two call conventions:

* legacy, that the legacy C++ depended on,

* modern, that the modern C++ depends on.

The **legacy call** convention required a function to return its
result in a temporary place at the top of the stack, which was easy to
locate with the stack register -- that was an advantage.  A
disadvantage it was to copy the result from that temporary place to a
destination, e.g., a variable that was initialized with the result.

The **modern call** convention allows the place for the return value
be allocated anywhere in memory (not only on the stack, but also on
the heap, or in the memory for the global and static data), and
passing to a function the address of the place, so that the function
can create the return value at the destination pointed.  We don't need
a temporary place anymore.  For instance, for x86, Linux, and GCC, the
address is passed to a function on the stack last, while to a
constructor in the RDI register.

The following example demonstrates that a result can be returned
anywhere (now that we have the modern call convention), and not only
on the stack (as the legacy convention stipulated in the past): the
function returns its value (an object) by creating it in the place for
the global variable `a` (allowed by the modern call convention),
without copy-initializing `a` from a temporary object on the stack
(required by the legacy call convention).

```cpp
{% include_relative anywhere.cc %}
```

As a corollary of these call conventions, let's notice that a
parameter of a function and a local variable of a function look the
same, but they differ in what code controls (creates, initializes and
destroys) them:

* a parameter is controlled by the caller of the function,

* a local variable is controlled by the function.

**Bottom line: a parameter is out of control of the function.**

## Constructor elision

The modern call convention opened the door to efficient returning by
value, and so the functionality that used to be known as the *return
value optimization* (RVO) was finally standardized in C++11 under the
name of the **constructor elision**.  We need to know that an
*optimization* is offered by a compiler: RVO has never been
standardized, there is even no mention of it in the standard.

Constructor elision is also known as the *copy elision*, *copy/move
elision* or *copy/move constructor elision*.  It applies to no other
constructor, and to no assignment operator.  I prefer the *constructor
elision*, because it's about constructors only (and not the assignment
operators too), and it can elide not only the copy constructor, but
also the move constructor.  However, we need to note that the standard
calls it the **copy/move elision**.

There used to be two versions of the RVO: named and unnamed.  In C++11
both became the constructor elision.  However, in C++17, what used to
be the unnamed RVO became the *temporary materialization*.  The
following example demonstrates a use case for the C++17 elision
(formerly for the named RVO): returning a non-static local variable
that is not a parameter.

```cpp
{% include_relative elide.cc %}
```

To see the legacy behviour, compile the above example with the
compiler flag `-fno-elide-constructors` (modify CXXFLAGS in
GNUmakefile).  Notice the differences at run-time, that with
constructor elision, objects are not copied (nor moved) unnecessarily.

Even if constructors are elided, they must be defined because
depending on the type of the returned value, a compiler can decide not
to elide constructors.  Also, in the exceptional use cases discussed
below, elision does not apply.  In the example below, remove the
constructors by removing the comments to see the compilation fail.

**Bottom line: elision is not mandatory.**

```cpp
{% include_relative no_ctors_elide.cc %}
```

### Exceptions

Elision cannot always take place, because of technical reasons.
First, because we return data, which has to be created prior to
deciding which data exactly to return:

```cpp
{% include_relative no_elision1.cc %}
```

Second, because we return a function parameter, which was created by
the caller, not the function, and so the function cannot create the
parameter in the location for the return value:

```cpp
{% include_relative no_elision2.cc %}
```

Finally, because we return global or static data, which has to be
available after the function returns, and so the function can only
copy the result from the global or static data:

```cpp
{% include_relative no_elision3.cc %}
```

## Temporary materialization

It's the materialization of a temporary (a temporary object), and not
a materialization that is temporary.  Materialization is just
creation, i.e., calling a constructor.  As shown in the example below,
returning a temporary is the most important use case of the temporary
materialization.

```cpp
{% include_relative materialization1.cc %}
```

A result is returned by a function directly in its destination, e.g.,
a variable that is initialized with the result.  The idea is to create
the result in its destination, so that it doesn't have to be copied
(copy-initialized) or moved (move-initialized) there.  Just like the
constructor elision!

However, **the materialization is mandatory**, while the elision is
not.  The returned value is never (no exceptions) copied or moved, and
so its type doesn't need to have the copy and move constructors, as
shown in the example below.

```cpp
{% include_relative no_ctors_mater.cc %}
```

Compile the above example with:

* `-std=c++14` to see the compilation fail: in C++14 it was a use case
  of the constructor elision,

* `-std=c++17` to see that `-fno-elide-constructors` has no effect: in
  C++17 it is not a use case of the constructor elision any longer.

# Lifetime and identity

Lifetime and identity are two notions that in C++ became technical
terms because they are fundamental to how C++ processes data.  A
**lifetime** of datum is the period of runtime the datum exists.  The
lifetime of some datum (a variable, an object, a temporary) starts
when it is constructed, and ends when it is destroyed.  The datum
during its lifetime has **identity**, i.e., it exists somewhere.  We
can take the address of a datum in existance with the `&` operator.

The location of a datum (the place where the datum is, lives, resides)
is usually RAM, but a compiler can also make it a processor register
to boost performance.  If so, what happens when we take addresses of
data in registers?  Then, it's a problem of the compiler that has to
work around our request for the address with less wiggle room for
optimization.

Below there's an example with integer variables.  Their lifetimes
begin with their declaration statements that can also initialize them.
The initializing `1` has no identity: it's not created anywhere and
then copy-constructed into the variable.  Instead, the value of `1`
(which may be an operand of a processor instruction) is written into
the location of the variable -- we could say that the temporary (`1`)
was materialized.

```cpp
{% include_relative identity1.cc %}
```

Here's the example with string variables.  Since, they are objects,
they always have to be initialized.  A compiler interprets `{}` as
`string{}`, which has no identity.  The value of this expression is
not copy-constructed or move-constructed into the variable.  Instead,
the value of `string{}` is created directly in the location of the
variable -- we say that a temporary was materialized.

```cpp
{% include_relative identity2.cc %}
```

In the example above, even expression `string("Hello!")` has no
identity!  This is surprising because `"Hello!"` surely has to be
somewhere in memory, i.e., it must have an identity.  Well, a string
literal is a singular datum: it is never created nor destroyed, and it
always exists.  Yes, a string literal has an identity, but
`string("Hello!")` still doesn't.

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
