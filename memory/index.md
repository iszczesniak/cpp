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
operating system or other processes.  For instance, an unprivileged
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
even more inefficient, because they are *nondeterministic*, i.e., it
is undefined when data are destroyed.

The C++ Standard Committee considered the garbage collection support,
but dropped it for performance reasons.  Nowadays, C++ requires no
garbage collection since it offers advanced container and smart
pointer support, which could be considered a form of garbage
collection.

## Struct A

In the examples that follow we use structure `A` that lets us see when
an object is constructed, copied, accessed (by calling function
`hello`) and destroyed.  Note that there is no default constructor,
and so nowhere in the following examples do we default-construct
objects of type A: an object is either directly initialized (with a
string) or copy constructed.  Please note (take a look at a make file)
that file `A.cpp` is separately compiled, and then linked with the
examples.

File A.hpp:

```cpp
{% include_relative A.hpp %}
```

File A.cpp:

```cpp
{% include_relative A.cpp %}
```

### Move semantics, mentioned in passing

We need to mention here the *move semantics*.  For now, it's enough to
say that *moving* sometimes replaces *copying*.  A value is copied
when copy-construcing (or copy-assigning to) some other (target)
object by using the copy constructor (or the copy-assignment
operator).  A value is moved when move-construcing (or move-assigning
to) some other (target) object by using the move constructor (or the
move-assignment operator).

Below we deliberately don't discuss moving, because what follows is
already a full mouth to swallow.  We'll look into moving in detail
later, in another lecture.  For this reason we disable moving for type
`A` by declaring its copy constructor.

# Data and their location

The read-write memory stores:

* global and static data in a location of fixed size,

* local data on a stack (more specifically, a stack per thread of the
  process),

* dynamic data on the heap (aka the free-store).

## Global and static data

Global data are initialized before entering the `main` function, and
are available everywhere in the program:

```cpp
{% include_relative global.cc %}
```

Static data are initialized before their first use, and are local to a
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
The local data are automatically destroyed when they go out of scope.
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
which is not recommended, but suitable now to demonstrate the dynamic
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
stack pointer (aka the stack register) by the size of the memory
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
writes are necessary for a single allocation.

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
no other ways of accepting an argument or returning a value.  A
pointer can be accepted or returned either by value or by reference.

A function can have *parameters*, and then we call a function with
*arguments*.  A function parameter is local to a function body, like a
local variable.  A parameter has a type and a name given in the
function declaration or definition.  An argument is an expression that
is part of a call expression.

A parameter is initialized with an argument.  A result is initialized
with the expression of the return instruction.

## Accepting arguments

If a function parameter is of a non-reference type (any type except a
reference type), we say that a function accepts (or takes) an argument
by value, or that we pass an argument to a function by value.  In
legacy C++, a non-reference parameter was initialized always by
copying the argument value into the parameter.  In modern C++,
depending on the category of the argument, that copying might be gone,
because of materialization.

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
that evolution, C++ must be binary compatible with C (so that C++ can
call C functions, most notably of the operating system), yet able to
implement new C++ functionality (like the constructor elision).

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
without copy-initializing variable `a` from a temporary object on the
stack (required by the legacy call convention).

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

# Returning by value

In modern C++, returing by value is fast, does not impose any
unnecessary overhead, and therefore is recommended.  It's not what it
used to be in the deep past, before C++ was standardized.  Back then
returning by value always copied the result twice.  First, from a
local variable of the function to a temporary place on the stack for
the return value.  Second, from the temporary place to the
destination, e.g., a variable that was initialized with the result.

To understand how returning an object by value became efficient, and
to be aware of exceptions, we need to understand the constructor
elision and materialization.

## Copy elision

For a historical review, the functionality that is now called elision
was mentioned for copying in C++98, termed elision in C++03, and
extended for moving in C++11.  This functionality was commonly known
as the return value optimization (RVO), but it wasn't called like this
in the standard.  Around the time of C++11, the modern call convention
started to spread that enabled (with the official support of an
operating system, specifically the system compiler) efficient
returning by value, and so this functionality gained in importance,
but under the standardized term of elision.

The **copy elision** ([class.copy.elision]) elides the copy
constructor, and not the direct-initialization constructors or
assignment operators.  It's also known as the *constructor elision*.
We distinguish between two versions of the elision: named and unnamed.
The terms of the named and unnamed elision are not standard: the
standard treats them just as elision, but we differentiate between
them for better understanding, and to emphasise the transition from
the unnamed elision to materialization.

