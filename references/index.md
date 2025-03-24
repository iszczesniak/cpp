---
title: References
---

# Introduction

These are the most important facts about references:

* Reference is an alias (a name) for some data (a variable, an object,
  a temporary).

* Reference has no identity, and so we cannot take its address.

* When using a reference to an object, we use the object member
  selection syntax (i.e., `object.member`), and not the object member
  selection through a pointer syntax (i.e., `pointer->member`).

* A reference must be initialized, and so there are no null references
  like there can be null pointers.

* Unlike a pointer, a reference cannot be changed to be an alias for
  some other data.

* A reference type cannot have the `const` and `volatile` type
  qualifiers.

* There is a reference to a pointer, but not a pointer to a reference.

* A reference can be an element of `std::pair` and `std::tuple`, but not
  of a container or an array.

* There is type `void *`, but not `void &` (thank goodness).

The main uses of references:

* passing an argument to a function by reference,

* returning a result from a function by reference,

* referencing data in an object member field,

* accessing data read-only (a const reference).

We say that a reference *binds to* data, which means something like
*points to*, though "points to" is used when talking about pointers.

A reference binds to the *data* of an lvalue, or an rvalue, but in
short we say that a reference binds to an lvalue or an rvalue.

C++ references are like no references of other languages: in C++ a
reference might not exists at run-time, because it was optimized out
at compile-time.

In languages like Java or C#, references are pointers with the
shared-ownership semantics (i.e., a reference can be copied, and the
object exists as long as at least one reference exists), and with the
object member selection syntax.  In these languages references must
exist at run-time.

As an example that references are optimized out at compile-time, there
are two programs below that produce the same output, but in the second
one we use references.  However, at compile-time, the references are
gone.

Save this file as `test1.cc`:

```cpp
{% include_relative test1.cc %}
```

Save this file as `test2.cc`:

```cpp
{% include_relative test2.cc %}
```

Now compile them to the assembly code with:

`g++ -S -O3 test1.cc test2.cc`

Now there are two files with the assembly code: `test1.s`, and
`test2.s`.  Take a look at one of them:

`c++filt < test1.s | less`

Compare them to see that they are instruction-to-instruction the same:

`diff test1.s test2.s`

# Reference types

There are three reference types:

* `T &` - *an lvalue reference*: binds to data that we can modify, but
  not move (because they still will be needed),

* `const T &` - *a const reference*: binds to data that we neither can
  modify nor move,

* `T &&` - *an rvalue reference*: binds to data that we can both
  modify and move (because they soon will not be needed).

The reference types we use only in the definition of a variable type
or of a function return type.  An expression is never of a reference
type, because a reference is replaced with the data the reference
refers to. [expr.type]

## Terms lvalue and rvalue in type names

Expressions are called an lvalue or an rvalue, e.g.:

* `"1"` is an lvalue,

* `1` is an rvalue.

These terms are also used to name a reference type:

* `int &x = <expr>;` - expression `x` is of the *lvalue reference*
  type, and of the lvalue category,

* `int &&x = <expr>;` - expression `x` is of the *rvalue reference*
  type, but of the lvalue category.

NOW I GET IT: *Even if the variable's type is an rvalue reference, the
expression consisting of its name is an lvalue expression.*

## Lvalue reference

An lvalue reference can bind to an lvalue, but not to an rvalue.

We define an lvalue reference like this:

`T &name = <expr>;`

Reference `name` binds to data of type T.  That thingy `&` is called
the lvalue reference **declarator**.  The reference is initialized
with expression `<expr>`.

Here are some examples:

```cpp
{% include_relative lref.cc %}
```

Here are some examples for containers and arrays:

```cpp
{% include_relative containers.cc %}
```

Here are some examples for `std::pair` and `std::tuple`:

```cpp
{% include_relative quasi.cc %}
```

## Const reference

We define a const reference like this:

`const T &name = <expr>;`

Precisely, it is called an lvalue reference that binds to the const
data of type `T`, i.e., the `const` qualifies the type of the data and
not the reference.  The reference itself is not really const because
we can't change the reference to bind to something else anyway.
Nonetheless, it's called the const reference for short; no need to say
it's an lvalue reference to const data.

The const reference was introduced so that the data can be referenced
read-only.  For instance, a function can accept an argument by const
reference, thus ensuring that the argument will not be modified.
Furthermore, in order to let a function accept a temporary (i.e., an
rvalue) as an argument, C++98 stated:

**A const reference can bind not only to an lvalue, but to an rvalue
too.**

