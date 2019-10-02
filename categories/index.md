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

%************************************************************************

\subsection{Kategoria l-wartość w C++}

\begin{frame}

  \frametitle{Kategoria l-wartość w C++}

  Jeżeli kategoria wartości wyrażenia to l-wartość, to można pobrać
  adres, czyli można wykonać: \code{\&(wyrażenie)}.

  \vspace{0.5cm}

  Przykłady l-wartości:

  \begin{itemize}
  \item nazwa zmiennej: \code{x}
  \item nazwa funkcji: \code{foo}
  \item literał ciągu znaków: \code{"Hello World!";}
  \item \code{++i}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Kategoria r-wartość w C++}

\begin{frame}

  \frametitle{Kategoria r-wartość w C++}

  Jeżeli wyrażenie nie jest l-wartością, to jest r-wartością.  Nie
  można pobrać adresu r-wartości.

  \vspace{0.5cm}

  Przykłady r-wartości:

  \begin{itemize}
  \item literał: \code{1}
  \item \code{std::string("Hello World!");}
  \item \code{i++}
  \item wywołanie funkcji: \code{foo()}, jeżeli \code{int foo();}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Konwersja z l-wartości na r-wartość}

\begin{frame}

  \frametitle{Konwersja z l-wartości na r-wartość}

  L-wartość może być poddana standardowej konwersji do r-wartości.

  \vspace{0.5cm}

  Na przykład, operator \code{+} dla typu \code{int} wymaga r-wartości
  jako swoich operandów, dlatego poniższy przykład jest poprawny, bo
  l-wartości, którymi są wyrażenia \code{x} i \code{y}, zostaną
  poddane konwersji do r-wartości.

  \vspace{0.5cm}

  \code{int x, y;}

  \code{x + y;}

  \vspace{0.5cm}

  Nie ma niejawnej konwersji z r-wartości do l-wartości.

\end{frame}

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

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}

  \item Kategoria wartości odnosi się do wyrażenia, a nie wartości
    pewnego typu (np.~klasy A albo typu \code{int}).

  \item Wartość pewnego typu (np.~klasy A albo typu \code{int}) nie ma
    kategorii wartości.

  \item Kategoria wartości wyrażenia określa, jakie operacje można
    dalej wykonać na wyrażeniu.

  \item Każde wyrażenie jest l-wartością albo r-wartością.

  \end{itemize}

\end{frame}
