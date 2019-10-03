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
lvalue.  There are no rvalues in C!

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

# The lvalue category

It's hard to find a short and succinct definition in the C++ standard,
because the meaning of the lvalue category is spread all over the
standard.  But the following is a good description of the lvalue
category.

If `&<expr>` compiles, then `<expr>` is an lvalue.  That is, if we can
take the address of an expression, then this expression is an lvalue.

The examples of lvalues are:

* the name of a variable: `x`
* the name of a function: `foo`
* a string literal: `"Hello World!"`
* the results of the prefix incrementation: `++i`

# The rvalue category

An expression is an rvalue, if it's not an lvalue.  We can't take the
address of an rvalue.

The examples of rvalues are:

* a numeric literal: `1`
* a temporary object: `std::string("Hello World!")`
* the result of the postfix incrementation: `i++`
* a function call: `foo()`, if `int foo();`

# From lvalue to rvalue

The C++ standard defines this *standard conversion*: an lvalue can be
implicityly (i.e., without a programmer explicityly writing it)
converted to an rvalue if needed.

For instance, the `+` operator for an integer type (e.g., `int`)
requires rvalues as its operands.  In the following example the `+`
operator expects rvalues, and so the lvalues `x` and `y` are converted
to rvalues.

{% highlight c++ %}
{% include_relative conversion.cc %}
{% endhighlight %}

There is no standard or implicit conversion from an rvalue to an
lvalue, but a programmer can still explicitly convert an rvalue to an
lvalue.

%************************************************************************

\subsection{Przykład: operator ++}

\begin{frame}

  \frametitle{Przykład: operator \code{++}}

  Operator inkrementacji (\code{++}) jako argumentu wymaga
  \red{l-wartości}.  Wyrażenie z operatorem \code{++} jest:

  \begin{itemize}
  \item \red{l-wartością} dla operatora prefixowego, np.~\code{++i},
    bo operator wykonuje działanie na obiekcie \code{i}, a potem
    zwraca l-referencję na ten obiekt,
  \item \red{r-wartością} dla operatora sufixowego, np.~\code{i++}, bo
    operator tworzy kopię obiektu \code{i}, wykonuje działanie na
    obiekcie \code{i}, a potem zwraca stworzoną kopię obiektu.
  \end{itemize}

  Dlatego \code{++++i} kompiluje się, a \code{i++++} już nie.
  
\end{frame}

%************************************************************************

\subsection{Obiekty tymczasowe}

\begin{frame}

  \frametitle{Obiekty tymczasowe}

  Obiekt tymczasowy (ang.~temporary) jest tworzony przy:

  \begin{itemize}
    \item opracowywaniu wyrażenia: \code{1 + 2, string("T") + "4";}
    \item przekazywaniu argumentu wywołania funkcji:\\
      \code{void foo(const A \&);}\\
      \code{foo(A());}
    \item zwracaniu wartości funkcji: \code{string x = foo();}
    \item rzucaniu wyjątku: \code{throw A();}
  \end{itemize}

  \vspace{0.25cm}

  Obiekty tymczasowe w C++98 były zawsze kopiowane.

  \vspace{0.25cm}

  Obiekty tymczasowe w C++11 mogą być \emph{przenoszone}, bo
  wyrażenia, w których są tworzone (np.~jako argument wywołania
  funkcji) są r-wartością, którą można wskazać r-referencją.

\end{frame}

%************************************************************************

\subsection{Funkcje a kategorie wartości wyrażeń}

\begin{frame}

  \frametitle{Funkcje a kategorie wartości wyrażeń}

  Funkcja o nazwie \code{foo} może być użyta w wyrażeniu na dwa
  sposoby:

  \begin{itemize}
  \item użycie tylko nazwy:
    \begin{itemize}
    \item przykładowe wyrażenie: \code{foo},
    \item w tym przypadku \code{foo} jest l-wartością, bo na nazwę,
    \item możemy pobrać adres l-wartości, więc \code{&foo} jest OK,
    \end{itemize}
  \item wywołanie funkcji:
    \begin{itemize}
    \item przykładowe wyrażenie: \code{foo(argumenty)},
    \item kategoria wartości wyrażenia wywołania funkcji zależy od
      typu wartości zwracanej przez funkcję:
      \begin{itemize}
      \item jeżeli typem jest l-referencja, to wyrażenie jest
        l-wartością, np.: jeżeli \code{int &foo();}, to \code{foo()}
        jest l-wartością,
      \item jeżeli typ nie jest referencyjny, to wyrażenie jest
        r-wartością: np.: jeżeli \code{int foo();}, to \code{foo()}
        jest r-wartością.
      \end{itemize}
    \end{itemize}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Typy niepełne a kategorie wartości wyrażeń}

\begin{frame}[fragile]

  \frametitle{Typy niepełne a kategorie wartości wyrażeń}

  Jeżeli typ nie został w pełni zdefiniowany, bo został jedynie
  zadeklarowany, albo częściowo zdefiniowany jako klasa abstrakcyjna,
  to typ taki nazywamy \red{typem niepełnym} (ang.~incomplete type).

  \vspace{0.25 cm}

  Wyrażenia typu niepełnego mogą mieć tylko kategorię l-wartość.

  \vspace{0.25 cm}

  {\scriptsize
  \lstinputlisting[]{incomplete.cc}
  }

\end{frame}

%************************************************************************

# Conclusion

  \item Kategoria wartości odnosi się do wyrażenia, a nie wartości
    pewnego typu (np.~klasy A albo typu \code{int}).

  \item Wartość pewnego typu (np.~klasy A albo typu \code{int}) nie ma
    kategorii wartości.

  \item Kategoria wartości wyrażenia określa, jakie operacje można
    dalej wykonać na wyrażeniu.

  \item Każde wyrażenie jest l-wartością albo r-wartością.

\end{frame}
