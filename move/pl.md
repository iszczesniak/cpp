---
title: Semantyka przeniesienia
---

# Wprowadzenie

Semantyka przeniesienia dotyczy wyłącznie danych typów klasowych (do
tego zaliczają się także struktury i unie), więc będziemy mówić o
przenoszeniu obiektów, a nie danych.  Obiekt jest daną typu klasowego,
czyli danymi interpretowanymi zgodnie z definicją klasy.  Stan obiektu
nazywamy **wartością obiektu**.

Definicja wartości obiektu zależy od implementacji klasy.  Zwykle
wartością obiektu jest stan obiektów bazowych i składowych.  Jednak na
stan obiektu nie muszą składać się niektóre dane, np. dane podręczne
(ang. cache data).

Wartość obiektu może być kopiowana podczas:

* inicjalizacji: `T t(<expr>);`

* przypisania: `t = <expr>;`

W inicjalizacji i przypisaniu rozróżniamy obiekt źródłowy (wyrażeń
`<expr>` wyżej) i docelowy (zmiennych `t` wyżej).  Obiekt docelowy
jest inicjalizowany obiektem źródłowym.  Obiekt docelowy jest po lewej
stronie operatora przypisania, a źródłowy po prawej.

Fakty o kopiowaniu obiektów:

* Kopiowanie jest czasochłonne, kiedy obiekty są duże.

* Kopiowanie obiektów jest implementowane przez:

  * *konstruktor kopiujący* podczas inicjalizacji,
  
  * *kopiujący operator przypisania* podczas przypisania.

Obiekty źródłowe i docelowe mogą być gdziekolwiek, czyli w dowolnym
obszarze pamięci, nie tylko na stosie czy stercie.  Na przykład,
obiekt źródłowy może być na stosie, a obiekt docelowy w obszarze
pamięci dla danych statycznych i globalnych.  Obiekt nie powinien
wiedzieć, w jakim obszarze pamięci się znajduje.

Kopiowanie może być problemem w zależności od tego czy jest potrzebne
czy nie.  Nie jest problemem, jeżeli jest potrzebne, np. kiedy musimy
wykonać kopię obiektu do zmian, bo oryginału nie możemy zmieniać.

Kopiowanie jest problemem, kiedy jest zbędne, czyli wtedy, kiedy
obiekt źródłowy po kopiowaniu nie jest potrzebny.  Zbędne kopiowanie
pogarsza wydajność: kod będzie działał poprawnie, ale mógłby być
szybszy.

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

{% highlight c++ %}
{% include_relative constructors.cc %}
{% endhighlight %}

### Implementation of the constructor overloads

In the implementation of the move constructor, in the initialization
list of the base and member objects, the initializing arguments should
be rvalues, so that the compiler can choose the move constructors for
the base and member objects.  To this end we can use the `std::move`
function, as shown in the example below, where the copy constructor is
also implemented for comparison.

{% highlight c++ %}
{% include_relative ctor-impl.cc %}
{% endhighlight %}
  
## The copy and move assignment operators

A class can have either the copy assignment operator or the move
assignment operator, both or none.

The move assignment operator of class `T` has a single parameter of
type `T &&`.

### A simple example

In the example below the class has both operators defined:

{% highlight c++ %}
{% include_relative operators.cc %}
{% endhighlight %}

### The return type of the move assignment operator

If `a` and `b` are of type `T`, then expression `a = b = T()` should
move the value of the temporary object `T()` to `b`, and then should
copy the value from `b` to `a`.  That expression is evaluated
right-to-left, because the assignment operator has the right-to-left
associativity.

Therefore, the move assignment operator should return an lvalue
reference, and not an rvalue reference.  If the move assignment
operator returned an rvalue reference, then that expression would move
the value from the temporary object `T()` to `b`, and then move (not
copy) the value of `b` to `a`.

Interestingly, because the move assignment operator returns an lvalue
reference, we can initialize an lvalue reference with the return value
of the operator: `T &l = T() = T();` even though `T &l = T();` would
fail to compile.

### Implementation of the assignment operator overloads

In the implementation of the move assignment operator, the argument
expressions for the assignment operators of the base and member
objects should be rvalues, so that the compiler can choose the move
assignment operators for the base and member objects.  To this end we
can use the `std::move` function, as shown in the example below, where
the copy assignment operator is also implemented for comparison.

{% highlight c++ %}
{% include_relative assign-impl.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative default.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative delete.cc %}
{% endhighlight %}

### Rules for special member functions

All special member functions are implicitly defaulted, but:

* the default constructor will be **undeclared**, if any other
  constructor is *explicitly declared*,

* the copy constructor and the copy assignment operator will be
  **implicitly deleted**, if the move constructor or the move
  assignment operator is *explicitly declared* (so that a programmer
  has to implement, if needed, the copy constructor and the copy
  assignment operators),

* the move constructor and the move assignment operator will be
  **undeclared**, if the copy constructor, the copy assignment
  operator or the destructor is *explicitly declared* (so that the
  legacy code continues to work and doesn't have the move semantics
  stuffed in).

These rules ensure the seamless integration of the move semantics into
the legacy and modern code.  For instance, the legacy code (such as
`std::pair`) that doesn't do any special resource management (in the
copy constructor, the copy assignment operator, and the destructor),
will have the move semantics implemented by default.

## Move-only types

A move-only type can only be moved: it cannot be copied.  This is an
example of a move-only type:

{% highlight c++ %}
{% include_relative move-only.cc %}
{% endhighlight %}

# Implications of the move semantics

## Initialization of function parameters

A function parameter is initialized with the argument expression.  For
a parameter of a non-reference (i.e., we pass the argument by value)
class type, the constructor overload resolution will depend on the
category of the argument expression and the overload availability, as
usual for [a function overloaded with reference
types](../references#reference-type-and-function-overload-resolution).

## Implicit move of returned values

If [the return value optimization
(RVO)](../memory/#return-value-optimization) cannot be used, then the
value of the returned object will be *implicitly moved*, if the
returned object is destroyed when returning from the function.  The
return instruction `return t;` is implicitly converted to `return
std::move(t);`.

Only the return expression consisting of a variable name is implicitly
moved (converted from an lvalue to an rvalue), and other expressions
are not.

We shouldn't explicitly use the `std::move` function (e.g., `return
std::move(t);`) in the return statement whenever we can, because it
disables the RVO.

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

{% highlight c++ %}
{% include_relative implicit1.cc %}
{% endhighlight %}


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

{% highlight c++ %}
{% include_relative implicit2.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative swap.cc %}
{% endhighlight %}

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
