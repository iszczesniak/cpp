---
title: Doskonałe przekazywanie argumentów
---

# Wprowadzenie

Argumentem wywołania funkcji może być albo l-wartość, albo r-wartość.
W ciele funkcji, wyrażenie z nazwą parametru funkcji jest zawsze
l-wartością, nawet jeżeli ten parametr jest r-referencją
(zainicjalizowaną r-wartością).  W ten sposób tracimy informację o
kategorii wyrażenia argumentu.

Piszemy funkcję `f`, która wywołuje funkcję `g`.  Argument przekazany
funkcji `f` ma zostać przekazany funkcji `g` bez kopiowania i z
zachowaniem kategorii wartości tego argumentu.  Ten problem nazywamy
*doskonałym przekazywaniem argumentu*.

O kwalifikatorach (const, volatile) i typie parametru funkcji `g` nic
nie wiemy.  Chcemy napisać tylko jedną wersję funkcji `f`, która nie
kopiowałaby argumentu i zachowywała jego kategorię wartości.

{% highlight c++ %}
template<typename T>
void
f(qualifiers_a type_a a)
{
  g(a);
}
{% endhighlight %}

PYTANIE: jakie mają być kwalifikatory `qualifiers_a` i jaki typ
`type_a` funkcji `f`?  Czy kwalifikatorem może być `const`, czy musi
być `const`?  Czy typem ma być `T`, `T &`, czy `T &&`?

ODPOWIEDŹ: można, ale tylko z C++11.  O tym później.

## Motywacja: fabryki obiektów

Funkcje \code{make_unique} i \code{make_shared} są fabrykami obiektów.
Tworzą one obiekty i potrzebują przekazać swoje argumenty do
konstruktora klasy w niezmienionej postaci.

To jest przykład dla dwóch parametrów:

\begin{lstlisting}[language=C++]
template<typename T, typename A1, typename A2>
unique_ptr<T>
make_unique(<kwalifikator> <typ A1> a1,
            <kwalifikator> <typ A2> a2)
{
  return unique_ptr<T>(new T(a1, a2));
}
\end{lstlisting}

\end{frame}

%************************************************************************

\section{Szczegóły}

\subsection{Parametry i argumenty funkcji}

\begin{frame}

  \frametitle{Parametry i argumenty funkcji}

  \begin{itemize}
  \item Parametry i argumenty funkcji to nie to samo!
  \item Parametr to zmienna dostępna w ciele funkcji.
  \item Argument to wyrażenie w wywołaniu funkcji.
  \item Parametry są \red{inicjalizowane} na podstawie argumentów.
  \item \code{foo(int x)} - \code{x} jest parametrem funkcji
  \item \code{foo(a)} - \code{a} jest argumentem wywołania funkcji
  \end{itemize}

  \vspace{0.5cm}

  Argument może być l-wartością albo r-wartością, a parametr zawsze
  jest l-wartością, bo ma nazwę (możemy pobrać jego adres).

\end{frame}

%************************************************************************

\subsection{Możliwe rozwiązania}

\begin{frame}

  \frametitle{Możliwe rozwiązania}

  Możliwe rozwiązania z pominięciem kwalifikatora \code{volatile}.

  \begin{itemize}
  \item przez wartość: \code{T}
  \item przez stałą wartość: \code{const T}
  \item przez referencję typu lvalue: \code{T &}
  \item przez referencję stałą typu lvalue: \code{const T &}
  \item przez referencję typu rvalue: \code{T &&}
  \item przez referencję stałą typu rvalue: \code{const T &&}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Rozwiązanie: przekazywanie przez wartość}

\begin{frame}[fragile]

  \frametitle{Rozwiązanie: przekazywanie przez wartość}

  Chodzi o \code{T} i \code{const T}.  Na przykład dla \code{T}:

\begin{lstlisting}[language=C++]
template<typename T>
void
f(T a)
{
  g(a);
}
\end{lstlisting}

  Gdy wykonamy \code{f(1)}, a funkcja \code{g} będzie pobierać
  argumenty przez referencję, to nie otrzyma referencji na oryginalny
  obiekt, a referencję na parametr funkcji \code{f}, który jest kopią
  oryginalnego obiektu.

  \vspace{0.25 cm}

  \red{TO JEST ZŁE ROZWIĄZANIE!}

\end{frame}

%************************************************************************

\subsection{Pozostałe rozwiązania do rozważenia}

\begin{frame}[fragile]

  \frametitle{Pozostałe rozwiązania do rozważenia}

  Bierzemy pod uwagę wyłącznie rozwiązania z referencjami, ale bez
  \code{const T &&}, bo jest ona bezużyteczna.

  \vspace{0.25 cm}

  Zostają nam trzy przypadki do rozważenia:

  \begin{itemize}
  \item \code{T &}
  \item \code{const T &}
  \item \code{T &&}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Rozwiązanie: T &}

\begin{frame}[fragile]

  \frametitle{Rozwiązanie: \code{T &}}

  Rozwiązanie z \code{T &} wygląda tak:
  
