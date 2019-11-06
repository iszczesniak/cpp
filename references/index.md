---
title: References
---

# Introduction

There are the most important facts about references:

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
*points to*, though points to is used when talking about pointers.
  
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

# Details

## Reference types

* `T &` - lvalue reference: binds to data that we can modify

referencja
    typu \red{l-wartość}: służy do wskazania obiektu, który możemy
    modyfikować, ale \red{nie przenosić}, zakładając, że ten obiekt
    będzie później używany,

  \item \code{const T &} - referencja stała typu \red{l-wartość}:
    służy do wskazania obiektu, którego nie możemy modyfikować ani
    przenosić,

  \item \code{T &&} - referencja typu \red{r-wartość}: służy do
    wskazania obiektu, który możemy modifikować i \red{przenosić},
    zakładając, że ten obiekt wkrótce zostanie zniszczony.
  \end{itemize}

  \vspace{0.25 cm}

  Nazwy skrócone:
  \begin{itemize}
  \item \red{l-referencja} to referencja typu l-wartość,
  \item \red{r-referencja} to referencja typy r-wartość.
  \end{itemize}

# Terminy l-wartość i r-wartość w nazwie typu

  \item Terminy l-wartość i r-wartość określają kategorię wartości
    wyrażenia:

    \begin{itemize}

    \item wyrażenie \code{"1"} ma kategorię l-wartość,

    \item wyrażenie \code{1} ma kategorię r-wartość.

    \end{itemize}

  \item Ale słowa te mogą też definiować typ referencji:

    \begin{itemize}

    \item \code{int &x;} - wyrażenie \code{x} ma typ ``referencja typu
      l-wartość'' i kategorię l-wartość,

    \item \code{int &&x;} - wyrażenie \code{x} ma typ ``referencja
      typu r-wartość'' i kategorię l-wartość.

    \end{itemize}

  \end{itemize}

  \vspace{0.5 cm}
  
  \red{TERAZ ROZUMIEM: Even if the variable's type is rvalue
    reference, the expression consisting of its name is an lvalue
    expression.}
  
\end{frame}

# Lvalue reference

  L-referencja wskazuje l-wartość, a nie może wskazać r-wartości.

  \vspace{0.5 cm}
  
  L-referencję definiujemy z użyciem \code{&}: \code{T &}

  \vspace{0.5 cm}

  Jeżeli mamy funkcję \code{int &foo()}, to wyrażenie \code{foo()}
  jest \red{l-wartością}, dlatego tak można zainicjalizować
  l-referencję: \code{int &z = foo();}

\subsection{L-referencja - przykłady}

%************************************************************************

\subsection{Stała l-referencja do r-wartości}

\begin{frame}

  \frametitle{Stała l-referencja do r-wartości}

  \red{To nie jest r-referencja!}

  \vspace{0.5cm}

  Zasada wprowadzona w C++98, która obowiązuje do dzisiaj:
  \begin{itemize}
  \item stała l-referencja może wskazywać l-wartość lub \red{r-wartość}.
  \end{itemize}

  \vspace{0.5cm}

  Po angielsku: \red{const lvalue reference to rvalue}

  \vspace{0.5cm}

  Kwalifikator \code{const} odnosi się do wskazywanego obiektu (to
  obiekt jest stały), a nie referencja, bo referencji i tak nie można
  zmienić.

\end{frame}

%************************************************************************

\subsection{Stała l-referencja do r-wartości - przykłady}

\begin{frame}

  \frametitle{Stała l-referencja do r-wartości - przykłady}

  \begin{itemize}
  \item \code{int \&a = 1;} nie będzie się kompilować, bo 1 jest
    r-wartością i chcemy ją wskazać niestałą l-referencją,
  \item \code{const int \&b = 1;} będzie się kompilować, bo r-wartość
    wskazujemy stałą l-referencją,
  \item \code{int foo();} - deklaracja funkcji
  \item \code{const int &c = foo();} - OK!
  \item \code{const int *p = &foo();} - błąd!
  \item \code{const int *p = &c;} - OK!
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{R-referencja}

\begin{frame}

  \frametitle{R-referencja}

  R-referencja wskazuje r-wartość, a nie może wskazać l-wartości.

  \vspace{0.5 cm}
  
  R-referencję definiujemy z użyciem \code{&&}: \code{T &&}

  \vspace{0.5 cm}

  To nowość wprowadzona w C++11, żeby umożliwić:

  \begin{itemize}
  \item mechanizm przenoszenia obiektów,
  \item doskonałe przekazywanie argumentów funkcji.
  \end{itemize}

  \vspace{0.5cm}

\end{frame}

%************************************************************************

\subsection{R-referencja - przykłady}

\begin{frame}[fragile]

  \frametitle{R-referencja - przykłady}

\begin{lstlisting}
int x = 1;

// BŁĄD: brak inicjalizacji.
int &&a;

// BŁĄD: nie może wskazać l-wartości.
int &&z = x;

// OK: wskazujemy r-wartość.
int &&z = 1;
\end{lstlisting}
  
\end{frame}

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

%************************************************************************

\subsection{Przeciążanie funkcji a referencje}

\begin{frame}[fragile]

  \frametitle{Przeciążanie funkcji a referencje}

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

\end{frame}

%************************************************************************

\subsection{Wiązanie obiektu tymczasowego przez referencję}

\begin{frame}[fragile]

  \frametitle{Wiązanie obiektu tymczasowego przez referencję}

  Jeżeli obiekt tymczasowy jest wskazywany przez referencję, to jest
  on niszczony wtedy, kiedy referencja wychodzi poza \red{zakres}
  (ang.~scope).  Inaczej obiekt byłby niszczony po opracowaniu
  wyrażenia.

  \vspace{0.25 cm}

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
