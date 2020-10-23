---
title: Callable, sth to call
---

# Introduction

In C we use a function pointer to ship a piece of code (e.g., that
establishes order between objects) to some other piece of code (e.g.,
a sorting function).  In C++ a generalization of a function is
something that we can call.  We call it a **callable**.  Calling a
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

Function `std::sort` is using the `<` operator if we do not provide a
comparison callable as the last call argument.  Well, `std::sort` is
actually using an object of type `std::less` which in turn uses the
`<` operator.  For comparing the sorted elements, the implementation
of `std::sort` does not use the `<` directly, because it would be
stuck with it, and be unfit for customization.  Instead, the
implementation uses a callable for comparison.

No wonder that we can get the same effect as in the example above if
we pass as the last argument an object of type `std::less<A>` (that's
a callable), because if we didn't, it would be used anyway:

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

With `std::sort`, we do not always have to use the `<` operator, and
instead we can pass a callable to induce ordering.  We can sort in
ascending order if we pass an object of the `std::greater` type.  That
type is using the `>` operator, and so we have to define it instead of
the `<` operator.

{% highlight c++ %}
{% include_relative motivation4.cc %}
{% endhighlight %}

A callable can be passed not only to a function, but also to a
constructor, which can store the callable as a member field, as, e.g.,
the standard priority queue (type `std::priority_queue`) does.  Here's
an example, which we'll be modifying later:

{% highlight c++ %}
{% include_relative pq.cc %}
{% endhighlight %}

# Callable types

A callable is either:

* a pointer to a function,

* a functor.

## A pointer to a function

An expression that is only the name of a function, e.g., `foo`,
(without the `()` operator) is treated as the address of that
function.  We can also take the address of a function by preceeding
the name of the function with the `&` operator, e.g., `&foo`.  These
ways of taking a function address are equivalent, which is
inconsistent, because there should be just one way.

Having this address, we can call the function.  The only operations we
can do with a function pointer is: take a function address, call the
function.

{% highlight c++ %}
{% include_relative function.cc %}
{% endhighlight %}

Here we sort descendingly by passing a callable, which is a function
pointer:

{% highlight c++ %}
{% include_relative sort_foo.cc %}
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

In the example below we define a simple functor type, create a
functor, and call it.  The functor is a callable, because we can call
it.  Since the `()` operator was defined constant, we can call it for
constant functors.

{% highlight c++ %}
{% include_relative functor1.cc %}
{% endhighlight %}

We can store some data in a functor:

{% highlight c++ %}
{% include_relative functor2.cc %}
{% endhighlight %}

A functor acts just like a function when it keeps no data.  For
example, types `std::less` and `std::greater` act like functions,
because they do not store any data.  Such functor types introduce no
performance hit: the constructors and destructors are empty, so they
generate no code, and the comparison function is inlined.  It's as
fast as it can be.

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

# Closure

**Closure** is a functor which is the result of a **lambda
expression**.  A lambda (in short for a lambda expression) is
*syntactic sugar* for conveniently creating functors: they help us
create functors with less writing in comparison with creating a
functor class first, and then creating a functor.  We could do away
with lambda expressions, and achieve the same functionality with
functors.  Lambdas are handy.

Since a closure is an object, it must have some type, but we usually
do not need it, and so we say that a closure is of an *anonymous
type*.  We can get the type of a closure with the `decltype` operator.

## Syntax

Lambda expressions can be nuanced, and we'll not cover all the
nuances.  However, most lambdas are of this syntax:

`[capture-list](param-list) mutable {body}`

The `capture-list` and `param-list` are comma-separated.  If
`param-list` is empty, the `()` can be dropped.  Even if
`capture-list` and `body` are empty, `[]` and `{}` cannot be dropped.

The `capture-list` can have:

* either `=` or `&`, but not both, e.g., `[=]`, or `[&]`, but not `[&,
  =]`,

* captured variable names that can, but do not have to be, preceded by
  `&`, e.g., `[&x]`,

* declaration of the form `name-in-closure = variable-name` that can,
  but do not have to be, preceded by `&`, e.g., `[&x = y]`.

The `param-list` is the list of function parameters, just like for a
regular function.

The `mutable` specifier is optional.  By default the member `()`
operator function is defined constant, but we can make it non-const
with the `mutable` specifier.

Therefore the simplest lambda is `[]{}`.  Here we create a closure and
call it in one go (in one expression):

{% highlight c++ %}
{% include_relative capture1.cc %}
{% endhighlight %}

Expression `[]{}()` is simply translated into this code:

{% highlight c++ %}
{% include_relative capture1a.cc %}
{% endhighlight %}

## Semantics

A lambda creates a functor type (a structure or a class), and an
object of this type.  These are the basic facts:

* The captured variables are stored as fields in the functor.

* The `param-list` becomes the parameter list of the member `()`
  operator function.

* The member `()` operator function is const unless `mutable` is
  specified.

* The `body` becomes the body of the member `()` operator function.
  The return type of that function is deduced based on the expression
  of the return statement in the body.  If there is no return
  statement, the return type is `void`.

The `capture-list` describes how to capture (access) variables from
the scope of the lambda expression, so that they are available in the
body.  The scope is the fragment of code where variables are
accessible: the global scope, the class scope, the function scope, and
the block scope.

The `capture-list` can be empty.  In that case only the parameters of
the `param-list` are available in the `body`.  Example:

{% highlight c++ %}
{% include_relative capture2.cc %}
{% endhighlight %}

The code above is equivalent to this code:

{% highlight c++ %}
{% include_relative capture2a.cc %}
{% endhighlight %}

The `capture-list` can begin with the default policy of capturing
variables either by value or by reference.  If a default capture
policy is given, *all variables* used in the body are captured, and we
do not have to list them.

We set the default capture-by-value policy with `=`.  When a variable
is captured by value, the closure has a copy of the variable as a
member field, i.e., the member field was initialized by copying the
value of the captured value.  For example:

{% highlight c++ %}
{% include_relative capture3.cc %}
{% endhighlight %}

The code above is equivalent to this code:

{% highlight c++ %}
{% include_relative capture3a.cc %}
{% endhighlight %}

We set the default capture-by-reference policy with `&`.  When a
variable is captured by reference, the closure has a member reference
to the captured variable, i.e., the member reference was initialized
with the captured variable.  For example:

{% highlight c++ %}
{% include_relative capture4.cc %}
{% endhighlight %}

The code above is equivalent to this code:

{% highlight c++ %}
{% include_relative capture4a.cc %}
{% endhighlight %}

## Examples

Here's an example of using a lambda with a priority queue:

{% highlight c++ %}
{% include_relative pq_lambda1.cc %}
{% endhighlight %}

Here we pass an argument to a closure:

{% highlight c++ %}
{% include_relative pq_lambda2.cc %}
{% endhighlight %}

<!-- LocalWords: callable callables constructor inlined -->
