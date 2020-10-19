---
title: Callable, sth to call
---

# Introduction

In C we use a function pointer to ship a piece of code (e.g., that
establishes order between objects) to some other piece of code (e.g.,
a sorting function).  In C++ a generalization of a function is
something that we can call.  We call it a *callable*.  Calling a
callable has the syntax of calling a function (i.e., applying the `()`
operator), and the function interface: we know the types of the
arguments and the return value.

The goal of that generalization is to:

* avoid calling a function indirectly, i.e., using a pointer, so that
  a function being called can be inlined (i.e., compiled into the
  place of call),

* allow for keeping some extra (which are not passed as call
  arguments) data, which we cannot do with a function pointer.

The standard library is using (passing, keeping as a member field)
callables **by value** (i.e., not by reference), so **copying a
callable should be fast**.  Callables passed to standard algorithms
(e.g., `std::sort`) and standard containers (e.g.,
`std::priority_queue`) should be copied fast.  That means, a callable
should not keep a lot of data that would be copied.

Callable is frequently used by value (e.g., by the standard library),
but it can be used by reference or by pointer too.

## Motivation

We sort integers below.  We can do it, because integers have a
built-in operator `<` defined:

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

Below we sort data of a class type, and to this end we need to define
the ordering between the objects with the **comparison operator**,
i.e., **the `<` operator**.  We defined the operator as a member
function: `this` is the first object to compare, and the function
parameter is the second object to compare.  The member comparison
operator should be declared as `const` (because it should not modify
its object, i.e., `this`), and it should take the other operand by a
const reference (because it should not change that operand).

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Function `std::sort` is using the '<' operator if we do not provide a
comparison callable as the last call argument.  We can get the same
effect as in the example above if we pass as the last argument an
object (**a functor**) of class `std::less<A>`, which uses the `<`
operator:

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

We can sort in ascending order if we pass a functor of the
`std::greater` structure.  That structure is using the `>` operator,
and so we have to define it instead of the `<` operator.

{% highlight c++ %}
{% include_relative motivation4.cc %}
{% endhighlight %}

With `std::sort`, we do not always have to use the `<` operator, and
instead we can pass a callable to induce ordering.  A callable can be
passed not only to a function, but also to a constructor, which can
store the callable as a member field, as, e.g., `std::priority_queue`
does.  Here's an example, which we'll modify later:

{% highlight c++ %}
{% include_relative pq.cc %}
{% endhighlight %}

# Callable types.

A callable is either:

* a pointer to a function,

* a functor.

## A pointer to a function.

An expression that is only the name of a function (without the `()`
operator) is treated as the address of that function.  Having this
address, we can call the function.  The only operations we can do with
a function pointer is: take a function address, call the function.

{% highlight c++ %}
{% include_relative function.cc %}
{% endhighlight %}

In the example below, we pass a pointer to a comparison function.

{% highlight c++ %}
{% include_relative pq_foo.cc %}
{% endhighlight %}

## A functor.

A functor is an object on which we can call the `()` operator.  The
exact definition of the `()` operator depends on how we call a
functor.  In comparison with a function, a functor is more capable,
because it can keep some extra data passed to its constructor.

A functor can act just like a function when it keeps no data.  For
example, types `std::less` and `std::greater` act like functions,
because they do not store any data.

By default, the priority queue uses `std::less`, and returns the
largest element.  To make the priority queue return the smallest
element, we can pass it a functor of type `std::greater`:

{% highlight c++ %}
{% include_relative pq_ro.cc %}
{% endhighlight %}

Here we define a functor type, which acts like a function:

{% highlight c++ %}
{% include_relative pq_fo1.cc %}
{% endhighlight %}

In the example below we pass to a functor a boolean value that is used
by the call operator.  This value is passed at run-time.  This
functionality couldn't be achieved with a function.

{% highlight c++ %}
{% include_relative pq_fo2.cc %}
{% endhighlight %}

### Domknięcie

Domknięcie (ang. closure) jest funktorem, który jest wynikiem
opracowania wyrażenia lambda.

{% highlight c++ %}
{% include_relative pq_lambda1.cc %}
{% endhighlight %}

