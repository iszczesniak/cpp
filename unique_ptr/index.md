---
title: std::unique_ptr
---

# Introduction

Pointers are indispensible.  Pointers:

* point to memory locations, usually dynamically-allocated,

* are used in every programming language: C, C++, Java, C#,

* can be used in the form of a reference, e.g., in Java or C#.

The pointer support can be:

* wrapped in a reference, e.g., in Java or C#,

* raw or advanced, as in C++,

* raw only, as in C.

In C++, it's best to avoid the raw pointers, and go for the advanced
pointer support in the form of standard smart pointers.

A reference in Java or C# is a shared pointer with the object member
selection syntax (i.e., `object.member`).  A C++ reference is an
alias, which at compile time will be either optimized out or turned
into a raw pointer.

# Motivation: the problems of raw pointers

While raw pointers are easy to use, their use is very error-prone,
i.e., it's easy to make mistakes.

## The problems

When we have a pointer of type `T *` which points to a
dynamically-allocated memory location, we have these problems:

* **the type problem**: we don't know whether a pointer points to a
  single piece of data or to an array of data,

* **the ownership problem**: we don't know whether *we* or *someone
  else* (i.e., some other programmer who implemented some other part
  of code) should destroy the allocated data,

* **the exception handling problem**: exception handling with raw
  pointers is difficult, arduous, and error-prone.

### The type problem

The new and delete operators come in many versions, most notably:

* the *single version* for allocating a single piece of data,

* the *array version* for allocating an array of data.

If we allocate data with either the single or array version of the new
operator, we should destroy the data with the same version of the
delete operator.  However, the type of the pointer used is the same
for both version, so it's easy to mismatch the versions, which results
in an undefined behaviour.

### The ownership problem

The ownership problem can result in:

* **a memory leak**, when the dynamically-allocated data is never
  destroyed,

* **a dangling pointer**, when we keep using a memory location, but
  the data that used to be there was already destroyed,

* **a double deletion**, when we try to destroy again the data that
    was already destroyed.

### The exception handling problem

If we manage the dynamically-allocated data with raw pointers, the
exception handling becomes a boring and error-prone task, espacially
if the data is complex.  It's doable, but who really wants to do it?

## An example

The example below shows how easily we can run into the type,
ownership, and exception handling problems.  The compiler does not
report problems with this broken code.

{% highlight c++ %}
{% include_relative problems.cc %}
{% endhighlight %}

## The smart pointer solution

The smart pointers in C++ solve:

* the type problem: a smart pointer knows the type of the object, so
  that it can be automatically (i.e., without a programmer requesting
  it explicitely) destroyed in the proper way,

* the ownership problem: a smart pointer automatically manages the
  data: either enforces the exclusive ownership or allows for shared
  management, and takes care of destruction,

* the exception handling problem: a smart pointer is automatically
  destroyed when an exception is handled.

Every flexible language should support raw pointers, because this
low-level functionality is needed to implement high-level
functionality, such as smart pointers.

A programmer should have a choice between the raw pointers (perhaps
for implementing an intricate functionality) and smart pointers (just
for every day use).

In C++, for every day use, a programmer should not resort to the raw
pointers, let alone to the `void *` trickery -- these times are long
gone.

# Smart pointer types

There are three smart pointer types:

* `std::unique_ptr` - usually used instead of a raw pointer,

* `std::shared_ptr` - used to share a managed data,

* `std::weak_ptr` - wskazuje obiekt współdzielony, ale
    nie współdzieli tego obiektu.

  \item \code{std::auto\_ptr} - przestażały, \red{lepiej unikać}


\item Te klasy to opakowania (używane w czasie kompilacji) surowych wskaźników.
  \item Zajmują tyle samo miejsca w pamięci, co surowy wskaźnik.
  \item Tak wydajny pamięciowo i czasowo, jak surowy wskaźnik.
  \item Są odporne na \red{wyjątki}, ale nie na \red{wątki}!
  \item Stosujemy inteligentne wskaźniki zamiast surowych wskaźników.
  \end{itemize}

\end{frame}

%************************************************************************

\section{std::unique\_ptr}

\subsection{Ogólnie o std::unique\_ptr}

