---
title: Move semantics
---

# Introduction

The move semantics applies only to the data of class types, so I'll
talk about *objects*, and not *data* as I do elsewhere.  An object is
an instance of a class type (i.e., a piece of memory interpreted
according to how a class or a structure was defined).  Usually the
state of the object is called the *value*.

The definition of the value of an object depends on the implementation
of the class.  Usually the value of an object is the state of its base
and member objects.  However, there might be some supporting data in
an object (e.g., some cache data that are part of the object state)
that do not have to be part of the object value.

The value of an object can be copied when the object is:

* used to initialize an object,

* used in an assignment expression,

* passed by value as an argument to a function,

* returned by value from a function,

all of which involve:

* either the initialization: `T t(<expr>);`,

* or the assignment: `t = <expr>;`.

We're interested in the case where the source expression `<expr>` is
of a class type, i.e., it has an object, which we call the source
object, or just a source.  Object `t` is the target object, or just a
target.

Important facts about copying:

* Copying takes time when the value to copy is big.

* Copying is implemented by:

  * the *copy constructor* (to initialize an object),

  * the *copy assignment operator* (to assign to an object).

* The source and the target can be *anywhere*.

By anywhere I mean different memory locations, i.e., copying is not
limited to objects on the stack or the heap only.  For instance, the
source can be on the stack, and the target in the fixed-size memory
for static and global data.  Objects should have no clue where they
live.

Copying might be a problem depending on whether it's necessary or not.
It's not a problem, when it's necessary, e.g., when we need to modify
a copy, and leave the original intact.

Copying is a problem when it's unnecessary.  Copying is unnecessary,
when the source is not needed after copying.  Unnecessary copying is a
*performance* problem: the code will work alright, but we wish it was
faster.

# The move semantics

The move semantics allows for moving the value from a source
expression to a target, when copying is unnecessary.  It was
introduced in C++11, but its need was already recognized in the
1990's.  Moving is like salvaging goods (the value) from a sinking
ship (the object that soon will not be needed).

The move semantics takes effect when:

  * an object is initialized, or an object is assigned to,

  * the source expression is an rvalue (e.g., the source is a
    temporary),

  * the type of the target has the move semantics implemented.

The move semantics is implemented by:

  * the **move constructor** (to initialize an object),

  * the **move assignment operator** (to assign to an object).

## How it works

* There is no magic!  An object is not moved bit-by-bit to some other
  place.  The programmer knows every detail and remains in total
  control.

* Only the value is moved.  The source, and the target objects remain
  in memory where they are, and they will be destroyed in a normal
  way.

* After moving, the source must be *consistent*, but its state can be
  *undefined*.  It must be consistent, because it will be destroyed as
  usual.

## The copy and move constructors

A class can have either the copy constructor or the move constructor,
both or none.

The move constructor of class `T` has a single parameter of type `T
&&`.

### A simple example

In the example below the class has both constructors defined:

```cpp
{% include_relative constructors.cc %}
```

### Implementation of the constructor overloads

In the implementation of the move constructor, in the initialization
list of the base and member objects, the initializing arguments should
be rvalues, so that the compiler can choose the move constructors for
the base and member objects.  To this end we can use the `std::move`
function, as shown in the example below, where the copy constructor is
also implemented for comparison.

```cpp
{% include_relative ctor_impl.cc %}
```
  
## The copy and move assignment operators

A class can have either the copy assignment operator or the move
assignment operator, both or none.

The move assignment operator of class `T` has a single parameter of
type `T &&`.

### A simple example

In the example below the class has both operators defined:

```cpp
{% include_relative operators.cc %}
```

### The return type of the move assignment operator

If `x` and `y` are of type `A`, then expression `x = y = A()` should
move the value of the temporary object `A()` to `y`, and then should
copy the value from `y` to `x`.  That expression is evaluated
right-to-left, because the assignment operator has the right-to-left
associativity.

Therefore, the move assignment operator should return an lvalue
reference, and not an rvalue reference.  If the move assignment
operator returned an rvalue reference, then that expression would move
the value from the temporary object `A()` to `y` (as expected), and
then move the value of `b` to `a`, while we would expect the copying.
The implementation is below.

```cpp
{% include_relative assign_cat1.cc %}
```

However, with the above implementation, expression `x = A() = A()` is
incorrectly evaluated.  Expression `A() = A()` indeed moves the value
from the right temporary to the left one, but it's an lvalue (because
the move assignment operator returns an lvalue reference) that becomes
the source expression for the assignment operator for `x`, a copy
assignment operator, a not the expected move one.

Interestingly, the move assignment operator returns an lvalue
reference that we can use to initialize an lvalue reference: `T &l =
T() = T();`.  Such initialization compiles, even though it shouldn't
as `T &l = T();` fails to compile.  That's a shortcoming.

To fix the above incorrect evaluation and the shortcoming, we should
overload the move assignment operator separately for the lvalues and
rvalues.  The correct implementation follows.

```cpp
{% include_relative assign_cat2.cc %}
```

### Implementation of the assignment operator overloads

In the implementation of the move assignment operator, the argument
expressions for the assignment operators of the base and member
objects should be rvalues, so that the compiler can choose the move
assignment operators for the base and member objects.  To this end we
can use the `std::move` function, as shown in the example below, where
the copy assignment operator is also implemented for comparison.

```cpp
{% include_relative assign_impl.cc %}
```

