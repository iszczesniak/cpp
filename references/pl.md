---
title: Referencje
---

# Wprowadzenie

Najważniejsze fakty o referencjach:

* Referencja jest aliasem (nazwą) danej (zmiennej, obiektu, czy
  obiektu tymczasowego),

* Mając referencję do obiektu, możemy uzyskać dostęp do składowych pól
  i funkcji z użyciem operatora dostępu (czyli `object.member`, jak w
  przypadku nazwy zmiennej), a nie z użyciem operatora dostępu przez
  wskaźnik (czyli `pointer->member`, jak w przypadku wskaźnika).

* Referencja musi być zaincjalizowana, więc nie ma referencji pustych,
  które nie zostały zainicjalizowane.  Wskaźnik może być pusty (czyli
  `nullptr`).

* W przeciwieństwie do wskaźnika, referencji nie można zmienić, żeby
  była aliasem innej danej.

* Referencja może być przechowywana w `std::pair` i `std::tuple`, ale
  nie w kontenerze czy tablicy.

Główne zastosowania referencji:

* przekazywanie argumentu do funkcji przez referencję,

* zwracanie wartości z funkcji przez referencję,

* użycie danych przez referencję w polach składowych obiektów.

**Referencja jest inicjalizowana na podstawie wyrażenia
inicjalizującego**.  Mając daną, która jest wartością wyrażenia
inicjalizującego, możemy równoważnie powiedzieć, że referencja:

* **odnosi się** (ang. refers to) do danej,

* **wiąże się** (ang. binds to) z daną,

* **nazywa** (ang. names) daną.

Referencja odnosi się do wartości wyrażenia kategorii l-wartość, albo
kategorii r-wartość, ale w skrócie możemy powiedzieć, że wiąże się z
l-wartością albo r-wartością (ang. a reference binds to an lvalue).

Referencje języka C++ nie mają odpowiednika w języku Java czy C#: w
C++ referencja może nie istnieć w czasie uruchomienia, bo została
**wyoptymalizowana** w czasie kompilacji.

W Javie czy C# referencja jest wskaźnikiem o semantyce współdzielonej
własności: referencje mogą być kopiowane, a dana będzie tak długo
istnieć, jak istnieje przynajmniej jeden taki wskaźnik.  W tych języka
wskaźnik (i to nie taki zwykły jak w C, tylko implementujący
współdzielenie obiektu) zawsze istnieje w czasie uruchomienia.

Poniższy przykład pokazuje wyoptymalizowanie referencji w czasie
kompilacji.  Poniższe dwa programy robią to samo, ale w drugim używamy
referencji, które są wyoptymalizowane.

Zapiszmy ten plik jako `test1.cc`:

{% highlight c++ %}
{% include_relative test1.cc %}
{% endhighlight %}

Zapiszmy ten plik jako `test2.cc`:

{% highlight c++ %}
{% include_relative test2.cc %}
{% endhighlight %}

Skompilujmy je do asemblera:

`g++ -S -O3 test1.cc test2.cc`

Mamy teraz dwa pliki `test1.s` i `test2.s`.  Spójrzmy na pierwszy z
nich:

`c++filt < test1.s | less`

Porównajmy je, żeby się przekonać, że są takie same (czyli że nie ma
śladu po referencji):

`diff test1.s test2.s`

# Typy referencyjne

Są trzy typy referencji:

* **l-referencja** typu `T &`: odnosi się do danej, którą możemy
  zmieniać, ale nie przenosić (ang. move), bo będzie może ta dana
  potem potrzebna w jej obecnym miejscu,

* **referencja stała** typu `const T &`: odnosi się do danej, której
  nie możemy zmieniać, ani przenosić,

* **r-referencja** typu `T &&`: odnosi się do danej, którą możemy
  zmieniać i przenosić, bo wkrótce będzie zniszczona.

L-referencja jest też nazywana referencją l-wartości, albo referencją
do l-wartości.  R-referencja jest też nazywana referencją r-wartości,
albo referencją do r-wartości.

## Terminy l-wartość i r-wartość w nazwach typów

Wyrażenia nazywamy l-wartością lub r-wartością, np.:

