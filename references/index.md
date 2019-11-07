---
title: References
---

# Introduction

These are the most important facts about references:

* Reference is an alias (a name) for some data (a variable, an object,
  a temporary).

* When using a reference to an object, we use the object-member
  selection syntax (i.e., `object.member`), and not the object-member
  selection through pointer syntax (i.e., `pointer->member`).

* A reference must be initialized, and so there are no null references
  like there can be null pointers.

* Unlike a pointer, a reference cannot be changed to be an alias for
  some other data.

* A reference can be a member of `std::pair` and `std::tuple`, but not
  of a container or an array.

The main use of references:

* passing an argument to a function by reference,

* returning a result from a function by reference,

* referencing data in an object member field.

We say that a reference *binds to* data, which means something like
*points to*, though "points to" is used when talking about pointers.
  
C++ references are like no references of other languages, because at
run-time they might not exists (that can be optimized out at the
compile-time).

In languages like Java or C#, references are pointers with
shared-ownership semantics (i.e., a reference can be copied, and the
object exists as long as at least one reference exists), and with the
object-member selection syntax.  In these languages references must
exist at run-time.

As an example that references are optimized out at compile-time, there
are two programs below that produce the same output, but in the second
one we use references.  However, at compile-time, the refernces are
gone.

Save this file as out1.cc:

{% highlight c++ %}
{% include_relative out1.cc %}
{% endhighlight %}

Save this file as out2.cc:

{% highlight c++ %}
{% include_relative out2.cc %}
{% endhighlight %}

Now compile with:

`g++ -S -O3 out1.cc out2.cc`

Taka look at one of them:

`c++filt < out1.s | less`

Now there are two files with the assembly code: out1.cc, and out2.cc.
Compare them to see that they are instruction-to-instruction the same:

`diff out1.s out2.s`

# Reference types

There are three reference types:

* `T &` - *an lvalue reference*: binds to data that we can modify, but
  not move (because they still will be needed),

* `const T &` - *a const reference*: binds to data that we neither can
  modify nor move,

* `T &&` - *an rvalue reference*: binds to data that we can both
  modify and move (becasue they soon will not be needed).

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

An lvalue reference can bind to the data of an lvalue, but not of an
rvalue.

We define an lvalue reference like this:

`T &name = <expr>;`

Reference `name` binds to data of type T.  `&` is called the reference
declarator.  The reference is initialized with expression `<expr>`.

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

We define a const reference like this:

`const T &name = <expr>;`

This is exactly an lvalue reference that binds to the const data of
type `T`, i.e., the const qualifier refers to the type of data the
reference binds to.  The reference itself is not really const, because
we can't change what the reference is bound to anyway.  Nonetheless,
it's called the const reference for short; no need to say it's an
lvalue reference to const data.

*A const reference can bind not only to the data of an lvalue, but to
an **rvalue** too.* This rule was introduced in C++98 to allow for
binding a function parameter reference to a temporary.

Here are some examples:

{% highlight c++ %}
{% include_relative cref.cc %}
{% endhighlight %}

## Rvalue reference

R-referencja wskazuje r-wartość, a nie może wskazać l-wartości.

R-referencję definiujemy z użyciem \code{&&}: \code{T &&}

To nowość wprowadzona w C++11, żeby umożliwić:

* mechanizm przenoszenia obiektów,

* doskonałe przekazywanie argumentów funkcji.

Here are some examples:

{% highlight c++ %}
{% include_relative rref.cc %}
{% endhighlight %}

%************************************************************************

\subsection{R-referencja do l-wartości}

\begin{frame}[fragile]

  \frametitle{R-referencja do l-wartości}

  Możemy uzyskać r-referencję do l-wartości z użyciem operatora
  \code{static_cast<T &&>(expr)} lub funkcji \code{std::move(expr)},
  gdzie \code{expr} może być l-wartością albo r-wartością.  Funkcja
  \code{std::move} jest szablonowa i kompilator sam wnioskuje typ
  wyrażenia, którego nie trzeba już podawać, jak dla
  \code{static_cast}.  Na przykład:

  {\tiny\lstinputlisting{move.cc}}

  Funkcji \code{std::move(x)} będziemy używać, aby umożliwić
  przenoszenie obiektu \code{x}, dla którego domyślnie przenoszenie
  nie jest stosowane, ponieważ wyrażenie \code{x} jest l-wartością.

\end{frame}

# Reference type and overload resolution 

  Funkcję można przeciążyć różnymi typami referencyjnymi:

  \begin{enumerate}
  \item \code{void foo(T &);}
  \item \code{void foo(const T &);}
  \item \code{void foo(T &&);}
  \end{enumerate}

  Dla wywołania funkcji \code{foo(expr)}, kompilator wybierze:

  \begin{itemize}
    \item przeciążenie nr 1, jeżeli \code{expr} jest l-wartością typu
      niestałego,
    \item przeciążenie nr 2, jeżeli \code{expr} jest l-wartością typu
      stałego,
    \item przeciążenie nr 3, jeżeli \code{expr} jest r-wartością.
  \end{itemize}

  Stała l-referencja (użyta w przeciążeniu nr 2) może wskazać
  l-wartość typu niestałego lub r-wartość, więc jeżeli nie ma
  przeciążenia nr 1 lub 3, kompilator wybierze przeciążenie nr 2.

# Wiązanie obiektu tymczasowego przez referencję

Jeżeli obiekt tymczasowy jest wskazywany przez referencję, to jest on
niszczony wtedy, kiedy referencja wychodzi poza \red{zakres}
(ang.~scope).  Inaczej obiekt byłby niszczony po opracowaniu
wyrażenia.

\begin{lstlisting}
// Obiekt tymczasowy T() jest niszczony
// wtedy, kiedy t1 wychodzi poza zakres.
const T &t1 = T();

// To samo, ale dla r-referencji.
T &&t2 = T();
\end{lstlisting}

  \vspace{0.25 cm}

  Nazywa się to \red{wiązaniem} obiektu tymczasowego przez referencję.

\end{frame}

# Conclusion

* Referencja to inna nazwa obiektu.

* Referencję trzeba zainicjalizować.

* \item Wartości referencji (wskazywanego obiektu) nie można zmienić.

\item Podstawowe typy referencji:
    \begin{itemize}
    \item l-referencja,
    \item r-referencja.
    \end{itemize}
  \item Niestała l-referencja może wskazać l-wartość, ale nie r-wartość.
  \item Stała l-referencja może wskazywać l-wartość lub r-wartość.
  \item R-referencja może wskazywać r-wartość, ale nie l-wartość.
  \item Stała r-referencja nie ma sensu.
  \item Referencje wiążą obiekty tymczasowe.
  \end{itemize}

\end{frame}

<!-- LocalWords: lvalue lvalues rvalue -->