\begin{frame}

  \frametitle{Ogólnie o \code{std::unique\_ptr}}

  \begin{itemize}
  \item W większości przypadków: używać zamiast surowych wskaźników.
  \item Jest wyłącznym właścicielem wskazywanego obiektu.
  \item \code{\#include {<}memory{>}}
  \item \code{std::unique\_ptr {<}moja\_klasa{>} p;}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{std::unique\_ptr jest właścicielem}

\begin{frame}

  \frametitle{\code{std::unique\_ptr} jest właścicielem}

  \begin{itemize}
  \item Posiada semantykę (znaczenie) wyłącznej własności.
  \item Posiada konstruktor przenoszący, ale nie kopiujący.
  \item Jest \red{wyłącznym właścicielem} wskazywanego obiektu, czyli:
    \begin{itemize}
    \item niszczy obiekt, kiedy sam jest niszczony
      (np.~kiedy wychodzi poza zakres),
    \item niszczy obiekt, zanim będzie wskazywał następny obiekt,
    \item nie da się kopiować, a jedynie przenosić (czyli nie ma dwóch
      \code{std::unique\_ptr} wskazujących ten sam obiekt),
    \item kiedy odda wskazywany obiekt, to sam wskazuje \code{nullptr}.
    \end{itemize}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Przykład użycia std::unique\_ptr}

\begin{frame}

  \frametitle{Przykład użycia \code{std::unique\_ptr}}

  Funkcja zwracająca obiekt użytkownikowi:

  \verbatiminput{example1.cc}

\end{frame}

std::unique_ptr<A> p1; // OK.  Nie wskazuje na nic.
std::unique_ptr<A> p1(new A("A1")); // OK.
p1 = new A("A1'"); // Zabronione!
p1.reset(new A("A2")); // OK, ale usunie "A1".
std::unique_ptr<A> p2(p1); // Błąd! Nie można kopiować.
std::unique_ptr<A> p2 = p1; // Błąd! Nie można kopiować.
p2 = p1; // Błąd! Nie można kopiować.
p2 = std::move(p1); // OK.  Przeniesienie.
p2->foo(); // Wywyłanie A::foo(), jak przez wskaźnik.
(*p2).foo(); // Wywyłanie A::foo(), jak przez wskaźnik.
p1.release(); // p1 już nie ma obiektu, ale go nie usuwa.
p1.get(); // Wartość surowego wskaźnika.

std::deque<std::unique_ptr<A> > c;
c.push_back(std::unique_ptr<A>(new A("C1")));

%************************************************************************

\subsection{std::make\_unique}

\begin{frame}

  \frametitle{std::make\_unique}

  \begin{itemize}
  \item Zdefiniowany dopiero w C++14, a nie w C++11 jak
    \code{unique\_ptr}.
  \item Zamiast pisać tak i użyć typu A dwa razy:\\
    \red{\lstinline|unique_ptr<A> up(A("A1"));|}
  \item Możemy napisać tak i użyć typu A tylko raz:\\
    \red{\lstinline|auto up = make_unique<A>("A1");|}
  \item ZALETA: tworzenie obiektu zarządzanego i zarządzającego odbywa
    się w jedyn kroku, co jest bezpieczne pod względem obsługi
    wyjątków.
  \item FACHOWO: \red{enkapsulacja i lokalizacja alokacji zasobów
    (encapsulation and localization of resource allocation).}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Użycie uniqu\_ptr}

\begin{frame}

  \frametitle{Użycie unique\_ptr}

  \begin{itemize}
  \item Zamiast implementować semantykę przeniesienia, możemy posługiwać się
    wskaźnikiem \code{unique\_ptr} na obiekt, którego kopiowania chcemy
    uniknąć.
  \item Wskaźnik \code{unique\_ptr} implementuje semantykę przeniesienia.
  \item Przeniesienie \code{unique\_ptr} jedynie będzie oznaczać
    skopiowanie surowego wskaźnika, a obiekt docelowy pozostanie
    nietknięty.
  \item Najprostsze rozwiązanie: zostaw klasę A w spokoju, używaj
    \code{unique\_ptr<A>}.
  \item Jednak właściwym rozwiązaniem jest ciągle implementacja
    semantyki przeniesienia dla danej klasy.
  \end{itemize}
  
\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}
    \item Unikać surowych wskaźników!
    \item Używać inteligentnych wskaźników!
    \item Najczęściej potrzebujemy \code{std::unique\_ptr}
    \item \code{std::unique\_ptr} trzeba się nauczyć używać.
    \item Na następnym wykładzie: \code{std::shared\_ptr}
    \item Konwersja z \code{std::unique\_ptr} do \code{std::shared\_ptr}:
      \begin{itemize}
      \item \code{std::shared\_ptr{<}A{>} s = foo();}
      \item \code{std::shared\_ptr{<}A{>} s = std::move(p1);}
      \end{itemize}
  \end{itemize}

\end{frame}

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
