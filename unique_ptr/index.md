---
title: std::unique_ptr
---

# Introduction

Pointers are indispensible.  Pointers:

* point to memory locations, usually dynamically-allocated,

* are used in every programming language: C, C++, Java, C#,

* can be used in the form of a reference, e.g., in Java or C#.

The pointer support can be:

* wrapped in a reference, e.g., in Java or C#,

* raw or advanced, as in C++,

* raw only, as in C.

In C++, it's best to avoid the raw pointers, and go for the advanced
pointer support in the form of standard smart pointers.

A reference in Java or C# is a shared pointer with the object member
selection syntax (i.e., `object.member`).  A C++ reference is an
alias, which at compile time will be either optimized out or turned
into a raw pointer.

# Motivation: the problems of raw pointers

While raw pointers are easy to use, but their use is very error-prone,
i.e., it's easy to make mistakes.

## The problems

When we have a pointer of type `T *` which points to a
dynamically-allocated memory location, we have these problems:

* **the type problem**: we don't know whether a pointer points to a
  single piece of data or to an array of data,

* **the ownership problem**: we don't know whether *we* or *someone
  else* (i.e., some other programmer who implemented some other part
  of code) should destroy the allocated data,

* **the exception handling problem**: exception handling with raw
  pointers is difficult, arduous, and error-prone.

### The type problem

The new and delete operators come in many versions, most notably:

* the *single version* for allocating a single piece of data,

* the *array version* for allocating an array of data.

If we allocate data with either the single or array version of the new
operator, we should destroy the data with the same version of the
delete operator.  However, the type of the pointer used is the same
for both version, so it's easy to mismatch the versions, which results
in an undefined behaviour.

### The ownership problem

The ownership problem can result in:

* **a memory leak**, when the dynamically-allocated data is never
  destroyed,

* **a dangling pointer**, when we keep using a memory location, but
  the data that used to be there was already destroyed,

* **a double deletion**, when we try to destroy again the data that
    was already destroyed.

### The exception handling problem

If we manage the dynamically-allocated data with raw pointers, the
exception handling becomes a boring and error-prone task, espacially
if the data is complex.  It's doable, but who really wants to do it?

## An example

The example below shows how easily we can run into the type,
ownership, and exception handling problems.  The compiler does not
report problems with this broken code.

{% highlight c++ %}
{% include_relative problems.cc %}
{% endhighlight %}

## The smart pointer solution

The smart pointers solve:

* the type problem: a smart pointer knows the type of the object, so
  that it can be automatically (i.e., without a programmer requesting
  it explicitely) destroyed in the proper way,

* the ownership problem: a smart pointer automatically manages the
  dynamically-allocated data, i.e., takes care of their destruction,
  and either enforces the exclusive ownership or allows for shared
  management,

* the exception handling problem: a smart pointer is automatically
  destroyed when an exception is handled.

Every flexible language should support raw pointers, because this
low-level functionality is needed to implement high-level
functionality, such as smart pointers.

A programmer should have a choice between the raw pointers (perhaps
for implementing an intricate functionality) and smart pointers (just
for every day use).

In C++, for every day use, a programmer should not resort to the raw
pointers, let alone to the `void *` trickery -- these times are long
gone.

## Smart pointer types

A smart pointer manages dynamically-allocated data, and so we call a
smart pointer the **managing object**, and the dynamically-allocated
data the **managed data**.

There are three smart pointer types defined in the `memory` header
file:

* `std::unique_ptr` - used to exclusively own the managed data,

* `std::shared_ptr` - used to share the managed data,

* `std::weak_ptr` - used to track, but not share, the managed data.

Smart pointer types are wrappers around raw pointers, which are used
at compile-time only, and so at run-time they should not degrade the
memory or time performance.  They should be as fast and take as little
memory as the code of the same functionality manually crafted with raw
pointers.

Smart pointer types are:

* *exception-safe*: they can be used without problems when throwing or
   catching exceptions,

* *not thread-safe*: they should be carefully used in a multithreaded
   program.

There is also deprecated type `std::auto_ptr` -- don't use it.

# `std::unique_ptr`

An object of type `std::unique_ptr` has the **exclusive ownership
semantics**:

* *exclusive*, because the managing object is the sole owner of the
  managed data, i.e., there can be only a single object that owns the
  managed data,

