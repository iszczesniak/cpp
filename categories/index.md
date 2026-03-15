---
title: Expression categories
---

# Introduction

Expression categories are fundamental, yet difficult to understand.
It's all about some details that we don't think of in our daily
programming.  To understand the meaning of categories, it's best to go
through this text, without searching for some deeper meaning at this
time.  Similar advice got Alice from Humpty Dumpty in the novel
"Through the Looking-Glass" by Lewis Carroll:

> “Must a name mean something?” Alice asks Humpty Dumpty, only to get
> this answer: “When I use a word... it means just what I choose it to
> mean – neither more nor less.”

## The value of an expression

An expression can be:

* a literal: `3.14`,
* a variable: `x`,
* an operator with operands: `x + y`,
* a function call: `foo(x)`.

**The value of an expression** is the result of evaluating an
  expression.

An expression has:

* a type (e.g., `int`, `bool`, `class A`) known at compile time,

* a value of the type (e.g., `5`, `false`, `A()`) known at run time,

* a category (e.g., lvalue, rvalue) known at compile time.

## History: CPL, C, C++98

Two expression categories introduced in the CPL language (about half a
century ago) were:

* **lvalue**: ``left of assignment'' value, i.e., any expression that
    can go on the left of the assignment operator is an lvalue,

* **rvalue**: ``right of assignment'' value, i.e., any expression that
    can go on the right of the assignment operator is an rvalue.

CPL defined the lvalue and rvalue categories in relation to the
assignment operator.  These definitions are only of historical
importance, and do not apply to C++.

In C, expressions are either lvalues (for **locator** value; a locator
is something that locates (points to) the value, e.g., the name of a
variable).  In C, a **non-lvalue** is an expression that is not an
lvalue.  There is no rvalue in C!

C++98 adopted lvalues from C, and named the expressions that are not
an lvalue as an **rvalue**.

# Details

## Category of an expression

The expression category determines what we can do with the expression.
Some operations we can do only with an lvalue (e.g., `&x`, i.e.,
taking the address of variable `x`), other operations only with an
rvalue.

Example operations for expression `<expr>`:

* assign: `<expr> = 1`
* initialize reference: `<reference type> y = <expr>`
* take the address: `&<expr>`
* dereference: `*<expr>`
* increment: `++<expr>`, `<expr>++`

## The definitions of lvalues and rvalues

Categories evolve.  Bjarne Stroustrup wrote in his "'New' Value
Terminology" paper:

> The terms "lvalue" and "rvalue" are deep in C++'s genes.

Bjarne Stroustrup also wrote in "The Design and Evolution of C++"
something that I think relates to categories:

> Within C++, there is a much smaller and cleaner language struggling
> to get out.

What these two quotes illustrate is the C++ language evolution so that
it meets the user needs better, which explains why the categories
evolve too.

What used to be true about categories in C++98 is still relevant
today, but has been refined and enhanced.  C++ is backward compatible,
so the legacy code still works, but now there are more categories, and
they are better defined.

Prior to C++11, you could look in vain for a concise definition of
lvalues and rvalues in the C++ standard.  The C++03 standard had about
eight hundred pages, and defined them in bits is various places, as
needed.  In C++11, new expression categories were introduced: prvalue,
glvalue, and xvalue.  In C++17, categories were finally defined in
terms of identity and the move semantics.  I think that during C++11
and C++17, the standard committee struggled to get the categories
right.

However, the important categories are still lvalue, and rvalue.  We
need to learn the details of the lvalue and rvalue categories to
understand and efficiently use the modern C++.  For instance, the
following is a statement from <http://cppreference.com>, which is hard
to understand without knowing the lvalue and rvalue details:

> Even if the variable's type is an *rvalue reference*, the expression
> consisting of its name is an *lvalue expression*.

Let's start with two expression categories: the lvalue category and
the rvalue category.  In short, an lvalue is an expression of the
lvalue category, and an rvalue is an expression of the rvalue
category.

