---
title: std::unique_ptr
---

# Introduction

Pointers are indispensible.  Pointers:

* point to memory locations,

* are used in every programming language (at least internally): C,
  C++, Java, C#,

* can be used in the form of a reference, e.g., in Java or C#.

The pointer support can be:

* internaly only, and unavilable for a programmer, e.g., in Java or
  C#,

* raw or smart, as in C++,

* raw only, as in C.

In C++, it's best to avoid the raw pointers.

\end{frame}

%************************************************************************

\subsection{Motywacja: wady surowych wskaźników}

\begin{frame}

  \frametitle{Motywacja: wady surowych wskaźników}

  \begin{itemize}
  \item Nie wiadomo, czy wskazuje jeden obiekt czy tablice obiektów.
  \item Czy obiekt niszczymy przez \code{delete} czy \code{delete[]}?
  \item Nie mówi, kiedy wskazany obiekt powinien być zniszczony.
  \item Łatwo popełnić błędy używając surowych wskaźników:
    \begin{itemize}
    \item nie niszcząc obiektu (wyciek pamięci),
    \item niszcząc obiekt i potem próbować się do niego odwołać (dyndający wskaźnik),
    \item niepoprawna obsługa wyjątów.
    \end{itemize}
  \item Rozwiązaniem tych problemów są \emph{inteligentne wskaźniki}.
  \item Czasy \code{void *} dawno minęły.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Rodzaje inteligentnych wskaźników}

\begin{frame}

  \frametitle{Rodzaje inteligentnych wskaźników}

  \begin{itemize}
  \item \code{std::auto\_ptr} - przestażały, \red{lepiej unikać}
  \item \code{std::unique\_ptr} - stosować zamiast surowego wskaźnika
  \item \code{std::shared\_ptr} - wskazuje i współdzieli obiekt
  \item \code{std::weak\_ptr} - wskazuje obiekt współdzielony, ale
    nie współdzieli tego obiektu.
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
