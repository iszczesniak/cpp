---
title: Expression categories
---

# Introduction

Expression categories are fundamental, yet difficult to understand.
It's all about the details of the **lvalues** and **rvalues**, about
which we don't think in our daily programming.

To understand the meaning of the lvalues and rvalues, it's best to go
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

## The definitions of lvalues and rvalues

You can look in vain for a concise and correct definition of lvalues
and rvalues in the C++ standard.  The C++ standard, which has about
1500 pages, defines them partially is various places, as needed.

Furthermore, in modern C++ new expression categories were introduced:
prvalue, glvalue, and xvalue.  However, the most important categories
are still lvalue, and rvalue.

We need to learn the details of the lvalue and rvalue categories to
understand and efficiently use the modern C++.  For instance, the
following is a statement from <http://cppreference.com>, which is hard
to understand without knowing the lvalue and rvalue details:

> Even if the variable's type is an *rvalue reference*, the expression
> consisting of its name is an *lvalue expression*.

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

{% highlight c++ %}
{% include_relative wrong-lvalue.cc %}
{% endhighlight %}

The assignment operator for the integral types expects an lvalue on
the left, so we cannot write `1 = 1`.  Here is a more elaborate
example:

{% highlight c++ %}
{% include_relative assignment.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative left-rvalue.cc %}
{% endhighlight %}

## From lvalue to rvalue

The C++ standard defines this *standard conversion*, which is applied
without the programmer explicitly requesting it:

> An lvalue of a non-function, non-array type T can be converted to an
> rvalue.

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
suffix versions of the operator.  The same applies to the decrement
operator.

{% highlight c++ %}
{% include_relative increment1.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative increment2.cc %}
{% endhighlight %}

As a side note:

* the prefix version has lower precedence than the suffix version,

* the prefix version has the right-to-left associativity,

* the suffix version has the left-to-right associativity.

In the example below, `std::string` has the suffix increment operator
defined.  The loop with the prefix operator would be more complicated.

{% highlight c++ %}
{% include_relative string.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative tmp-fun.cc %}
{% endhighlight %}

### A temporary as an exception

An expression with a temporary can be an argument of the `throw`
instruction, in which case that expression is an rvalue.  If a catch
block catches the exception by a reference, the expression with that
reference name is an lvalue even though the reference is bound to an
rvalue.

That example follows.  The constructor outputs the address of the
object, so that we can make sure it's the same object in the catch
block:

{% highlight c++ %}
{% include_relative tmp-except.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative overloading.cc %}
{% endhighlight %}

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

    * if the return type is *a reference* type, then that expression
      is an *lvalue*,

    * if the return type is *not a reference* type, then that
      expression is *an rvalue*.

This is an example of a function call that is an lvalue:

{% highlight c++ %}
{% include_relative lvalue-call.cc %}
{% endhighlight %}

This is an example of a function call that is an rvalue:

{% highlight c++ %}
{% include_relative rvalue-call.cc %}
{% endhighlight %}

## Incomplete types and categories of expressions

An incomplete type is the type that was either:

* declared, but not defined,

* or defined as an abstract class.

Expressions of the incomplete type can be only lvalues (and so rvalues
can be only of complete types).

{% highlight c++ %}
{% include_relative incomplete.cc %}
{% endhighlight %}

# Conclusion

An expression has a category.  A value of some type (e.g., of class
`A` or type `int`) has no category.

What we can do with an expression depends on its category.

Every expression is either an lvalue or an rvalue.

We covered only the basics, there is more: glvalue, prvalue, xvalue.

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