### Named elision

The following example demonstrates a use case for the named elision
(that also used to be known as the *named RVO*): the expression of the
return instruction is a non-static local variable that is not a
parameter.  It is still elision according to the newest standard
(C++26).

```cpp
{% include_relative named.cc %}
```

To see the legacy behavior (i.e., without the elision), compile the
above example with the compiler flag `-fno-elide-constructors` (modify
CXXFLAGS in GNUmakefile).  Notice the differences at run-time, that
with constructor elision, objects are not copied unnecessarily.

Even if constructors are elided, they must be defined because
depending on some minor technical details, the standard allows a
compiler not to elide constructors.  In the example below, delete the
copy constructor by removing the comment to see the compilation fail.
Also, in the exceptional use cases discussed further below, elision
does not apply, and so constructors must be defined, because they are
used.

**Bottom line: elision is optional.**

```cpp
{% include_relative optional.cc %}
```

#### Exceptions

Elision cannot always take place, because of technical reasons.
First, because we return a variable which has to be created prior to
deciding which variable exactly to return:

```cpp
{% include_relative no_elision1.cc %}
```

Second, because we return a function parameter, which was created by
the caller, not the function, and so the function cannot create the
parameter in the location for the return value:

```cpp
{% include_relative no_elision2.cc %}
```

Finally, because we return a global or static variable, which has to
be available after the function returns, and so the function can only
copy its value:

```cpp
{% include_relative no_elision3.cc %}
```

### Unnamed elision

The following example demonstrates a use case for the unnamed elision
(that also used to be known as the *unnamed RVO*): the expression of
the return instruction is a temporary object.

```cpp
{% include_relative unnamed.cc %}
```

There is another use case of the unnamed elision: initialization with
a temporary object, because **a constructor is a *special function*
that returns by value the created object**.  The example below shows
the variable initialization:

```cpp
{% include_relative initialization.cc %}
```

#### Parameter initialization

An example below shows the initialization of a function parameter with
a temporary object, just like above a variable was initialized with a
temporary object.  The parameter is initialized (controlled) by the
caller, and so the temporary object can be created in the parameter in
accordance with the unnamed elision.

```cpp
{% include_relative parameter.cc %}
```

**In C++17, the use cases of the unnamed elision became the use cases
  of *materialization*.**

## Materialization

Materialization, introduced in C++17, makes the unnamed elision
mandatory, while before it was optional -- that nifty wording,
however, describes a new concept (of materialization) with the defunct
terminology (of the unnamed elision) that is not even standard.  Since
C++17, elision includes only the use cases that we termed 'named'.

The C++17 introduced a **new take** on the problem of returning by
value: the copy constructor is not elided, it's unneeded by design.
Why should the return value be copied when it's materialized?  The
returned value is never (no exceptions) copied, and so its type
doesn't need to have the copy constructor, as shown in the example
below.

```cpp
{% include_relative mandatory.cc %}
```

Compile the above example with:

* `-std=c++14` to see the compilation fail: in C++14 it was a use case
  of the constructor elision,

* `-std=c++17` to see that `-fno-elide-constructors` has no effect: in
  C++17 it is not a use case of the constructor elision any longer.

Materialization generalizes creation: materialization is just creation
of an object when it's returned by value.  A constructor creates an
object and returns it by value too, so creation is materialization
too, but limited to a single return.

In materialization, functions return by value the results returned by
value by functions called -- in this call chain, we are interested in
the return instruction at the end of the chain, because it creates the
object that then crosses the function boundaries without being copied.
The function called last is a constructor, but constructors have no
return instruction, and so we are interested in the return statement
that calls the constructor.  A compiler chooses the right constructor
depending on the expression of that return statement, specifically
whether the return expression creates an object with a new or copied
value.

### Case 1: a new value

In this case the return expression creates a new value by defining:

* the type of data to create,

* the arguments for the creation.

Let's temporarily call such an expression a "recipe" for a value of a
given type.  The expression differs from a variable initilization in
that we don't give it a name.  Here are some example recipes:

* `std::string()`: type `std::string`, no arguments,

* `int()` is really `int(0)`: type `int`, argument `0`,

* `1` is `int(1)`: type `int`, argument `1`,

* `std::string("Hello")`: type `std::string`, argument `"Hello"`.

#### Prior to C++17: a temporary

