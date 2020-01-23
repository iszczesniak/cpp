---
title: std::shared_ptr
---

# Introduction

  Współdzielenie bez uwiązania polega na możliwości ewentualnego
  użycia współdzielonego obiektu, ale bez zachowania gwarancji, że
  obiekt będzie ciągle istniał.

  Mając obiekt współdzielony, chcemy jedynie mieć możliwość
  ewentualnego odwołania się do niego, jeżeli istnieje.  Jeżeli obiekt
  już nie istnieje, to chcemy jedynie mieć możliwość sprawdzenia tego.

Inteligentny wskaźnik \code{std::weak_ptr} pozwala na śledzenie
obiektu, który jest zarządzany przez \code{std::shared_ptr}.
Śledzenie nie daje nam gwarancji, że obiekt istnieje, ale daje nam
możliwość ewentualnego dostępu, jeżeli zarządzany obiekt jeszcze
istnieje.

\lstinputlisting{intro.cc}


# Example

Napisać funkcję \code{factory}, która będzie fabryką obiektów klasy A.
Fabryka powinna śledzić już stworzone obiekty i nie tworzyć ich
ponownie, jeżeli ciągle istnieją.

\section{Rozwiązanie zadania}

\lstinputlisting{factory.cc}

  \item Jest fabryka (czyli funkcja zwracająca obiekty) wracająca
    obiekty współdzielone z użyciem \code{shared_ptr<A>}.

  \item Jeżeli obiekt nie istnieje, to fabryka go tworzy.

  \item Obiekt współdzielony jest niszczony, jeżeli nie jest już
    potrzebny.

  \item Fabryka nie współdzieli obiektu (nie uwiązuje go), ale chce
    mieć możliwość ponownego zwrócenia go, jeżeli on jeszcze istnieje
    i jeżeli będzie potrzebny.

  \item ROZWIĄZANIE: fabryka powinna pamiętać zwrócone obiekty
    współdzielone, ale bez uwiązywania ich, żeby mogły być zniszczone,
    jak nie będą już potrzebne.
    
  \end{itemize}

\end{frame}

%************************************************************************

\section{Szczegóły}

\subsection{std::weak\_ptr}

\begin{frame}

  \frametitle{\code{std::weak_ptr}}

  \begin{itemize}

  \item \code{\#include <memory>}
  \item Klasa C++11 implementująca współdzielenie bez uwiązania.
  \item Obiekty tej klasy można kopiować i przenosić, ale nie ma to
    szczególnego znaczenia, jak przy \code{unique_ptr} czy
    \code{shared_ptr}.
  \item Nierozerwalnie związany z \code{shared_ptr}.
  \item Obiekt \code{weak_ptr} tworzony jest na podstawie obiektu
    \code{shared_ptr}.
  \item \red{Nie niszczy obiektu, do którego się odwołuje.}
  \item Zarządzane obiekty nie wiedzą, że są zarządzane.
    
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Użycie}

\begin{frame}

  \frametitle{Użycie \code{weak_ptr}}

  \begin{itemize}
  \item Mając: \code{shared_ptr<A> sp;}
  \item Deklaracja: \code{weak_ptr<A> wp;}
  \item Tworzenie: \code{weak_ptr<A> wp(sp);}
  \item Tworzenie: \code{wp = sp;}
  \item Kopiowanie obiektów: \code{weak_ptr<A> wp2(wp);}
  \item Kopiowanie obiektów: \code{wp2 = wp;}
  \item Przenoszenie obiektów: \code{weak_ptr<A> wp2(move(wp));}
  \item Przenoszenie obiektów: \code{wp2 = move(wp);}
  \item Czy obiekt został już zniszczony? \code{wp.expired();}
  \item Ale jak pozyskać wskaźnik na obiekt współdzielony?
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Pozyskanie obiektu współdzielonego}

\begin{frame}

  \frametitle{Pozyskanie obiektu współdzielonego}

  PROBLEM: Jak bezpiecznie użyć (bez hazadru), skoro \code{weak_ptr}
  nie daje nam gwarancji, że obiekt nie zostanie zniszczony?  Taką
  gwarancję daje nam \code{shared_ptr}.

  \vspace{0.25 cm}

  Przecież bezpośrednio po uzyskaniu surowego wskaźnika obiekt może
  być zniszczony.

  \vspace{0.25 cm}

  ROZWIĄZANIE: tworzenie \code{shared_ptr} na podstawie
  \code{weak_ptr}.

  \vspace{0.25 cm}

  Robimy to tak (może rzucić wyjątek):\\
  \code{shared_ptr<A> sp(wp);}

  \vspace{0.25 cm}

  Albo tak (obiekt sp może być \code{nullptr}):\\
  \code{shared_ptr<A> sp = wp.lock();}

\end{frame}

%************************************************************************

\subsection{Jak to działa?}

\begin{frame}

  \frametitle{Jak to działa?}

  \begin{itemize}
  \item Grupa obiektów \code{shared_ptr} i \code{weak_ptr} współdzielą
    jedną strukturę zarządzającą, alokowaną dynamicznie.

  \item Każdy obiekt \code{shared_ptr} i \code{weak_ptr} posiada
    wskaźnik na strukturę zarządzającą.

  \item Częścią struktury zarządzającej jest licznik odwołań tylko
    obiektów \code{shared_ptr}.

  \item Inną częścią struktury zarządzającej jest licznik odwołań
    obiektów \code{shared_ptr} i \code{weak_ptr}.

  \item Kiedy licznik odwołań \code{shared_ptr} wyniesie 0, obiekt
    zarządzany jest niszczony.

  \item Kiedy licznik odwołań \code{shared_ptr} i \code{weak_ptr}
    wyniesie 0, struktura zarządzająca jest niszczona.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Użycie współbieżne}

\begin{frame}

  \frametitle{Użycie współbieżne}

  \begin{itemize}
  \item Klasa jest bezpieczna w programowaniu współbieżnym.
  \item Pozyskany obiekt klasy \code{shared_ptr} możemy swobodnie
    używać, bo jest on wyłączną kopią wątku.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Wydajność}

\begin{frame}

  \frametitle{Wydajność}

  \begin{itemize}
  \item Obiekt \code{weak_ptr} zajmuje dwa razy więcej pamięci niż
    surowy wskaźnik, bo zawiera dwa pola:
    \begin{itemize}
    \item wskaźnik na zarządzany obiekt,
    \item wskaźnik na strukturę zarządającą.
    \end{itemize}
  \item Po co wskaźnik na zarządzany obiekt, skoro i tak użytkownik
    nie ma do niego dostępu?  Bo potrzebny jest przy tworzeniu obiektu
    \code{shared_ptr}.
  \item Wskaźnik na zarządzany obiekt mógłby być częścią struktury
    zarządzającej, ale wtedy dla obiektów \code{shared_ptr} odwołanie
    do obiektu zarządzanego byłoby wolniejsze (bo byłoby dodatkowo
    pośrednie).
  \end{itemize}
  
\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}

  \item Klasa \code{weak_ptr} implementuje współdzielenie bez
    uwiązania.
  \item Bez uwiązania, czyli bez gwarancji, że obiekt, do którego się
    odwołujemy, będzie istniał.
  \item Główne zadanie: pozwala użyć obiekt współdzielony, jeżeli
    jeszcze istnieje.
  \item Nie niszczy obiektu, do którego się odwołuje.
    
  \end{itemize}

\end{frame}


# Conclusion

<!-- LocalWords: inlined multithreaded -->
<!-- LocalWords: performant rvalue suboptimal -->