## Overload resolution

The overload resolution of a constructor or an assignment operator
(i.e., whether the copy or the move version is chosen) depends on the
category of the source expression, and the availability of the copy
and move overloads.  The same rules apply as in the overload
resolution for [a function overloaded with reference
types](../references#reference-type-and-function-overload-resolution).

## Special member functions

The special member functions are:

* the default constructor,

* the copy constructor, the copy assignment operator,

* the move constructor, the move assignment operator,

* the destructor.

A special member function can be either undeclared or declared.  A
function can be declared:

* *explicitly* as:

  * *user-defined*: a programmer provides the function definition,

  * *defaulted*: a programmer requests a default implementation,

  * *deleted*: a programmer declares the function as deleted,

* *implicitly* as:

  * *defaulted*: a compiler provides a default definition without the
     user requesting it,

  * *deleted*: a compiler declares the function as deleted without the
     programmer requesting it.

When a function is declared as *deleted* (regardless of whether
implicitly or explicitly), the function is considered in overload
resolution, but when the function is chosen, an error message reports
the function is deleted.

### Explicitly defaulted

A programmer can explicitly request the default implementation of a
special member function with `= default`, like this:

```cpp
{% include_relative default.cc %}
```

### Default implementation

All base and member objects in a defaulted (regardless of whether
implicitly or explicitly):

* default constructor are default constructed,

* copy constructor are copy initialized,

* copy assignment operator are copy assigned,

* move constructor are move initialized,

* move assignment operator are move assigned,

* destructor are destroyed.

### Deleted

A programmer can explicitly request a special member function be
deleted with `= delete`, like this:

```cpp
{% include_relative delete.cc %}
```

### Rules for special member functions

All special member functions are implicitly defaulted (if they are
needed), unless one of the following rules applies:

* *the same old rule*: the default constructor will be **undeclared**,
  if any other constructor is **explicitly declared**,

* *the backward compatibility rule*: the move members will be
  **undeclared** (so that overload resolution does not consider them),
  if the copy members or the destructor are **explicitly declared**:
  the legacy code continues to work the old way because the default
  implementation of move semantics (i.e., the move members) will not
  be stuffed in,

* *the rule for the new code*: the copy members will be **implicitly
  deleted** (so that overload resolution considers them), if a move
  member is **explicitly declared**: a programmer would have to
  declare the copy members, if they are required.

These rules ensure the seamless integration of the move semantics into
the legacy and modern code.  A type that does not manage its resources
in some unusual way (it's about the special members), will have the
copy and move semantics implemented by default.

## Move-only types

A move-only type can only be moved: it cannot be copied.  This is an
example of a move-only type:

```cpp
{% include_relative move_only.cc %}
```

# Implications of the move semantics

## Initialization of function parameters

A function parameter is initialized with the argument expression.  For
a parameter of a non-reference (i.e., we pass the argument by value)
class type, the constructor overload resolution will depend on the
category of the argument expression and the overload availability, as
usual for [a function overloaded with reference
types](../references#reference-type-and-function-overload-resolution).

## Implicit move of returned values

If constructor elision (or the return value optimization) cannot be
used, then the value of the returned object will be *implicitly
moved*, if the returned object is destroyed when returning from the
function.  The return instruction `return t;` is implicitly converted
to `return std::move(t);`.

Only the return expression consisting of a variable name is implicitly
moved (converted from an lvalue to an rvalue), and other expressions
are not.

We shouldn't explicitly use the `std::move` function (e.g., `return
std::move(t);`) in the return statement whenever we can, because it
disables the constructor elision (or the RVO).

There are two cases described below in which the RVO cannot be used,
but the returned value will be implicitly moved.

#### Case 1

When we return a function parameter.  A function parameter is
allocated and initialized in a location on the stack that is different
from the location for the return value.  A function parameter is
destroyed when returning from the function, so we can move the value
from it to the location for the return value.  The return expression
is the name of the parameter only, so the implicit move can take
place.

```cpp
{% include_relative implicit1.cc %}
```


#### Case 2

When we return a base object of a local object.  The local object is
too big to be initialized in the location for the return value, which
is of the size of the base object.  The local object is destroyed when
returning from the function, so we can move the value from its base
object to the location for the return value.  Only the value of the
base object will be moved, which is called *object slicing*, because
we slice off the value of the base object.  The return expression is
the name of the local object only, so the implicit move can take
place.

```cpp
{% include_relative implicit2.cc %}
```

If the local object was static, the value would have to be copied, not
moved.
  
## The `std::swap` function

Let's end with how it all began.  Function `std::swap` is the reason
for the work on the move semantics that started in the 1990's.  This
function showed that it's more efficient to move than to copy.

Function `std::swap` takes by reference two arguments, and swaps their
values.  This function is implemented in the standard library, but in
the example below we also have an example implementation to show
what's going on:

```cpp
{% include_relative swap.cc %}
```

# Conclusion

* The move semantics was introduced in C++11.

* The move semantics is used when copying is unnecessary.

* The move semantics is a performance boost.

* Only the values of rvalues can be moved.

* A compiler can ship the default implementation of the move semantics.

* A programmer doesn't have to know about the move semantics, but it
  will be used by a compiler anyway.

# Quiz

* What do we need the move semantics for?

* How does the move sementics work?

* What's a move-only type?

{% include rid %}

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
