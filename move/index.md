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

all of which boil down to:

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

In the example below, we define the copy constructor and the copy
assignment operator, and see how they work.

{% highlight c++ %}
{% include_relative copy.cc %}
{% endhighlight %}

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

%************************************************************************

\subsection{Konstruktor: kopiujący i przenoszący}

\begin{frame}[fragile]

  \frametitle{Konstruktor: kopiujący i przenoszący}

  \lstinputlisting[]{constructors.cc}

\end{frame}

%************************************************************************

\subsection{Operator przypisania: kopiujący i przenoszący}

\begin{frame}[fragile]

  \frametitle{Operator przypisania: kopiujący i przenoszący}

  \lstinputlisting[]{operators.cc}

\end{frame}

%************************************************************************

\subsection{Przenoszący operator przypisania: zwracany typ}

\begin{frame}[fragile]

  \frametitle{Przenoszący operator przypisania: zwracany typ}

  Przenoszący operator przypisania powinien zwracać l-referencję, a
  nie r-referencję, ponieważ wyrażenie \code{a = b = T()} powinno
  przenieść obiekt tymczasowy \code{T()} do \code{b}, a następnie
  skopiować obiekt \code{b} do \code{a}.

  \vfill

  Jeżeli operator przypisania zwracałby r-referencję, to wyrażenie
  \code{a = b = T()} przeniosłoby obiekty tymczasowy \code{T()} do
  \code{b}, a następnie obiekt \code{b} zostałby przeniesiony do
  \code{a}.

  \vfill

  Ciekawostka: ponieważ przenoszący operator przypisania zwraca
  l-referencję, to jego wynikiem możemy zainicjalizować l-referencję:
  \code{T &l = T() = T();}, mimo że \code{T &l = T();} oczywiście się
  nie kompiluje.

\end{frame}

%************************************************************************

## Overload resolution

Wybór przeciążenia (kopiującego lub przenoszącego) konstruktora czy
  operatora przypisania zależy od kategorii wartości wyrażenia, które
  jest argumentem wywołania i także od dostępności przeciążenia.

  Jeżeli dostępne są oba przeciążenia, kompilator wybierze
  przeciążenie kopiujące dla l-wartości i przeciążenie przenoszące dla
  r-wartości.


  Jeżeli dostępne jest tylko przeciążenie kopiujące, kompilator
  wybierze przeciążenie kopiujące także dla r-wartości, bo stała
  l-referencja może wskazać r-wartość.

  Jeżeli dostępne jest tylko przeciążenie przenoszące, kompilator
  zgłosi błąd dla l-wartości, bo r-referencja nie może wskazać
  l-wartości.

%************************************************************************

Special member functions are:

* the default constructor,

* the copy constructor, the copy assignment operator,

* the move constructor, the move assignment operator,

* the destructor.

\subsection{Domyślne implementacje składowych specjalnych}

\begin{frame}

  \frametitle{Domyślne implementacje składowych specjalnych}

  Kompilator dołączy domyślne implementacje:

  \begin{itemize}
  \item konstruktora: kopiującego i przenoszącego,
  \item operatora przypisania: kopiującego i przenoszącego,
  \item destruktora,
  \end{itemize}

  jeżeli programista nie dostarczył żadnej z nich.  W przeciwnym razie
  kompilator ich nie dołączy, ale możemy jakąś jawnie dołączyć:

  \lstinputlisting{default.cc}

\end{frame}

%************************************************************************

\subsection{Implementacja konstruktora przenoszącego}

\begin{frame}

  \frametitle{Implementacja konstruktora przenoszącego}

  W liście inicjalizacji argumentami konstruktorów obiektów bazowych i
  składowych powinny być r-wartości, żeby zostały wybrane konstruktory
  przenoszące obiektów bazowych i składowych, dlatego używamy funkcji
  \code{std::move}.

  {\footnotesize\lstinputlisting{move-ctor.cc}}
  
\end{frame}

%************************************************************************