\begin{lstlisting}[language=C++]
template<typename T>
void
f(T &a)
{
  g(a);
}
\end{lstlisting}

PROBLEM: jeżeli argument jest kategorii rvalue, np.~\code{f(1)}, to
będzie błąd kompilacji.  Dlaczego?

\vspace{0.25 cm}

\red{TO JEST ZŁE ROZWIĄZANIE!}

\end{frame}

%************************************************************************

\subsection{Rozwiązanie: const T &}

\begin{frame}[fragile]

  \frametitle{Rozwiązanie: \code{const T &}}

  Rozwiązanie z \code{const T &} wygląda tak:
  
\begin{lstlisting}[language=C++]
template<typename T>
void
f(const T &a)
{
  g(a);
}
\end{lstlisting}

Teraz będzie się kompilować dla r-wartości, np.~\code{f(1)}.

\vspace{0.25 cm}

PROBLEM: Jeżeli funkcja będzie \code{g(int &)}, to kod nie będzie się
kompilować.  Dlaczego?

\vspace{0.25 cm}

\red{TO JEST ZŁE ROZWIĄZANIE!}

\end{frame}

%************************************************************************

\subsection{Rozwiązanie: T & razem z const T &}

\begin{frame}[fragile]

  \frametitle{Rozwiązanie: \code{T &} razem z \code{const T &}}

  Możemy mieć dwie definicje, jedna dla \code{T &}, a druga dla
  \code{const T &}.  Czyli mamy dwie definicje dla jednego parametru.

  \vspace{0.25 cm}

  PROBLEM: Dla $n$ parametrów potrzebujemy $2^n$ definicji funkcji!

  \vspace{0.25 cm}
  
  \red{TO JEST ZŁE ROZWIĄZANIE!}

\end{frame}

%************************************************************************

\subsection{Prawidłowe rozwiązanie}

\begin{frame}[fragile]

  \frametitle{Prawidłowe rozwiązanie}

  Z C++11, typem parametru powina być r-referencja bez kwalifikatorów,
  czyli tak:

\begin{lstlisting}[language=C++]
template<typename T>
void
f(T &&t)
{
  g(std::forward<T>(t));
}
\end{lstlisting}

  Problem w tym, że parametr \code{t} jest l-wartością (bo ma nazwę
  \code{t}), nawet jeżeli argumentem wywołania funkcji \code{f} była
  r-wartość.  W ten sposób tracimy informację o kategorii wartości
  wyrażenia, które było argumentem funkcji \code{f}.

\end{frame}

%************************************************************************

\subsection{Referencja do referencji}

\begin{frame}[fragile]

  \frametitle{Referencja do referencji}

  W C++ nie ma typu \red{referencji do referencji}, ale takie typy
  mogą się pojawić, jako efekt definicji typów szablonowych z użyciem
  \code{typedef} czy \code{using}.

\begin{lstlisting}
template<typename T>
class A
{
  typedef typename T &my_type;
  // ...
};
\end{lstlisting}

Jeżeli kompilator wywnioskuje typ T jako, na przykład, \code{int &},
to wtedy otrzymamy typ \code{my_type} jako \code{int & &}.  Co wtedy?

\end{frame}

%************************************************************************

\subsection{Spłaszczanie typów referencji}

\begin{frame}[fragile]

  \frametitle{Spłaszczanie typów referencji}

  Jeżeli pojawi się typ referencji do referencji, to kompilator
  zamieni taki typ na referencję według zasady:

  \begin{itemize}
  \item \code{cv1 T & cv2 T &} $\to$ \code{cv12 T &}
  \item \code{cv1 T & cv2 T &&} $\to$ \code{cv12 T &}
  \item \code{cv1 T && cv2 T &} $\to$ \code{cv12 T &}
  \item \code{cv1 T && cv2 T &&} $\to$ \code{cv12 T &&}
  \end{itemize}

  Zbiory cv1, cv2, cv12 oznaczają zbiory kwalifikatorów, do których
  mogą należeć \red{const} i \red{volatile}.  Zbiór cv12 jest sumą
  zbiorów cv1 i cv2, czyli $\texttt{cv12} = \texttt{cv1} \cup
  \texttt{cv2}$.

\end{frame}

%************************************************************************

\subsection{Dopasowywanie typu argumentu szablonu}

\begin{frame}[fragile]

  \frametitle{Dopasowywanie typu argumentu szablonu}

  Jaki będzie dopasowany typ \code{T} w szablonie?  Przykład:

\begin{lstlisting}[language=C++]
template<typename T>
void
f(T &&a)
{
}
\end{lstlisting}

Dwie zasady:
\begin{itemize}
\item jeżeli argumentem funkcji \code{f} jest r-wartość typu A, to
  \code{T = A}
\item jeżeli argumentem funkcji \code{f} jest l-wartość typu A, to
  \code{T = A &}
\end{itemize}

\end{frame}

%************************************************************************

\subsection{std::forward}