When a recipe is a standalone expression, then its evaluation creates
a temporary (a temporary value) that is next destroyed, and so it is a
*discarded-value expression*.  A temporary object is created on the
stack.  Here's an example:

```cpp
{% include_relative standalone.cc %}
```

When a recipe is not standalone, then it's an **argument** of a return
instruction or a call (of a function, a constructor or an operator).
Prior to C++17, a recipe used as an argument also created a temporary
that was used to initialize a return value or a parameter (of a
function, a constructor or an operator), regardless of whether the
parameter was of a reference type or not.  A temporary was destroyed
before the evaluation of the complete (whole) expression was complete.
When passing by value, however, that temporary didn't exist because
its value was created directly in a parameter in accordance with the
unnamed elision.

**Bottom line: prior to C++17, a recipe always created a temporary
object, that could have been elided.**

#### Since C++17: a prvalue

Since C++17 these recipes are called expressions of the **prvalue**
category, prvalue expressions or just prvalues.  We'll look into the
expression categories later, but we start refering to these
expressions as prvalues.  Along with the prvalues, there came a new
semantics.

An evaluation of a prvalue materializes the result (the **result
object**, the result value) directly into a destination, voiding the
need for the elision.  That destination doesn't have to be a
temporary, it can also be a variable.  A **temporary materialization**
is the materialization into a temporary, and not a materialization
that is temporary.  Here's an example:

```cpp
{% include_relative materialization.cc %}
```

### Case 2: a copied value

## Test implementation

Here's a test implementation of the constructor elision and the
materialization.  We are not returning anything, but pass a pointer to
a location where we want to have the return value created.

Let's keep in mind that this implementation is supposed to help us
understand how the elision and materialization work, but we don't
program like this: we don't call a constructor again (as we do with
the placement new) after an object has been created.  We could
legitimately call the constructor again, if the destructor was called
first.

```cpp
{% include_relative implementation.cc %}
```

### Beware of hack.hpp!

In the implementation above we include the `hack.hpp` file.  It's a
hack, a handy one.  This file defines the same struct `A` as files
`A.hpp` and `A.cpp`, except for the default constructor that
`hack.hpp` requests to be default implemented.

In the implementation above, we default initialize the local variable,
and pretend it has never happened because it writes nothing to `cout`,
but we need that initialization to have the memory allocated and the
destructor called.  We don't call the destructor before the placement
new, even though we should, because that would obfuscate the output of
the program.  We play this underhanded trickery just to get the output
right.

# Lifetime and identity

Lifetime and identity are two notions that in C++ became technical
terms because they are fundamental to how C++ processes data.  A
**lifetime** of a datum is the period of runtime the datum exists.
The lifetime of some datum (a variable, a temporary) starts when it is
constructed, and ends when it is destroyed.  The datum during its
lifetime has **identity**, i.e., it exists somewhere.  We can take the
address of a datum in existance with the `&` operator.

The location of a datum (the place where the datum is, lives, resides)
is usually RAM, but a compiler can also make it a processor register
to boost performance.  If so, what happens when we take addresses of
data in registers?  Then, it's a problem of the compiler that has to
work around our request for the address with less wiggle room for
optimization.

Below there's an example with integer variables.  Their lifetimes
begin with their declaration statements that can also initialize them.
The initializing `1` has no identity: it's not created anywhere and
then copy constructed into the variable.  Instead, the value of `1`
(which may be an operand of a processor instruction) is written into
the location of the variable -- we could say that the value (`1`) was
materialized.

```cpp
{% include_relative identity1.cc %}
```

Here's the example with `std::string` variables.  Since, they are
objects, they always have to be initialized.  A compiler interprets
`{}` as `string{}`, which has no identity.  The value of this
expression is not copy constructed or move constructed into the
variable.  Instead, the value of `string{}` is created directly in the
location of the variable -- we say that a value (`string{}`) was
materialized.

```cpp
{% include_relative identity2.cc %}
```

In the example above, even expression `string("Hello!")` has no
identity!  This is surprising because `"Hello!"` surely has to be
somewhere in memory, i.e., it must have an identity.  Well, a string
literal is a singular datum: it is never created nor destroyed, and it
always exists.  Yes, a string literal has an identity, but
`string("Hello!")` still doesn't.

# More elaborate examples

As a drill, we study the examples below and analyze them to understand
whether the copy or move constructors are called or not, or whether
they are elided.  These examples are simple and minimalistic, and they
cover almost all use cases of daily programming.  To see the
differences, we compile the examples the usual way (with at least
C++17), and then with C++11, asking the compiler to elide constructors
or not.