* *ownership*, because the managing object is responsible for
   destroying the managed data.

The exclusivity implies that `std::unique_ptr` is a move-only type,
and so:

* you cannot copy-initialize or copy-assign objects of this type, and
  for this reason this type has the copy constructor, and the copy
  assignment operator deleted,

* you can transfer the ownership between the managing objects by
  move-initializing, and move-assigning.

The ownership means that the managed data should be destroyed when the
managing object is:

* destroyed, e.g., goes out of scope,

* assigned new data to manage.

Most likely you need this smart pointer when you want to switch from
raw pointers to smart pointers.

## An example

Type `std::unique_ptr` is a templated type: you need to pass the type
of managed data as an argument to the template type.  We pass the
template arguments in the angle brackets, i.e., `<>`, like this:

`std::unique_ptr<managed_data_type> p;`

In the example below, the managing object `p` manages the data of type
`int`, which will be automatically destroyed by `p` when it goes out
of scope.

{% highlight c++ %}
{% include_relative simple.cc %}
{% endhighlight %}

## Function `std::make_unique`

Function template `std::make_unique` was introduced for convenience
(we could do without it): it creates both the managing object, and the
managed data.  Instead of writing the type `A` twice like this:

`unique_ptr<A> up(new A("A1"));`

We can write the equivalent code like this, without typing type `A`
twice:

`auto up = make_unique<A>("A1");`

Function `std::make_unique` introduces no overhead: the move
constructor will be elided, the return value optimization will take
place, and so the managing object will be created directly in the
location of `up`.

By type `auto` above we ask the compiler to make the type of `up` the
same type as the type of the initializing expression
`make_unique<A>("A1")`, which is `std::unique_ptr<A>`.  We could have
equivallently written:

`unique_ptr<A> up = make_unique<A>("A1");`

To use function `std::make_unique`, you need to pass the template
argument, which is the type of the managed data to create, and manage.
The arguments (none, one or more) of the function are passed to the
constructor of the managed data (a feat accomplished with the variadic
templates).  In the example above `"A1"` is the argument passed to the
constructor of type `A`.

## No performance overhead

This example demonstrates that there is no performance overhead of
using smart pointers.  In more complicated examples there might be
some small overhead, which should go away as compilers get better at
optimization.

The following example uses both the `std::unique_ptr` and
`std::make_unique`.  Save this file as `test1.cc`:

{% highlight c++ %}
{% include_relative test1.cc %}
{% endhighlight %}

The following example of the same functionality uses raw pointers.
Save this file as `test2.cc`:

{% highlight c++ %}
{% include_relative test2.cc %}
{% endhighlight %}

Now compile them to the assembly code with:

`g++ -S -O3 test1.cc test2.cc`

Now there are two files with the assembly code: `test1.s`, and
`test2.s`.  Take a look at one of them:

`c++filt < test1.s | less`

Compare them to see that they are instruction-to-instruction the same
(almost, there is one small difference), which shows there is no
overhead of using `std::unique_ptr` and `std::make_unique`:

`diff test1.s test2.s`

# More on the usage

std::unique_ptr<A> p1; // OK.  Nie wskazuje na nic.
std::unique_ptr<A> p1(new A("A1")); // OK.
p1 = new A("A1'"); // Zabronione!
p1.reset(new A("A2")); // OK, ale usunie "A1".
std::unique_ptr<A> p2(p1); // Błąd! Nie można kopiować.
std::unique_ptr<A> p2 = p1; // Błąd! Nie można kopiować.
p2 = p1; // Błąd! Nie można kopiować.
p2 = std::move(p1); // OK.  Przeniesienie.
p2->foo(); // Wywyłanie A::foo(), jak przez wskaźnik.
(*p2).foo(); // Wywyłanie A::foo(), jak przez wskaźnik.
p1.release(); // p1 już nie ma obiektu, ale go nie usuwa.
p1.get(); // Wartość surowego wskaźnika.

std::deque<std::unique_ptr<A> > c;
c.push_back(std::unique_ptr<A>(new A("C1")));

# Conclusion

* Don't use raw pointers, unless you really have to.

* Start using `std::unique_ptr`, the most useful smart pointer type.

* Smart pointers solve the type, ownership and exception handling
  problems.

* Smart pointers introduce no, or little, performance overhead.

* Go for the smart pointers!

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
