---
title: Expression categories
---

# Introduction

## The value of an expression

An expression can be:

* a literal: `3.14`,
* a variable: `x`,
* an operator with operands: `x + y`,
* a function call: `foo(x)`.

**The value of an expression** is the result of evaluating an
  expression.

The value of an expression has:

* a type (e.g., `int`, `bool`, `class A`) known at compile time,

* a value of the type (e.g., `5`, `false`, `A()`) known at run time,

* a category (e.g., lvalue, rvalue) known at compile time.

## History: CPL, C, C++98

Two expression categories introduced in the CPL language (about half a
century ago) were:

* **lvalue** (``left of assignment'' value),
* **rvalue** (``right of assignment'' value).

In C, expressions are either lvalues (for **locator** value; a locator
is something that locates (points to) the value, e.g., the name of a
variable).  In C, a **non-lvalue** is an expression that is not an
lvalue.  There is no rvalue in C!

C++98 adopted lvalues from C, and named the expressions that are not
an lvalue as an **rvalue**.

# Details

## Category of an expression

In C++, the two most important categories of an expression are: the
lvalue category and the rvalue category.  In short, an lvalue is an
expression of the lvalue category, and an rvalue is an expression of
the rvalue category.

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

## Modern C++: changes

In modern C++ new expression categories were introduced: prvalue,
glvalue, and xvalue.  However, the most important categories are still
lvalue, and rvalue.

We need to learn the details of the lvalue and rvalue categories to
understand and efficiently use the modern C++.  For instance, the
following is a statement from <cppreference.org>, which is hard to
understand without knowing the lvalue and rvalue details:

> Even if the variable's type is *rvalue reference*, the expression
> consisting of its name is an *lvalue expression*.

## The lvalue category

It's hard to find a short and succinct definition in the C++ standard,
because the meaning of the lvalue category is spread all over the
standard.  But the following is a good description of the lvalue
category.

If `&<expr>` compiles, then `<expr>` is an lvalue.  That is, if we can
take the address of an expression, then this expression is an lvalue.

An expression with a variable name (e.g., `x`) is always an lvalue.

The examples of lvalues are:

* the name of a variable: `x`
* the name of a function: `foo`
* a string literal: `"Hello World!"`
* the results of the prefix incrementation: `++i`

## The rvalue category

An expression is an rvalue, if it's not an lvalue.  We can't take the
address of an rvalue.

The examples of rvalues are:

* a numeric literal: `1`
* a temporary object: `std::string("Hello World!")`
* the result of the sufffix incrementation: `i++`
* a function call: `foo()`, if `int foo();`

## From lvalue to rvalue

The C++ standard defines this *standard conversion*: an lvalue can be
implicitly (i.e., without a programmer explicitly requesting it)
converted to an rvalue if needed.

For instance, the `+` operator for an integer type (e.g., `int`)
requires rvalues as its operands.  In the following example the `+`
operator expects rvalues, and so the lvalues `x` and `y` are converted
to rvalues.

{% highlight c++ %}
{% include_relative conversion1.cc %}
{% endhighlight %}

For instance, the unary `*` operator (i.e., the dereference operator)
requires a value of a memory address, which is an rvalue.  However, we
can use the dereference operator with an lvalue too, because that
lvalue will be converted to an rvalue.

{% highlight c++ %}
{% include_relative conversion2.cc %}
{% endhighlight %}

There is no standard or implicit conversion from an rvalue to an
lvalue.  For example, the reference operator (i.e., the unary `&`
operator, a.k.a. the take-the-address-of operator) expects an lvalue.
The rvalue that you try to pass will not be converted to an lvalue.

{% highlight c++ %}
{% include_relative conversion3.cc %}
{% endhighlight %}

## Example of the increment operator

The increment operator (i.e., the `++` operator) requires an lvalue as
its operand.  This requirement applies to both the prefix and the
suffix versions of the operator.

{% highlight c++ %}
{% include_relative increment1.cc %}
{% endhighlight %}

The expression of the increment operator is:

* an **lvalue** for the **prefix** version of the operator, i.e., the
  `++<expr>` is an lvalue, because the prefix increment operator
  returns a reference to the just-incremented object it got as an
  operand,

* an **rvalue** for the **suffix** version of the operator, i.e., the
  `<expr>++` is an rvalue, because the suffix increment operator
  returns a temporary copy (which is an rvalue) of the object is got
  as an operand.

Therefore `++++x` compiles, and `x++++` doesn't.

{% highlight c++ %}
{% include_relative increment2.cc %}
{% endhighlight %}

The same applies to the decrement operator.

## Temporary objects

A temporary object (or just a temporary) is an object that is created
when an expression is evaluated.  A temporary is automatically
destroyed when it is not needed anymore.

A temporary is needed when:

* evaluating an operation: `1 + 2`, `string("T") + "4"`

* when passing an argument to a function: `foo(A())`

* when returning an object from a function: `string x = foo();`

* throwing an exception: `throw A();`

In C++98 (the first C++ standard) temporaries were always copied.
However, the return value optimization (RVO) prevented the copying of
objects retured by value from functions.

Starting with C++11, temporaries can be *moved*, and the creation of
temporaries can be *elided* (i.e., avoided) by creating object in the
place where they are supposed to finally be.

A temporary is an object, not an expression, and so a temporary is
neither an lvalue nor an rvalue, because an object has no categoty of
expression.  An object is used in an expression that is either of the
lvalue or rvalue category.  Usually a temporary is created in rvalue
expressions.

## Functions and categories of expressions

Function `foo`, (e.g., `void foo(<params>)`) can be used in an
expression in two ways:

* by name only:

  * the expression: `foo`,

  * that expression is an lvalue, 

  * we can take the address of that expression: `&foo`,

* by a function call:

  * the expression: `foo(<args>)`,

  * the category of that expression expression depends on the return
    type of the function called:

    * if the return type is a reference type, then that expression is
      an lvalue: e.g., if `int &foo();`, then `foo()` is an lvalue,

    * if the return type is not a reference type, then that expression
      is an rvalue: e.g., if `int foo();`, then `foo()` is an rvalue.

## Incomplete types and categories of expressions

An incomplete type is the type that was either:

* declared, but not defined,

* or defined as an abstract class.

Expressions of the incomplete type can only be lvalues.

{% highlight c++ %}
{% include_relative incomplete.cc %}
{% endhighlight %}

# Conclusion

An expression has a category.  An value of some type (e.g., of class
`A` or type `int`) has no category.

What we can do with an expression depends on its category.

Every expression is either an lvalue or an rvalue.

We covered only the basics, there is more: glvalue, prvalue, xvalue.

<!-- LocalWords: lvalue lvalues rvalue rvalues -->
<!-- LocalWords: decrementation incrementation -->
<!-- LocalWords: dereference expr unary -->
<!-- LocalWords: glvalue prvalue xvalue -->
