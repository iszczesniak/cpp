---
title: std::unique_ptr
---

# Wprowadzenie

Wskaźniki są nieodzowne.  Wskaźniki:

* wskazują miejsce w pamięci, zwykle zaalokowane dynamicznie,

* są używane w każdym języku programowania: C, C++, Java, C#,

* mogą być użyte w formie referencji, np. w Javie czy C#.

Wsparcie wskaźników może być:

* opakowane w referencję, np. w Javie czy C#,

* surowe albo zaawansowane, jak w C++,

* tylko surowe, jak w C.

W C++ najlepiej unikać surowych wskaźników i korzystać z
zaawansowanego wsparcia w postaci standardowych wskaźników
inteligentnych.

Referencja w Javie czy C# jest inteligentnym wskaźnikiem o semantyce
współdzielonej własności, gdzie dostęp do składowej uzyskujemy z
użyciem operatora `.` (czyli `object.member`), a nie `->` (czyli
`pointer->member`).  W C++ referencja jest aliasem, która w czasie
kompilacji będzie wyoptymalizowana albo zmieniona na surowy wskaźnik.

# Motywacja: problemy surowych wskaźników

Surowe wskaźniki łatwo używać, ale też łatwo popełniać błędy.

## Problemy

Kiedy mamy wskaźnik typu `T *`, który wskazuje na dynamicznie
stworzone dane, to mamy następujące problemy:

* **problem typu**: nie wiemy, czy wskaźnik wskazuje na jedną daną,
    czy może na tablicę danych,

* **problem własności**: nie wiemy, czy *my* czy może *ktoś inny*
    (czyli inny programista, który napisał inny fragment kodu)
    powinien zniszczyć dane,

* **problem obsługi wyjątków**: obsługa wyjątków ze surowymi
    wskaźnikami jest trudna, pracochłonna i podatna na błędy.

### Problem typu

Operatory `new` i `delete` mają wiele wersji, ale ważnymi są:

* wersja pojedyncza dla jednej danej,

* wersja tablicowa dla tablicy danych.

Jeżeli tworzymy dane z użyciem wersji pojedynczej albo tablicowej
operatora `new`, to powinniśmy zniszczyć dane tą samą wersją operatora
`delete`.  Pomieszanie dwóch wersji skutkuje niezdefiniowanym
działaniem.  Kompilator nie jest w stanie wychycić błędu, bo operatory
`new` i `delete` posługują się tym samym typem danych: `T *`.

### Problem własności

Problem własności może skutkować:

* **przeciekiem pamięci**, kiedy dynamicznie zaalokowane dane nie są
    nigdy zniszczone, mimo że nie są już potrzebne,

* **dyndającym wskaźnikiem**, kiedy odwołujemy się do miejsca w
    pamięci, ale dane, które tam się znajdowały, zostały już
    zniszczone,

* **podwójnym usunięciem**, kiedy próbujemy zniszczyć dane, które już
    zostały zniszczone.

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

# The smart pointer solution

A smart pointer manages dynamically-allocated data, and so we call a
smart pointer the **managing object**, and the dynamically-allocated
data the **managed data**.

A smart pointer doesn't copy or move the managed data, it can only
destroy the data.

The type of the managed data doesn't have to be prepared in some
special way in order to be managed by smart pointers, e.g., the type
doesn't have to be derived from some special type with the required
functionality implemented.

The smart pointers solve:

* the type problem: a smart pointer knows the type of the object, so
  that it can be automatically (i.e., without a programmer requesting
  it explicitely) destroyed in the proper way,

* the ownership problem: a smart pointer automatically manages the
  dynamically-allocated data, i.e., takes care of their destruction,
  and implements either the exclusive or shared ownership,

* the exception handling problem: a smart pointer is automatically
  destroyed (and so is the managed data) when an exception is handled.

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
  assignment operator explicitly deleted,

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
managed data.

We can create the managed data yourself with the new operator, and
pass its raw pointer to the managing object like this:

`unique_ptr<A> up(new A("A1"));`

Instead, we can write the equivalent code like this, without typing
type `A` twice:

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

## How to use `std::unique_ptr`

The example below demonstrates the basic usage of `std::unique_ptr`.

{% highlight c++ %}
{% include_relative usage.cc %}
{% endhighlight %}

# The solutions to the problems

## The type problem

The type problem, more specifically the problem of mismatching the
single and array versions of the new and delete operators, is solved
by two versions (two template overloads) of smart pointers:

* `std::unique_ptr<A>`: the managed data will be destroyed with the
  single version of the delete operator,

* `std::unique_ptr<A[]>`: the managed data will be destroyed with the
  array version of the delete operator.

By using the right version of the smart pointer, you don't have to
remember to destroy the managed data with the matching version of the
delete operator.

### Lurking problems, and how to deal with them.

However, we still can introduce bugs like in the example below, where
we:

* declare to allocate a single integer, but allocate an array of
  integers,

* declare to allocate an array of integers, but allocate a single
  integer.

Use `std::make_unique` to get the same done safer, as shown below.

{% highlight c++ %}
{% include_relative solved_type.cc %}
{% endhighlight %}

### Use `std::array` instead!

If you really have to have an array of static size (i.e., the size
doesn't change at run-time), it's better to use `std::array` instead
of the C-style array.  You can use it with smart pointers like this:

{% highlight c++ %}
{% include_relative array.cc %}
{% endhighlight %}

## The ownership problem

The ownership problem is solved: you just move the ownership where you
need to, e.g., a function or some structure.  You can move the
ownership when you pass or return a unique pointer by value in a
function call, as shown in the example below.

{% highlight c++ %}
{% include_relative solved_ownership.cc %}
{% endhighlight %}

## The exception handling problem

When an exception is thrown, the data previously allocated (or any
other resource acquired) and not required any longer because of the
exception, should be deleted (or released).  When programming with raw
pointers, we can release the memory in the catch block, as shown in
the example below.  We have to declare `p` before the try block, so
that it's accessible in the catch block, and that complicates the
code.

{% highlight c++ %}
{% include_relative except_raw1.cc %}
{% endhighlight %}

The same can be accomplished with smart pointers better:

{% highlight c++ %}
{% include_relative except_smart1.cc %}
{% endhighlight %}

### Raw pointers not so easy, rather error-prone.

Because function arguments are not guaranteed to be evalued in the
order they are listed, in the example below we've got a memory leak.
At least I've got it with GCC, and if you don't, try to swap the
arguments in the call to `foo`.  The object of class `A` is:

* created, because the second argument of the call to function `foo`
  is evaluated first, before function `index` is called,

* not destroyed, because function `foo` is not called, because a call
  to function `index` throws an exception.

{% highlight c++ %}
{% include_relative except_raw2.cc %}
{% endhighlight %}

The same can be accomplished the safe way with smart pointers.  This
code works correctly regardless of whether an exception is thrown or
not.

{% highlight c++ %}
{% include_relative except_smart2.cc %}
{% endhighlight %}

## The first example revisited

Below there is the first example fixed with raw pointers.  All
problems gone.

{% highlight c++ %}
{% include_relative problems_solved.cc %}
{% endhighlight %}

# Conclusion

* Don't use raw pointers, unless you really have to.

* Start using `std::unique_ptr`, the most useful smart pointer type.

* Smart pointers solve the type, ownership and exception handling
  problems.

* Smart pointers introduce no, or little, performance overhead.

* Go for the smart pointers!

# Quiz

* Why should we use smart pointers instead of raw pointers?

* What is the exclusive ownership?

* What do we need the `make_uniqe` function for?

{% include rid %}

<!-- LocalWords:  -->
