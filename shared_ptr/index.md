---
title: std::shared_ptr
---

# Introduction

Smart pointer type `std::shared_ptr` is used for sharing objects
between different parts of code and threads.  It implemented the
semantics of the shared pointer.

Sharing a dynamically-allocated object is necessary, when:

* the object is used by different parts of code, and perhaps by
  different threads,

* it is hard to predict where and when exactly the object will be
  destroyed.

It may be hard to predict where and where the object will be
destroyed, because:

* its lifetime may depend on the data,

* different threads may process the data at different time.

%************************************************************************

\subsection{std::shared\_ptr}

\begin{frame}

  \frametitle{\code{std::shared_ptr}}

  \begin{itemize}

  \item \code{\#include <memory>}
  \item Klasa C++11 implementująca współdzielenie dynamicznego
    obiektu.
  \item Przeciwstawność \code{std::unique_ptr}.
  \item Obiekty tej klasy można kopiować i przenosić.
  \item Kopiując obiekt \code{std::shared_ptr}, tworzymy grupę
    obiektów zarządzających, które współdzielą jeden obiekt
    dynamiczny.
  \item Grupa obiektów \code{shared_ptr} jest właścicielem
    zarządzanego obiektu.
  \item Grupa posiada \red{jeden licznik odwołań} do zarządzanego
    obiektu.
  \item Zarządzane obiekty nie wiedzą, że są zarządzane.
  \item Użycie tak wydajne czasowo, jak surowego wskaźnika.
  \item Zajmuje dwa razy więcej pamięci, niż surowy wskaźnik.
  \end{itemize}

\end{frame}

%************************************************************************

\section{Szczegóły}

\subsection{Użycie}

\begin{frame}

  \frametitle{Użycie}

  \begin{itemize}
  \item Deklaracja: \code{shared_ptr<A> a;}
  \item Oddanie pod zarządzanie: \code{shared_ptr<A> sp(new A());}
  \item Oddanie pod zarządzanie: \code{sp.reset(new A());}
  \item Kopiowanie obiektów: \code{shared_ptr<A> sp2(sp);}
  \item Kopiowanie obiektów: \code{sp2 = sp;}
  \item Przenoszenie obiektów: \code{shared_ptr<A> sp2(move(sp));}
  \item Przenoszenie obiektów: \code{sp2 = move(sp);}
  \item Niszczenie: tego nie robimy, to odbywa się automatycznie.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Jak to działa?}

\begin{frame}

  \frametitle{Jak to działa?}

  \begin{itemize}
  \item Grupa obiektów \code{shared_ptr} współdzieli jedną strukturę
    zarządzającą, alokowaną dynamicznie.
  \item Każdy obiekt \code{shared_ptr} posiada wskaźnik na strukturę
    zarządzającą.
  \item Częścią struktury zarządzającej jest licznik odwołań.
  \item Licznik odwołań to inaczej wielkość grupy.
  \item Przy kopiowaniu obiektów \code{shared_ptr}, licznik odwołań
    jest inkrementowany.
  \item Przy niszczeniu obiektów \code{shared_ptr}, licznik odwołań
    jest dekrementowany.
  \item Kiedy licznik odwołań wyniesie 0, obiekt zarządzany jest
    niszczony.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Z unique_ptr do shared_ptr}

\begin{frame}

  \frametitle{Z \code{unique_ptr<T>} do \code{shared_ptr<T>}}

  Można tak? Można.

  \code{unique_ptr<A> up(new A("A1"));}\\
  \code{shared_ptr<A> sp(up.release());}

  \vspace{0.25 cm}
  
  Ale lepiej tak:
  
  \code{unique_ptr<A> up(new A("A1"));}\\
  \code{shared_ptr<A> sp(move(up));}

  \vspace{0.25 cm}

  Można, bo \code{shared_ptr<T>} ma konstruktor, który przyjmuje
  referencję typu rvalue do obiektu typu \code{unique_ptr<T>}.

  \vspace{0.25 cm}

  Dzięki temu możemy tworzyć \code{shared_ptr<T>} z obiektów
  tymczasowych typu \code{unique_ptr<T>}, np.~zwracanych jako wynik
  wywołania funkcji.

\end{frame}

%************************************************************************

\subsection{Użycie współbieżne}

\begin{frame}

  \frametitle{Użycie współbieżne}

  \begin{itemize}
    \item Klasa częściowo jest bezpieczna w programowaniu
      współbieżnym.
    \item Jeżeli wątek ma swoją kopię \code{shared_ptr}, to może jej
      swobodnie używać bez synchronizacji, włącznie z jej
      przenoszeniem i tworzeniem kopii.
    \item Jeżeli wątki używają tego samego obiektu \code{shared_ptr},
      to muszą synchronizować działania, jeżeli obiekt jest zmieniany.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Wydajność}

\begin{frame}

  \frametitle{Wydajność}

  \begin{itemize}
  \item Obiekt \code{shared_ptr} zajmuje dwa razy więcej pamięci niż
    surowy wskaźnik, bo zawiera dwa pola:
    \begin{itemize}
    \item wskaźnik na zarządzany obiekt,
    \item wskaźnik na strukturę zarządającą.
    \end{itemize}
  \item Dodatkowo jest dynamicznie alokowana pamięć na strukturę
    zarządzającą.
  \item Wskaźnik na zarządzany obiekt mógłby być częścią struktury
    zarządzającej, ale wtedy odwołanie do obiektu zarządzanego byłoby
    wolniejsze.
  \end{itemize}
  
\end{frame}

%************************************************************************

\subsection{std::make_shared}

\begin{frame}

  \frametitle{\code{std::make_shared}}

  Zamiast pisać typ A dwa razy w sposobie na piechotę:

  \code{shared_ptr<A> sp(new A("A1"));}

  \vspace{0.2 cm}
  
  Możemy napisać typ A tylko raz używając funkcji \code{make_shared}:
  
  \code{auto sp = make_shared<A>("A1");}

  \vspace{0.2 cm}

  Obiekt stworzony przez \code{make_shared} jest przenoszony, a nie
  kopiowany.

  \vspace{0.2 cm}

  ZALETA \#1: tworzenie obiektu zarządzanego i zarządzającego odbywa
  się w jedyn kroku, co jest bezpieczne pod względem obsługi wyjątków.

  \vspace{0.25 cm}

  ZALETA \#2: Funkcja \code{std::make_shared} tworzy obiekt zarządzany i
  zarządzający używając jednej alokacji pamięci, przez co jest szybsza
  niż osobne tworzenie tych obiektów.

\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}

  \item Klasa \code{shared_ptr<T>} pozwala na łatwe współdzielenie
    obiektów, które były stworzone dynamicznie.
  \item Główne zadanie: zniszczyć obiekt zarządzany, kiedy nie jest
    już potrzebny.
  \item Obiekty klasy \code{shared_ptr<T>} są dwa razy większe niż
    surowy wskaźnik.
  \item Można łatwo tworzyć obiekty \code{shared_ptr<T>} z
    \code{unique_ptr<T>}.

  \end{itemize}

\end{frame}

<!-- LocalWords:  -->