## The lvalue category

It's hard to find a succinct definition in the C++ standard of the
lvalue category, because the meaning of the lvalue category is spread
all over the standard.  But the following is a good description of the
lvalue category.

If `&<expr>` compiles, then `<expr>` is an lvalue.  That is, if we can
take the address of an expression, then this expression is an lvalue.

**An expression with a variable name (e.g., `x`) is always an
  lvalue.**

The examples of lvalues are:

* the name of a variable: `x`
* the name of a function: `foo`
* a string literal: `"Hello World!"`
* the results of the prefix incrementation: `++i`

The definition of the lvalue that anything that can go on the left of
the assignment operator is an lvalue does not apply to C++.  You can
have an lvalue on the left of the assignment operator, and the code
will not compile:

```cpp
{% include_relative wrong-lvalue.cc %}
```

The assignment operator for the integral types expects an lvalue on
the left, so we cannot write `1 = 1`.  Here is a more elaborate
example:

```cpp
{% include_relative assignment.cc %}
```

## The rvalue category

An expression is an rvalue, if it's not an lvalue.  We can't take the
address of an rvalue.

The examples of rvalues are:

* a numeric literal: `1`
* an expression that creates a temporary object: `std::string("Hello World!")`
* the result of the sufffix incrementation: `i++`
* a function call: `foo()`, if `int foo();`

The definition of the rvalue as something that should be on the right
of the assignment operator does not apply to C++.  You can have an
rvalue on the left of the assignment operator, and the code will
compile.  For instance, `A()` is an rvalue (that creates a temporary
object), and we can assign to it, because we defined the assignment
operator in class `A`:

```cpp
{% include_relative left-rvalue.cc %}
```

## From lvalue to rvalue

The C++ standard defines this *standard conversion*, which is applied
without the programmer explicitly requesting it, i.e., the conversion
is implicit:

> An lvalue of a (non-function, non-array) type T can be converted to
> an rvalue.

This conversion creates a temporary object that is copy-constructed
from some existing data.  The expression that used the existing data
is called lvalue, the expression that creates a temporary data is an
rvalue.

For instance, the `+` operator for an integer type (e.g., `int`)
requires rvalues as its operands.  In the following example the `+`
operator expects rvalues, and so the lvalues `x` and `y` are converted
to rvalues.

```cpp
{% include_relative conversion1.cc %}
```

For instance, the unary `*` operator (i.e., the dereference operator)
requires a value of a memory address, which is an rvalue.  However, we
can use the dereference operator with an lvalue too, because that
lvalue will be converted to an rvalue.

```cpp
{% include_relative conversion2.cc %}
```

There is no standard or implicit conversion from an rvalue to an
lvalue.  For example, the reference operator (i.e., the unary `&`
operator, a.k.a. the take-the-address-of operator) expects an lvalue.
The rvalue that you try to pass will not be converted to an lvalue.

```cpp
{% include_relative conversion3.cc %}
```

## Example of the increment operator

The increment operator (i.e., the `++` operator) requires an lvalue as
its operand.  This requirement applies to both the prefix and the
suffix versions of the operator.  The same applies to the decrement
operator.

```cpp
{% include_relative increment1.cc %}
```

The expression of the increment operator for built-in types is:

* an **lvalue** for the **prefix** version of the operator, i.e., the
  `++<expr>` is an lvalue, because the prefix increment operator
  returns a reference to the just-incremented object it got as an
  operand,

* an **rvalue** for the **suffix** version of the operator, i.e., the
  `<expr>++` is an rvalue, because the suffix increment operator
  returns a temporary copy (which is an rvalue) of the object is got
  as an operand.

Therefore `++++x` compiles, and `x++++` doesn't.

```cpp
{% include_relative increment2.cc %}
```

As a side note:

* the prefix version has lower precedence than the suffix version,

* the prefix version has the right-to-left associativity,

