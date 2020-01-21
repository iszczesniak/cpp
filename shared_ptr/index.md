---
title: std::shared_ptr
---

# Introduction

When we dynamically create some data (or any other resource) and use
them in other threads or parts of code, we run into the problem when
to destroy the data.  If we:

* don't destroy the data, we get a memory leak,

* destroy the data too soon, we get a race condition: a dangling
  pointer and undefined behavior, because other threads or parts of
  code still use the data,

* destroy the data too late, we get suboptimal performance, because we
  let the dispensable data linger in memory.

Therefore we should destroy the data at the right time, i.e., when
they are no longer needed.  However, this right time is hard to
pinpoint with raw pointers, because it may depend on:

* the data (i.e., their specific values),

* the timing of other threads.

The solution to the problem is the *shared-ownership semantics*:

* shared, because the data are managed by a group,

* ownership, because the data are destoryed when the group becomes
  empty.

In Java or C#, a reference has the shared-ownership semantics.

# `std::shared_ptr`

* `#include <memory>`

* The smart pointer type that implements the shared-ownership
  semantics.

* The objects of this type are the **managing objects**, and the data
  allocated dynamically is the **managed data**.

* It's a template class that implements the shared-ownership
  semantics.  The template argument is the type of the manged data.

* The opposite of `std::unique_ptr`.

* Objects of this class can be copied and moved.

* A managing object that takes the ownership of the managed data
  creates a group of managing objects.  Initially, this group has only
  one managing object.

* When we copy a managing object, we create another managing object,
  which belongs to the same group of managing objects.

* The managed data is destroyed, when the last managing object is
  destroyed.

* The managed data don't know they are managed: the type of the data
  doesn't have to be prepared to be managed, e.g., derived from some
  base class.

* As performant in terms of memory and time, as the same functionality
  implemented "manually" with raw pointers.

* An object of this class takes twice as much memory as the raw
  pointer.

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