\subsection{Implementacja przenoszącego operatora przypisania}

\begin{frame}

  \frametitle{Implementacja przenoszącego operatora przypisania}

  Żeby kompilator wybrał przenoszące (a nie kopiujące) operatory
  przypisania (jeżeli istnieją) dla obiektów bazowych i składowych,
  używamy funkcji \code{std::move}.

  {\scriptsize\lstinputlisting{move-assign.cc}}
  
\end{frame}

%************************************************************************

\subsection{Usuwanie składowych}

\begin{frame}

  \frametitle{Usuwanie składowych}

  Możemy usunąć składowe przez zadeklarowanie ich jako \code{delete}:

  \lstinputlisting{delete.cc}

  W ten sposób usunęliśmy konstruktor kopiujący i kopiujący operator
  przypisania, jak robi się to w typach danych tylko do przenoszenia
  (ang.~move-only type), którego przykładem jest
  \code{std::unique_ptr}.

\end{frame}

%************************************************************************

\subsection{Inicjalizacja parametrów funkcji}

\begin{frame}[fragile]

  \frametitle{Inicjalizacja parametrów funkcji}

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

\end{frame}

%************************************************************************

\subsection{Zwracanie wyniku funkcji przez wartość}

\begin{frame}[fragile]

  \frametitle{Zwracanie wyniku funkcji przez wartość}

  Jeżeli wartość zwracana przez funkcję nie jest typu referencyjnego,
  to mówimy, że funkcja zwraca wynik przez wartość.  Na przykład:

  \vfill

  {\scriptsize\lstinputlisting[]{return.cc}}

  \vfill

  Od C++03 zezwala się na optymalizację wartości powrotu (ang.~return
  value optimization, RVO), której celem jest uniknięcie wywołania
  konstruktora (ang.~constructor elision) kopiującego lub
  przenoszącego przy zwracaniu wartości funkcji.

  \vfill

  Jeżeli nie można zastosować RVO, to C++11 wymaga, aby kompilator
  stosował niejawne przeniesienie (ang.~implicit move) zwracanego
  obiektu lokalnego.
    
\end{frame}

%************************************************************************

\subsection{Optymalizacja wartości powrotu}

\begin{frame}[fragile]

  \frametitle{Optymalizacja wartości powrotu}

  Miejsce dla zwracanego obiektu jest alokowane na stosie przez kod
  wywołujący funkcję przed wywołaniem funkcji.  Funkcja stworzy obiekt
  w już zaalokowanym miejscu i jeżeli może, to bez wywoływania
  konstruktora kopiującego czy przenoszącego.

  \vfill

  W ten sposób funkcja tworzy obiekt w miejscu, do którego zwracany
  obiekt musiałby być skopiowany albo przeniesiony, gdyby był
  stworzony w miejscu na stosie zaalokowanym przez funkcję.

\end{frame}

%************************************************************************

\subsection{Niejawne przeniesienie}

\begin{frame}[fragile]

  \frametitle{Niejawne przeniesienie}

  Przy zwracaniu przez wartość niestatycznego obiektu lokalnego $t$
  funkcji, jeżeli nie można zastosować RVO, lub zwracaniu parametru
  $t$ funkcji, wyrażenie instrukcji \code{return} niejawnie traktowane
  jest jako r-wartość, żeby pozwolić na przeniesienie zwracanego
  obiektu.  Wtedy instrukcja \code{return t;} działa jak \code{return
    std::move(t);}.

  \hfill

  Standard C++ pozwala na jawne przeniesienie tylko w przypadku
  \code{return t;}.  Inne, bardziej złożone, wyrażenia nie są
  uwzględnione.

  \hfill

  Nie powinniśmy sami używać funkcji \code{std::move} dla argumentu
  instrukcji \code{return}, bo wtedy wymusimy przenoszenie obiektu
  nawet w sytuacjach, kiedy może być zastosowana RVO.

\end{frame}

%************************************************************************

\subsection{Kiedy RVO nie działa: przypadek 1}