Here are some examples:

```cpp
{% include_relative cref.cc %}
```

## Rvalue reference

An rvalue reference can bind to an rvalue, but not to an lvalue.

We define an rvalue reference like this:

`T &&name = <expr>;`

The rvalue reference declarator is `&&`.

The rvalue reference was introduced in C++11 to enable:

* the move semantics,

* the perfect forwarding of function arguments.

Here are some examples:

```cpp
{% include_relative rref.cc %}
```

## A reference cannot rebind

Every reference (not only the const reference) cannot rebind to a new
expression.  A reference can only be initialized, i.e., bound to an
expression once.  Such rebinding would be required in the assignment
operator of a class-type, which has a reference member field, as in
this example:

```cpp
{% include_relative members.cc %}
```

## Qualifiers

A pointer type can be cv-qualified, i.e., can have the `const` or
`volatile` qualifiers, while a reference type cannot (i.e., can only
be cv-unqualified).

A pointer example:

```cpp
{% include_relative qualifiers_ptr.cc %}
```

A reference example:

```cpp
{% include_relative qualifiers_ref.cc %}
```

In the above example we used the qualifiers in reference declarations
but not at the **top level**.  A top-level qualifier for a reference
type would be on the right of the `&` declarator but is disallowed
there.

## A reference to a pointer, but not the other way around.

A reference to a pointer exists, but a pointer to a reference doesn't.

```cpp
{% include_relative r2p.cc %}
```

# Reference tricks

## Reference type and function overload resolution

A function can be overloaded depending on the parameter types, and
this applies to references too.  We can have these overloads:

* `void foo(T &);` - overload #1,
* `void foo(const T &);` - overload #2,
* `void foo(T &&);` - overload #3.

For a call expression `foo(<expr>)`, a compiler will choose (which is
called *overload resolution*):

* overload #1, if `<expr>` is an lvalue of a non-cost type,

* overload #2, if `<expr>` is an lvalue of a const type,

* overload #3, if `<expr>` is an rvalue.

A const reference (used in overload #2) can bind to an lvalue of a
non-const type or to an rvalue, so when there is no overload #1 and
#3, a compiler will choose overload #2 instead.

Here's a complete example:

```cpp
{% include_relative overloading.cc %}
```

## Explicit conversion from an lvalue to an rvalue

We already know the standard conversion that **implicitly** converts
an lvalue to an rvalue.  However, that standard conversion is
suppressed in the initialization of an rvalue reference: the
initializing expression must by an rvalue ([dcl.init.ref]).

We can **explicitly** get an rvalue reference to an lvalue with
`static_cast<T &&>(<expr>)`, where `<expr>` can be an lvalue or an
rvalue.  This is, however, a bit wordy, since we have to type in the
type `T`.

It's easier to get an rvalue reference with `std::move(<expr>)`, where
`<expr>` can be an lvalue or an rvalue.  `std::move` is a function
template: a compiler will deduce the type `T` based on `<expr>`, so we
don't have to type it in.  That function uses `static_cast<T
&&>(<expr>)`.

Here's an example:

```cpp
{% include_relative move.cc %}
```

### The use case

I can think of one use case only.  We use `std::move(x)` to explicitly
enable the move semantics for object `x` (i.e., we turn `x` from an
lvalue to an rvalue), which by default would not have the move
sematics enabled, because the expression `x` is an lvalue.  We enable
the move semantics by making the compiler choose a different overload
depending on category of the expression.

## A temporary lifetime extension by reference

The lifetime of a temporary is extended by the reference that binds to
it.  The temporary will be destroyed when the reference goes out of
scope.  Otherwise, a temporary would be destroyed after the expression
was evaluated.

```cpp
{% include_relative tmp.cc %}
```

A reference field has to be initialized by a constructor but not with
a temporary expression [class.base.init#8].  The following example is
ill-formed:

```cpp
{% include_relative tmp2.cc %}
```

# Conclusion

* A reference gives us a way to refer by name to some data.

* A reference is initialized, and then cannot be changed.

* Three reference types:

  * an lvalue reference, which can bind to an lvalue only,

  * a const reference, which can bind to both an lvalue and rvalue,

  * an rvalue reference, which can bind to an rvalue only.

* A reference extends the lifetime of a temporary it's bound to.

# Quiz

* What are the reference types, and what are their hallmarks?

* What can we initialize a const reference with?

* Can we get an rvalue reference to a non-const lvalue?

{% include rid %}

<!-- LocalWords: lvalue lvalues rvalue -->