\begin{frame}[fragile]

  \frametitle{\code{std::forward}}

  Funkcja szablonowa \code{std::forward} przyjmuje l-wartość \code{a}
  typu $T$ i zależności od sposobu wywołania (typu argumentu szablonu)
  zwraca:

  \begin{itemize}
  \item r-referencję na \code{a} dla \code{std::forward<T>(a)}
  \item l-referencję na \code{a} dla \code{std::forward<T &>(a)} 
  \end{itemize}

  Funkcji \code{std::forward} używa się w definicji pewnej funkcji
  szablonowej \code{f}, gdzie trzeba odzyskać kategorię wyrażenia,
  które było argumentem wywołania funkcji szablonowej \code{f}.

\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}

  \item Problem doskonałego przekazywania argumentów występuje w
    programowaniu generycznym z użyciem szablonów.

  \item Jako typ parametru funkcji używamy: \code{T &&t}, gdzie
    \code{T} jest parametrem szablonu, a \code{t} parametrem funkcji.

  \item Aby przekazać parametr do innej funkcji, używamy funkcji
    \code{std::forward}, która odzyskuje kategorię wartości wyrażenia.

  \end{itemize}
\section{Złe rozwiązania}

Programista ma napisać funkcję \code{f}, która wywołuje funkcję
\code{g}.  Nie wiemy jaki jest typ parametru funkcji \code{g}, ale
chcielibyśmy wywoływać funkcję \code{f} tak, jak wykonujemy funkcję
\code{g}.

Rozwiązanie z taką definicją szablonu (typem parametru funkcji
szablonowej jest niestała l-referencja) nie kompiluje się:

\lstinputlisting{bad1.cc}

Rozwiązanie z taką inną definicją szablonu (typem parametru funkcji
szablonowej jest stała l-referencja) też się nie kompiluje:

\lstinputlisting{bad2.cc}

Jeżeli zdefiniujemy dwa szablony (jeden dla referencji niestałej, a
drugi dla stałej), to wtedy problem jest rozwiązany, chociaż lepiej
byłoby zdefiniować tylko jeden szablon:

\lstinputlisting{bad3.cc}

\section{\code{std::forward}}

Przykładowy program pokazujący działanie funkcji \code{std::forward}:

\lstinputlisting{forward.cc}

\section{Spłaszczenie referencji}

Przykładowy program pokazujący spłaszczanie referencji:

\lstinputlisting{collapse.cc}

\section{Wnioskowanie typów}

Przykładowy program pokazujący wnioskowanie typów.  Jeżeli typem jest
\code{auto &&}, to kompilator wywnioskuje, czy referencja powinna być
typu l-wartość czy r-wartość w zależności od kategorii wartości
wyrażenia, które jest inicjalizatorem referencji.

Żeby zobaczyć wywnioskowany typ w czasie kompilacji, w kodzie
wprowadzono błąd, o którym kompilator informuje jednocześnie wypisując
interesujący nas typ.

\lstinputlisting{deduction.cc}

\section{Dobre rozwiązanie}

Zdefiniujemy różne przeciążenia dla funkcji \code{g}.  Funkcja
\code{g} będzie przyjmowała też drugi parametr, który będzie pozwalał
nam stwierdzić, czy kompilator wybrał te przeciążenie, które się
spodziewaliśmy.  W funkcji \code{main} wywołujemy każde przeciążenie
funkcji.

Potem piszemy funkcję \code{f}, która doskonale przekazuje swój
argument do funkcji \code{g}.

\lstinputlisting{perfect.cc}

Usunąć funkcję \code{forward} z funkcji \code{f}.  Wtedy będą
przekazywane zawsze l-wartości do funkcji \code{g}.  Funkcja forward
załatwia nam poprawne przekazywanie kategorii wartości argumentu
wywołania funkcji \code{f}.

<!-- LocalWords: expr -->
<!-- LocalWords: lvalue lvalues rvalue -->
<!-- LocalWords: rvalue -->

<!-- LocalWords: deklaratora -->
<!-- LocalWords: deklaratorem -->

<!-- LocalWords: inicjalizowana -->
<!-- LocalWords: inicjalizowaną -->
<!-- LocalWords: inicjalizowane -->
<!-- LocalWords: inicjalizującego -->
<!-- LocalWords: inicjalizującym -->

<!-- LocalWords: wyoptymalizowana -->
<!-- LocalWords: wyoptymalizowane -->
<!-- LocalWords: wyoptymalizowanie -->

<!-- LocalWords: zainicjalizowana -->
<!-- LocalWords: zainicjalizowaną -->
<!-- LocalWords: zainicjalizowane -->

<!-- LocalWords: binds -->
<!-- LocalWords: nullptr -->
<!-- LocalWords: object -->
<!-- LocalWords: overload -->
<!-- LocalWords: name names -->
<!-- LocalWords: member -->
<!-- LocalWords: move -->
<!-- LocalWords: reference references -->
<!-- LocalWords: refer refers -->
<!-- LocalWords: resolution -->
<!-- LocalWords: title -->
