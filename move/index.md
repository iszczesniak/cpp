---
title: Move semantics
---

# Introduction

The move semantics applies only to the data of class types, so I'll
talk about *objects*, and not *data* as I do elsewhere.  An object is
an instance of a class type (i.e., a piece of memory interpreted
according to how a class or a structure was defined).  The state of
the object is called the *value*.

The definition of the value of an object depends on the implementation
of the class.  Usually the value of an object is the state of its
member fields and base objects.  However, there might be some
supporting data in an object (e.g., some cache data) that do not have
to be part of the object value.

The value of an object can be copied when the object is:

* used to initialize a new object,

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

For a given class type, the move constructor and the move assignment
operator can be:

* user-implemented: the programmer implements them,

* compiler-provided: the compiler provides their default
  implementation.

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

### Implementation of the move constructor

In the implementation of the move constructor, in the initilization
list of the base and member objects, the initializing arguments should
be rvalues, so that the compiler can choose the move constructors for
the base and member objects.  To this end we can use the `std::move`
function, as shown in the example below.

{% highlight c++ %}
{% include_relative move-ctor.cc %}
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

### Implementation of the move assignment operator

In the implementation of the move assignment operator, the argument
expressions for the assignment operators of the base and member
objects should be rvalues, so that the compiler can choose the move
assignment operators for the base and member objects.  To this end we
can use the `std::move` function, as shown in the example below.

{% highlight c++ %}
{% include_relative move-assign.cc %}
{% endhighlight %}

## Overload resolution

Wybór przeciążenia (kopiującego lub przenoszącego) konstruktora czy
operatora przypisania zależy od kategorii wartości wyrażenia, które
jest argumentem wywołania i także od dostępności przeciążenia.

Jeżeli dostępne są oba przeciążenia, kompilator wybierze przeciążenie
kopiujące dla l-wartości i przeciążenie przenoszące dla r-wartości.

Jeżeli dostępne jest tylko przeciążenie kopiujące, kompilator wybierze
przeciążenie kopiujące także dla r-wartości, bo stała l-referencja
może wskazać r-wartość.

Jeżeli dostępne jest tylko przeciążenie przenoszące, kompilator zgłosi
błąd dla l-wartości, bo r-referencja nie może wskazać l-wartości.

## Special member functions

A compiler can generate default implementations of the special member
functions.  Special member functions are:

* the default constructor,

* the copy constructor, the copy assignment operator,

* the move constructor, the move assignment operator,

* the destructor.

The default implementation of the move constructor and the move
assignment operator will not be implicitly included by a compiler, if
the copy constructor, the copy assignment operator or the destructor
were defined by a programmer.

The default implementation of the copy constructor and the copy
assignment operator will be defined as deleted, if the move
constructor or the move assignment operator was defined (which
includes as default or deleted too).

A programmer can explicitely request the default implementation of a
special member function with `= default`, like this:

{% highlight c++ %}
{% include_relative default.cc %}
{% endhighlight %}

## Deleting special member functions

  Możemy usunąć składowe przez zadeklarowanie ich jako \code{delete}:

  \lstinputlisting{delete.cc}

  W ten sposób usunęliśmy konstruktor kopiujący i kopiujący operator
  przypisania, jak robi się to w typach danych tylko do przenoszenia
  (ang.~move-only type), którego przykładem jest
  \code{std::unique_ptr}.

# Implications of the move semantics

## Initialization of function parameters

  Parametr funkcji inicjalizowany jest na podstawie wyrażenia, które
  jest argumentem wywołania funkcji.  Dla parametru typu
  niereferencyjnego będzie wywołany:

  \begin{itemize}
    \item \red{konstruktor kopiujący}, jeżeli argumentem jest
      \red{l-wartość},
    \item \red{konstruktor przenoszący}, jeżeli argumentem jest
      \red{r-wartość}.
  \end{itemize}

  Jeżeli konstruktor kopiujący nie jest dostępny, a argumentem jest
  l-wartość, to będzie zgłoszony błąd kompilacji.

  Jeżeli konstruktor przenoszący nie jest dostępny, a argumentem jest
  r-wartość, to będzie użyty konstruktor kopiujący.