A tu wersja z dodatkowym argumentem domknięcia przekazywanym w czasie
uruchomienia:

{% highlight c++ %}
{% include_relative pq_lambda2.cc %}
{% endhighlight %}

# Callable a czas kompilacji czy uruchomienia

Callable może być określone (o który callable dokładnie chodzi) w
czasie **uruchomienia**, albo **kompilacji**.

## Callable w czasie uruchomienia

Jeżeli callable jest ustalane w czasie uruchomienia, to kod callable
będzie wywołany i nie będzie wkompilowany (ang. inlined) w miejsce
wywołania, no bo nie wiadomo co wkompilować.  Proszę sprawdzić kod
wynikowy przykładu niżej (z Code Explorer lub z użyciem narzędzia
`objdump`).

{% highlight c++ %}
{% include_relative run.cc %}
{% endhighlight %}

## Callable w czasie kompilacji

Jeżeli w czasie kompilacji callable jest znane i nie zmienia się w
czasie uruchomienia, to może ono być wkompilowane w miejscu wywołania.
Jeżeli chcemy użyć inne callable, to musimy zmienić kod źródłowy.  Oto
przykład:

{% highlight c++ %}
{% include_relative compile1.cc %}
{% endhighlight %}

Przykład niżej pokazuje wkompilowanie domknięcia.  Przykład pokazuje
też brak narzutu wydajnościowego użycia domknięcia.

{% highlight c++ %}
{% include_relative compile2.cc %}
{% endhighlight %}

# Typ przyjmowanego callable

Typ przyjmowanego callable określamy jako typ parametru funkcji czy
konstruktora.  Ten typ możemy zdefiniować *dokładnie*, z użyciem
*`std::function`*, lub *szablonowo*.

## Dokładnie zdefiniowany typ callable

Możemy dokładnie określić typ przyjmowanego callable jako typ
wskaźnika na funkcję, jak w przykładzie niżej.  Co ciekawe, wyrażenie
z domknięciem (w przykładzie jest to `[]{cout << "World!\n";}`) może
być niejawnie rzutowane na wskaźnik na funkcję domknięcia, dlatego ten
przykład się kompiluje.

{% highlight c++ %}
{% include_relative passing1.cc %}
{% endhighlight %}

Możemy też określić typ przyjmowanego callable jako konkretny typ
funktora.

{% highlight c++ %}
{% include_relative passing2.cc %}
{% endhighlight %}

## `std::function` jako callable

Klasa szablonowa `std::function` dale możliwość przekazywania
dowolnego callable: wskaźnika, funktora czy domknięcia, pod warunkiem,
że callable ma wymagane typy parametrów i wyniku, które podajemy jako
argument szablonu.

Dwie ważne funkcjonalności `std::function`:

* Obiekt klasy `std::function` opakowuje i przechowuje przez wartość
  przekazany callable (więc callable jest kopiowany), udostępniając
  ujednolicony interfejs (jeden składowy operator wywołania)
  niezależny od typu przechowywanego callable.

* Obiekt klasy `std::function` może mieć zmieniany callable w czasie
  uruchomienia, a te callable mogą mieć różne typy.

Ta funkcjonalność `std::function` niestety jest okupiona narzutem
wydajnościowym pośredniego wywołania i kopiowania callable.  Jeżeli
tej funkcjonalności nie potrzebujemy, to nie używamy `std::function`.

{% highlight c++ %}
{% include_relative passing3.cc %}
{% endhighlight %}

## Szablonowy typ callable

Typ callable może być parametrem szablonu.  Wtedy na etapie kompilacji
funkcja jest konkretyzowana dla tego konkretnego callable, co
przekłada się na maksymalną wydajnośc, bo kod wynikowy generowany jest
"na miarę".

Użycie szablonu nie wyklucza użycie `std::function`, która może być po
prostu argumentem szablonu.

{% highlight c++ %}
{% include_relative passing4.cc %}
{% endhighlight %}

# Wydajność

Przykład niżej demonstruje wydajność użycia różnego rodzaju callable
dla kolejki priorytetowej i sortowania.  Proszę skompilować program z
opcją `-O3`.

{% highlight c++ %}
{% include_relative timing.cc %}
{% endhighlight %}

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
