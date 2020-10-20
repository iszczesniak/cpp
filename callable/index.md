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
{% include_relative motivation1.cc %}
{% endhighlight %}

Below we sort data of a user-defined type, and to this end we need to
define the ordering (we could also say to induce order or to establish
order) between the objects with the **comparison operator**, i.e.,
**the `<` operator**.  There are a number of comparison operators that
we can define for a user-defined type: `==`, `!=`, `<`, `<=`, `>`,
`=>`, `<=>`, but for inducing order between elements (the objects of
the user-defined type) the most important operator is the **less-than
operator**, i.e., the `<` operator.  We could refer to the less-than
operator as *the comparison operator*, but the avoid confusion, we
refer to it as the `<` operator.

We defined the `<` operator as a member function: `this` is the first
object to compare, and the function parameter is the second object to
compare.  The member comparison operator should be declared as `const`
(because it should not modify its object, i.e., `this`), and it should
take the other operand by a const reference (because it should not
change that operand).

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Function `std::sort` is using the '<' operator if we do not provide a
comparison callable as the last call argument.  We can get the same
effect as in the example above if we pass as the last argument an
object (**a functor**) of type `std::less<A>`, which uses the `<`
operator:

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

We can sort in ascending order if we pass a functor of the
`std::greater` type.  That type is using the `>` operator, and so we
have to define it instead of the `<` operator.

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

# Callable types

A callable is either:

* a pointer to a function,

* a functor.

## A pointer to a function

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

## A functor

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

### Closure

**Closure** is a functor which is the result of a **lambda
expression**.  A lambda (in short for a lambda expression) is
*syntactic sugar* for conveniently creating functors: they help us
create functors with less writing in comparison with creating a
functor class, and then creating a functor.  We could do away with
lambda expressions, and achieve the same functionality by implementing
manually a functor class.  Lambdas are handy.

Here's an example of using a lambda with a priority queue:

{% highlight c++ %}
{% include_relative pq_lambda1.cc %}
{% endhighlight %}

Here we pass an argument to a closure:

{% highlight c++ %}
{% include_relative pq_lambda2.cc %}
{% endhighlight %}

<!-- LocalWords: callable callables constructor inlined -->
