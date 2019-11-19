---
title: Move semantics
---

# Introduction

The move semantics applies only to the class types, so I'll talk about
the *values of objects*, and not *data*.  An object is an instance of
a class type (i.e., a piece of memory interpreted as a class type).
The state of the object is called the *value*.

The value can be copied when the object is:

* passed by value as an argument to a function,

* returned by value from a function,

* assigned to another object (e.g., a variable, an object in a
  container).

Facts:

* Copying takes time when the value to copy is big.

* Copying is implemented by:

  * the copy constructor (to initialize a new object),

  * the copy assignment operator (to assign to an existing object).

* We copy a value from the *source* object to the *target* object (or
  the source and the target in short).

* The source and the target can be in different memory locations,
  i.e., copying is not limited to objects on the stack or the heap
  only.  For instance, the source can be on the stack, and the target
  in the fixed-size memory for static and global data.

Copying of objects might be necessary or not.  When it's necessary
(e.g., because we need to modify a copy, and leave the original
unchanged), then it's not a problem.

However, copying is a problem when it's not necessary.  Copying an
object is not necessary, when the source of the copy is not needed
after copying.  It's a *performance* problem: the code will work
alright, but it could be faster.

# The move semantics

Cecha języka C++11, która pozwala na \emph{uniknięcie
    kopiowania obiektów} poprzez przenoszenie obiektów.

\item Kopiowanie nie jest potrzebne i może być uniknione, jeżeli
    obiekt źródłowy nie będzie potem potrzebny.

\item Przenoszenie obiektów jest realizowane przez konstruktor
    przenoszący lub przenoszący operator przypisania.

\item Obiekt może być przeniesiony tylko wtedy, jeżeli:

\begin{itemize}
    \item jest użyty w wyrażeniu kategorii r-wartość,
    \item ma zaimplementowaną semantykę przeniesienia.
    \end{itemize}

\item Implementacja semantyki przenoszenia obiektów danej klasy może
    być domyślna (dostarczona przez kompilator) albo dostarczona przez
    programistę.

%************************************************************************

\section{Jak to działa?}

\subsection{Jak to działa?}

\begin{frame}

  \frametitle{Jak to działa?}

  \begin{itemize}
  \item Nic magicznego się nie dzieje!  Obiekty nie są przenoszone
    bit-po-bicie między różnymi miejscami pamięci!
  \item Przenoszenie obiektu polega na przenoszeniu danych z obiektu
    źródłowego do obiektu docelowego.  Obiekt źródłowy i obiekt
    docelowy pozostają w pamięci tam, gdzie były i będą w normalny
    sposób niszczone.
  \item Programista może zaimplementować przenoszenie obiektów danej
    klasy przez zdefiniowanie:
    \begin{itemize}
    \item \red{konstruktora przenoszącego},
    \item \red{przenoszącego operatora przypisania}.
    \end{itemize}
  \item Obiekt, który jest źródłem przeniesienia, po przeniesieniu ma
    być \red{spójny} (bo obiekt będzie potem normalnie niszczony), ale
    jego stan nie musi być \red{zdefiniowany}.
  \end{itemize}

\end{frame}

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

\subsection{Wybór przeciążenia}

\begin{frame}

  \frametitle{Wybór przeciążenia}

  Wybór przeciążenia (kopiującego lub przenoszącego) konstruktora czy
  operatora przypisania zależy od kategorii wartości wyrażenia, które
  jest argumentem wywołania i także od dostępności przeciążenia.

  \vspace{0.25 cm}

  Jeżeli dostępne są oba przeciążenia, kompilator wybierze
  przeciążenie kopiujące dla l-wartości i przeciążenie przenoszące dla
  r-wartości.

  \vspace{0.25 cm}

  Jeżeli dostępne jest tylko przeciążenie kopiujące, kompilator
  wybierze przeciążenie kopiujące także dla r-wartości, bo stała
  l-referencja może wskazać r-wartość.

  \vspace{0.25 cm}

  Jeżeli dostępne jest tylko przeciążenie przenoszące, kompilator
  zgłosi błąd dla l-wartości, bo r-referencja nie może wskazać
  l-wartości.

\end{frame}

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