* `"1"` jest l-wartością,

* `1` jest r-wartością.

Te terminy także są używane w nazwach typów, co jest trochę mylące:

* `int &x = <expr>;` - wyrażenie `x` jest referencją l-wartości
  (ang. lvalue reference) i kategorii l-wartość.

* `int &&x = <expr>;` - wyrażenie `x` jest referencją r-wartości
  (ang. rvalue reference) i kategorii l-wartość.

Teraz rozumiem to zdanie z <http://cppreference.com>:

> Nawet jeżeli typem zmiennej jest referencja typu r-wartość
> (r-referencja), to wyrażenie składające się z nazwy tej zmiennej
> jest l-wartością.

## Lvalue reference

An lvalue reference can bind to an lvalue, but not to an rvalue.

We define an lvalue reference like this:

`T &name = <expr>;`

Reference `name` binds to data of type T.  `&` is called the lvalue
reference declarator.  The reference is initialized with expression
`<expr>`.

Here are some examples:

{% highlight c++ %}
{% include_relative lref.cc %}
{% endhighlight %}

Here are some examples for containers and arrays:

{% highlight c++ %}
{% include_relative containers.cc %}
{% endhighlight %}

Here are some examples for `std::pair` and `std::tuple`:

{% highlight c++ %}
{% include_relative quasi.cc %}
{% endhighlight %}

## Const reference

*A const reference can bind not only to an lvalue, but to an *rvalue**
*too.* This rule was introduced in C++98 to allow for binding a
*function parameter reference to a temporary.

We define a const reference like this:

`const T &name = <expr>;`

This is exactly an lvalue reference that binds to the const data of
type `T`, i.e., the const qualifier refers to the type of data the
reference binds to.  The reference itself is not really const, because
we can't change what the reference is bound to anyway.  Nonetheless,
it's called the const reference for short; no need to say it's an
lvalue reference to const data.

Here are some examples:

{% highlight c++ %}
{% include_relative cref.cc %}
{% endhighlight %}

## Rvalue reference

An rvalue reference can bind to an rvalue, but not to an lvalue.

We define an rvalue reference like this:

`T &&name = <expr>;`

`&&` is called the rvalue reference declarator.

The rvalue reference was introduced in C++11 to enable:

* the move semantics,

* the perfect forwarding of function arguments.

Here are some examples:

{% highlight c++ %}
{% include_relative rref.cc %}
{% endhighlight %}

## A reference cannot rebind

Every reference (not only the const reference) cannot rebind to a new
expression.  A reference can only be initialized, i.e., bound to an
expression.  Such rebinding would be required in the assignment
operator of a class-type, which has a reference member field, as in
this example:

{% highlight c++ %}
{% include_relative members.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative overloading.cc %}
{% endhighlight %}

## Rvalue reference to an lvalue

We can explicitely get an rvalue reference to an lvalue with
`static_cast<T &&>(<expr>)`, where `<expr>` can be an lvalue or an
rvalue.  This is, however, a bit wordy, since we have to type in the
type `T`.

It's easier to get an rvalue reference with `std::move(<expr>)`, where
`<expr>` can be an lvalue or an rvalue.  `std::move` is a function
template: a compiler will deduce the type `T` based on `<expr>`, so we
don't have to type it in.  That function uses `static_cast<T
&&>(<expr>)`.

Here's an example:

{% highlight c++ %}
{% include_relative move.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative tmp.cc %}
{% endhighlight %}

We can even create a temporary, and make a member reference bind to
it.  The temporary will be destroyed, when the object is destroyed:

{% highlight c++ %}
{% include_relative tmp2.cc %}
{% endhighlight %}

# Conclusion

* A reference gives us a way to refer by name to some data.

* A reference is initialized, and then cannot be changed.

* Three reference types:

  * an lvalue reference, which can bind to an lvalue only,

  * a const reference, which can bind to both an lvalue and rvalue,

  * an rvalue reference, which can bind to an rvalue only.

* A reference extends the lifetime of a temporary it's bound to.

<!-- LocalWords: lvalue lvalues rvalue -->