* the suffix version has the left-to-right associativity.

In the example below, `std::string` has the suffix increment operator
defined.  The loop with the prefix operator would be more complicated.

```cpp
{% include_relative string.cc %}
```

## Temporary objects

A temporary object (or just a temporary) is an object that is created
when an expression is evaluated.  A temporary is automatically
destroyed (i.e., you don't need to explicitly destroy it) when it is
not needed anymore.

A temporary is needed when:

* evaluating an operation: `1 + 2`, `string("T") + "4"`

* when passing an argument to a function: `foo(A())`

* when returning an object from a function: `string x = foo();`

* throwing an exception: `throw A();`

A temporary is an object, not an expression, and so a temporary is
neither an lvalue nor an rvalue, because an object has no category of
expression.  An object is used in an expression that is either an
lvalue or an rvalue.  Usually a temporary is created in rvalue
expressions.

### A temporary as a function argument

An expression with a temporary can be an argument of a function call,
in which case that expression is an rvalue.  If a function takes an
argument by reference (i.e., the parameter of the function is of a
const reference type), the expression with that parameter name is an
lvalue even though the reference is bound to an rvalue.

That example follows.  The constructor outputs the address of the
object, so that we can make sure it's the same object in function
`foo`.

```cpp
{% include_relative tmp-fun.cc %}
```

### A temporary as an exception

An expression with a temporary can be an argument of the `throw`
instruction, in which case that expression is an rvalue.  If a catch
block catches the exception by a reference, the expression with that
reference name is an lvalue even though the reference is bound to an
rvalue.

That example follows.  The constructor outputs the address of the
object, so that we can make sure it's the same object in the catch
block:

```cpp
{% include_relative tmp-except.cc %}
```

We should catch an exception by reference: if we catch it by value,
we're going to copy that exception.  Change the example so that an
exception is caught by value, and you'll see that we get a copy
(you'll see different addresses).

Interestingly, and as a side note: in the example above, that
non-const reference is bound to an rvalue.  C++98 states that only a
const reference can bind to an rvalue, which does not hold in the case
of catching an exception.  In the example above, I would expect
`catch(A &a)` to fail to compile, as it should be `catch(const A &a)`.
Wierd.

Interestingly, and as a side note, a statement block (i.e.,
`{<statements>}`), can be replaced with a single statement, e.g.,
`{++i;}` can be replaced with `++i;`.  However, the try and catch
blocks always have to be blocks, and you cannot remote `{}` even if it
has a single statement.  Wierd.

## Overloading member functions

A member function can be called for both an lvalue or an rvalue.
However, a member function can be declared with a reference qualifier
`&` or `&&` (and therefore be ref-qualified), so that it can be called
for either an lvalue or an rvalue.  Example:

```cpp
{% include_relative over_cat.cc %}
```

## Functions and categories of expressions

Function `foo`, (e.g., `void foo(<params>)`) can be used in an
expression in two ways:

* by name only:

  * i.e., the expression: `foo`,

  * that expression is an lvalue, because we can take its address:
    `&foo`,

* by a function call:

  * i.e., the expression: `foo(<args>)`,

  * that expression is:

    * an lvalue if the function returns a reference (an lvalue
      reference, specifically),

    * an rvalue otherwise.

This is an example of a function call that is an lvalue:

```cpp
{% include_relative lvalue-call.cc %}
```

This is an example of a function call that is an rvalue:

```cpp
{% include_relative rvalue-call.cc %}
```

## Incomplete types and categories of expressions

An incomplete type is the type that was either:

* declared, but not defined,

* or defined as an abstract class.

Expressions of the incomplete type can be only lvalues (and so rvalues
can be only of complete types).

```cpp
{% include_relative incomplete.cc %}
```

# C++11 categories

Prior to C++11, we took little interest in categories, but we have to
from C++11 because of the move semantics.  C++11 extended the category
terminology by:

1. splitting the rvalue category into two new refined categories:

   * **prvalue**,

   * **xvalue**.

2. introducing a new category of **glvalue** to collectively refer to
   both the lvalue and the xvalue.

An expression that is a prvalue or an xvalue is still an rvalue, but
we differentiate between them so that:

* we are better C++ programmers: we can better understand C++
  technical documentation that commonly uses these categories, and so
  that we can implement more efficient code,

* compilers have a fine-grained means of processing expressions: for a
  C++11 compiler, processing an expression as an rvalue is no longer
  enough; a compiler needs to know whether it's a prvalue or an
  xvalue.

The name of:

* prvalue stands for *pure rvalue*,

* glvalue stands for *generalized lvalue*,

* xvalue stands for *any value*.

An xvalue comes from either of:

* an *implicitly* converted prvalue,

* an *explicitly* converted lvalue.

Since C++11, categories are defined in terms of two properties of an
expression:

* whether the expression has **identity**,

* whether the expression can be **moved**.

Now the three basic categories are:

* lvalue: has identity and cannot be moved,

* xvalue: has identity and can be moved,

* prvalue: doesn't have identity and can be moved.

There is no category for an expression that doesn't have identity and
cannot be moved, because no such expression exists.  We report the
above information in a table:

| has identity \ can be moved | no | yes
| no | doesn't exist | prvalue |
| yes| lvalue | xvalue |

The two collective categories are:

* glvalue that has identity,

* rvalue that can be moved.

## More specifics

### Call expression

A call expression of a function that returns:

* by value is a prvalue,

* by reference is a glvalue.

### The lvalue-to-rvalue conversion

Now the lvalue-to-rvalue conversion is now called this way for the
historic reason, but it should be called the glvalue-to-prvalue
conversion.

The newest C++ (March, 2026) standard draft defines the
glvalue-to-prvalue conversion as:

> If T has a class type, the conversion copy-initializes the result
> object from the glvalue.

The results object mentioned above is the object that is the result of
the prvalue materialization.

## Back to constructor elision

**Initialization with a prvalue elides a (copy or move) constructor.**
It may seem that introducing the prvalue is like splitting hair.  Yes,
in statement `A a = A();`, expression `A()` is a prvalue, and so its
value is directly initialized in `a`.  All that hassle just for this?
The worthwhile use case is returning by value, the only one I know of.

In the example below, functions `f` and `g` return by value.  Function
`f` returns right away (without using a local variable) the result of
function `g`.  The result of function `f` initializes the local
variabe `s` of the main function.  Expression `g()` is a prvalue, so
its value is initialized in the return value of `f()`, but `f()` is
also prvalue, so its value in turn is initialized in `s`.  A
constructor was elided twice, because the compiler knew it was dealing
with prvalues.

```cpp
{% include_relative elide1.cc %}
```

The example below is a modified above example: we changed function
`f`, so that it takes an argument by value, and returns by value its
parameter.  The parameter `p` of function `f` is constructed with the
prvalue returned by function `g`, and so a constructor is elided.  The
variable `s` of the main function is constructed with the prvalue
returned by function `f`, and so a constructor is elided.

```cpp
{% include_relative elide2.cc %}
```

## Temporary materialization

Temporary materialization is a fancy name for construcing a temporary
object.

A conversion from a prvalue to an xvalue creates a temporary object,
which is also known as the materialization of a temporary.  While
rvalue can be moved, it's really about moving the xvalue because
prvalue doesn't have an identity.

# Conclusion

An expression has a category.  A value of some type (e.g., of class
`A` or type `int`) has no category.

What we can do with an expression depends on its category.

Every expression is either an lvalue or an rvalue.

# Quiz

* Can an expression be both an lvalue and an rvalue at the same time?

* Is a temporary object an rvalue?

* What does the category of the function-call expression depend on?

* Why does `int i; ++i++;` not compile?

{% include rid %}

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->