\begin{frame}[fragile]

  \frametitle{Kiedy RVO nie działa: przypadek 1}

  Kiedy w momencie tworzenia obiektów lokalnych funkcji nie wiadomo,
  który z nich zostanie zwrócony, wtedy RVO nie może być zastosowana.

  \vfill

  {\scriptsize\lstinputlisting[]{no_rvo_1.cc}}

  \vfill

  Zwracana wartość będzie kopiowana, a nie przenoszona niejawnie, bo
  wyrażeniem instrukcji \code{return} nie jest nazwa zmiennej, a
  operator warunkowy.

\end{frame}

%************************************************************************

\subsection{Kiedy RVO nie działa: przypadek 2}

\begin{frame}[fragile]

  \frametitle{Kiedy RVO nie działa: przypadek 2}

  Kiedy zwracany jest parametr funkcji.  Parametr funkcji jest
  alokowany i inicjowany w osobnym miejscu na stosie, a nie w miejscu
  zaalokowanym dla zwracanej wartości.

  \vfill

  {\scriptsize\lstinputlisting[]{no_rvo_2.cc}}

  \vfill

  Ponieważ wyrażeniem instrukcji \code{return} jest nazwa parametru
  \code{t} funkcji, to obiekt \code{t} zostanie niejawnie
  przeniesiony.

\end{frame}

%************************************************************************

\subsection{Kiedy RVO nie działa: przypadek 3}

\begin{frame}[fragile]

  \frametitle{Kiedy RVO nie działa: przypadek 3}

  Kiedy funkcja zwraca obiekt globalny albo statyczny, bo one nie są
  alokowane na stosie, gdzie jest alokowane miejsce dla wracanego
  obiektu.

  \vfill

  {\scriptsize\lstinputlisting[]{no_rvo_3.cc}}

  Ponieważ wyrażeniem instrukcji \code{return} jest nazwa statycznej
  zmiennej lokalnej \code{t} funkcji, to obiekt \code{t} nie zostanie
  niejawnie przeniesiony.  Tego obiektu \code{t} będziemy potrzebować
  przy następnym wywołaniu funkcji, skoro jest statyczny.

\end{frame}

%************************************************************************

\subsection{Kiedy RVO nie działa: przypadek 4}

\begin{frame}[fragile]

  \frametitle{Kiedy RVO nie działa: przypadek 4}

  Kiedy zwracany obiekt jest obiektem bazowym lokalnego obiektu.
  Lokalny obiekt był za duży, żeby można było go stworzyć w miejscu
  dla zwracanej wartości.

  \vfill

  {\scriptsize\lstinputlisting[]{no_rvo_4.cc}}

  \vfill

  Tylko obiekt bazowy zmiennej lokalnej \code{b} zostanie niejawnie
  przeniesiony (ang.~object slicing) do zwracanego obiektu, bo i tak
  \code{b} będzie zniszczony.  Jeżeli obiekt \code{b} byłby statyczny,
  to obiekt bazowy zostałby skopiowany.
  
\end{frame}

%************************************************************************

\subsection{Funkcja std::swap}

\begin{frame}

  \frametitle{Funkcja \code{std::swap}}

  Funkcja \code{std::swap} była jednym z powodów, dla którego zaczęto
  pracować nad semantyką przeniesienia w języku C++.  Ta funkcja
  pokazała, że wydajniej jest przenosić obiekty niż je kopiować.

  \vfill

  Funkcja \code{std::swap(x, y)} przyjmuje przez referencję dwa
  obiekty \code{x} i \code{y}, których wartości zamienia.  Przykładowa
  implementacja:

  \vfill

  {\scriptsize\lstinputlisting{swap-impl.cc}}

\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

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

  \vspace{0.5cm}

\end{frame}

<!-- LocalWords: enum  sigsegv endhighlight heisenbugs -->
<!-- LocalWords: deallocates defragmentation manyfold args -->
<!-- LocalWords: EAX RDI RVO SIGSEGV -->