## Returning by value from a function

  Jeżeli wartość zwracana przez funkcję nie jest typu referencyjnego,
  to mówimy, że funkcja zwraca wynik przez wartość.  Na przykład:

  {\scriptsize\lstinputlisting[]{return.cc}}

  Od C++03 zezwala się na optymalizację wartości powrotu (ang.~return
  value optimization, RVO), której celem jest uniknięcie wywołania
  konstruktora (ang.~constructor elision) kopiującego lub
  przenoszącego przy zwracaniu wartości funkcji.

  Jeżeli nie można zastosować RVO, to C++11 wymaga, aby kompilator
  stosował niejawne przeniesienie (ang.~implicit move) zwracanego
  obiektu lokalnego.

### Implicit moves

  Przy zwracaniu przez wartość niestatycznego obiektu lokalnego $t$
  funkcji, jeżeli nie można zastosować RVO, lub zwracaniu parametru
  $t$ funkcji, wyrażenie instrukcji \code{return} niejawnie traktowane
  jest jako r-wartość, żeby pozwolić na przeniesienie zwracanego
  obiektu.  Wtedy instrukcja \code{return t;} działa jak \code{return
    std::move(t);}.

  Standard C++ pozwala na jawne przeniesienie tylko w przypadku
  \code{return t;}.  Inne, bardziej złożone, wyrażenia nie są
  uwzględnione.

  Nie powinniśmy sami używać funkcji \code{std::move} dla argumentu
  instrukcji \code{return}, bo wtedy wymusimy przenoszenie obiektu
  nawet w sytuacjach, kiedy może być zastosowana RVO.

#### Example 1

  Kiedy zwracany jest parametr funkcji.  Parametr funkcji jest
  alokowany i inicjowany w osobnym miejscu na stosie, a nie w miejscu
  zaalokowanym dla zwracanej wartości.

  \vfill

  {\scriptsize\lstinputlisting[]{no_rvo_2.cc}}

  \vfill

  Ponieważ wyrażeniem instrukcji \code{return} jest nazwa parametru
  \code{t} funkcji, to obiekt \code{t} zostanie niejawnie
  przeniesiony.

#### Example 2

  Kiedy zwracany obiekt jest obiektem bazowym lokalnego obiektu.
  Lokalny obiekt był za duży, żeby można było go stworzyć w miejscu
  dla zwracanej wartości.

  {\scriptsize\lstinputlisting[]{no_rvo_4.cc}}

  Tylko obiekt bazowy zmiennej lokalnej \code{b} zostanie niejawnie
  przeniesiony (ang.~object slicing) do zwracanego obiektu, bo i tak
  \code{b} będzie zniszczony.  Jeżeli obiekt \code{b} byłby statyczny,
  to obiekt bazowy zostałby skopiowany.
  
## The `std::swap` function

  Funkcja \code{std::swap} była jednym z powodów, dla którego zaczęto
  pracować nad semantyką przeniesienia w języku C++.  Ta funkcja
  pokazała, że wydajniej jest przenosić obiekty niż je kopiować.

  Funkcja \code{std::swap(x, y)} przyjmuje przez referencję dwa
  obiekty \code{x} i \code{y}, których wartości zamienia.  Przykładowa
  implementacja:

  {\scriptsize\lstinputlisting{swap-impl.cc}}

# Conclusion

  \begin{itemize}
  \item Przenoszenie obiektów wprowadzono w C++11.
  \item Przenoszenie obiektów pozwala na uniknięcie kopiowania.
  \item Tylko obiekty r-wartości mogą być przenoszone.
  \item Kompilator może dołączyć domyślne przeciążenia przenoszące.
  \item Wybór przeciążenia (kopiującego lub przenoszącego)
    konstruktora czy operatora przypisania zależy od kategorii
    wartości wyrażenia, które jest argumentem wywołania i także od
    dostępności przeciążenia.
  \end{itemize}

<!-- LocalWords:  -->