I tried to compile with C++03 to see the copying instead of moving.
However, the move semantics (of C++11) was still used.  Also, I
couldn't get the behavior of the legacy call convention, which is not
surprising, because I'm using a modern system that offers the modern
call convention only.  I tried the same with an online compiler with
the same effect.  It's legacy, so we shouldn't be bothered.  In a few
years, we can expect to have problems replicating the C++11 behavior.
If we really wanted to see the C++03 behavior, we should use some
really old system, e.g., Debian 4.

I include the `hack.hpp` file in the examples below, so that you can
use an online compiler (e.g., Compiler Explorer) to quickly compile
the examples with various compiler versions and compilation flags:
there you replace `#include "hack.hpp"` with the contents of this
file, without having to use another compilation unit (A.cpp).

## Example 1

Returning a prvalue by value is a special use case in C++17, that of
materialization: the prvalue is materialized directly in the
destination, no copy or move constructor is needed.  The result is
returned by value twice, no copy or move constructor is called.  The
lifetime of the object starts in function `g`, and ends in the main
function. **What?** A temporary object is not destroyed in the same
scope it was created in?  Since C++17, it's not a temporary, but a
prvalue.  Asking a compiler to elide constructors makes no difference.

In C++11, a temporary is created in function `g` as an argument of the
return instruction.  That first temporary is used to move-initialize
the result of function `g`, i.e., the second temporary object that
becomes the argument of the return instruction of function `f`.  That
second temporary is used to move-initialize the result of function
`f`, i.e., the third temporary object that becomes the argument of the
move-initialization of variable `a`.  These move constructors are
elided, but you can ask the compiler not to do it.

```cpp
{% include_relative example1.cc %}
```

## Example 2

In this example, function `f` doesn't return right away the result of
`g` as in the example above, but initializes local variable `a` with
it, and then returns `a`.  The output of this example is the same as
of the above, because no copy or move constructor is called.

The prvalue returned by `g` is materialized into the local variable of
function `f`.  Function `f` returns a prvalue that is move-initialized
(materialized) from the local variable and into the local variable of
function `main`.  Move-initialization is more efficient than
copy-initialization because the local variable (that is the argument
of the return instruction) will soon be destroyed -- it's called the
*implicit move* (we'll get to it).  Function `f` is in full control of
its local variable, and so it can elide the move initialization (i.e.,
calling the move constructor, where the source object is the local
variable of function `f`, and the target object is the local variable
of the main function) by passing the address for the return value
(passed by the main function) to function `g`.  Ask your compiler to
use C++17 and not to elide constructors to see a move constructor
called once.

For C++11, the output is the same because of the elision.  There is no
materialization yet, but there is unnamed elision.  Ask your compiler
to use C++11 and not to elide constructors to see the move constructor
called four times.  Each function call results in the move constructor
called twice: first the value of a return expression is moved into a
temporary of the call expression, and next to a local variable.

```cpp
{% include_relative example2.cc %}
```

## Example 3

In this example, function `f` returns the value of its parameter.  The
main function passes the result of `g` to `f`.  The output shows a
move constructor was called.  No way, no how could this constructor be
elided.

The main function allocates memory for the parameter of function `f`
and passes its address to function `g` as the address for the return
value, so that function `g` can materialize its prvalue there.  Next,
the main function passes the address of its local variable to function
`f`, so that function `f` can materialize its prvalue there by the
move initialization (it's also the implicit move) from its parameter.
Ask your compiler to use C++17 and not to elide constructors to see no
difference in output, because no elision was used.

In C++11, the output is the same because of the elision.  Function `g`
creates a temporary, but the move constructor is elided, so the result
is created in the parameter of function `f`.  Ask your compiler to use
C++11 and not to elide constructors to see the move constructor called
four times, as in the example above, with the same explanation.

```cpp
{% include_relative example3.cc %}
```

## Example 4

In the example below, the prvalue argument of the constructor is
materialized into the parameter of the constructor, and then its value
is copied into the member field.  In C++17, asking a compiler not to
elide constructors has no effect, because elision is not used.  In
C++11 without elision, a temporary move-initializes the constructor
parameter.

```cpp
{% include_relative member.cc %}
```

# Conclusion

* Data can be allocated globally, statically, locally or dynamically.

* Allocating memory on the stack is ultra fast, while on the heap is
  much slower.

* Don't use the dynamically-allocated data, if local data are good
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
