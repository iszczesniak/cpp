---
title: Containers
---

# Introduction

A list, a vector, an array, an associative map, a set, and other data
structures, are called **containers** in C++.  A container:

* is a *generic* data structure,
* stores elements of any type,
* stores elements only of a single type,
* stores elements by value, not by reference.

Containers are complemented by iterators and algorithms.  The iterator
is a generalization of a pointer.  Algorithms, such as `std::sort`,
are generalized in that they can be used with various containers.

# History

In the early 90's, the containers were:

* a cutting-edge technology, and a hot research topic,
* implemented as the STL.

Now the containers are:

* an indispensible tool of every-day use,
* part of the standard library.

There is no excuse, put them to use.

\subsection{Basic container types}

* `std::vector<T>` - the vector,

* `std::forward_list<T>` - the sinlgy-linked list,

* `std::list<T>` - the doubly-linked list,

* `std::deque<T>` - the deque, amalgamation of the vector and the
  doubly-linked list,

* `std::map<K, V>` - the associative array (aka dictionary),

* `std::multimap<K, V>` - the associative array with duplicate keys
  allowed,

* `std::set<T>` - the set,

* `std::multiset<T>` - the set with duplicate elements allowed,

* `std::priority_queue<T>` - the priority queue.

Container types can be nested, i.e. `T` can be a container type too.



%************************************************************************

\subsection{Typy kontenerów - wady i zalety}

\begin{frame}

  \frametitle{Typy kontenerów - wady i zalety}

  \begin{itemize}

  \item \code{std::vector{<}T{>}} - najlepszy, jeżeli potrzebujemy
    swobodnego dostępu (\code{operator []}), ale rzadko zmieniamy
    rozmiar wektora, wstawiamy albo usuwamy elementy.  Jest to po
    prostu tablica, którą możemy swobodnie i wygodnie zmieniać.

  \item \code{std::list{<}T{>}} - najlepsza, jeżeli często zmieniamy
    rozmiar, często dodajemy albo usuwamy elementy, wystarczy dostęp
    iteracyjny i nie jest nam potrzebny swobodny dostęp (nie ma
    \code{operator []}).

  \item \code{std::deque{<}T{>}} - najlepszy, jeżeli często zmianiamy
    rozmiar, często dodajemy albo usuwamy elementy, ale ciągle
    potrzebujemy szybkiego swobodnego dostępu (\code{operator []}
    jest).

  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Iteratory}

\begin{frame}

  \frametitle{Iteratory}

  \begin{itemize}
    \item Pozwalają na dostęp do elementów kontenera.
    \item Implementacja: wskaźniki obudowane w klasy.
    \item Do funkcji przekazujemy przez wartość, nie referencję.
    \item Dla kontenera T, iterator to: \code{T::iterator}.
    \item Iterator ``const'' obiektów stałych: \code{T::const\_iterator}.
    \item Używaj iteratora ``const'', jeżeli nie modyfikujesz kontenera.
    \item Podstawowe operacje: \code{++i}, \code{i++}.
    \item Podstawowe funkcje: \code{T::begin()}, \code{T::end()}.
    \item Różne funkcje (\code{find}, \code{insert}) zwracają iteratory.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Iteratory odwrotne}

\begin{frame}

  \frametitle{Iteratory odwrotne}

  \begin{itemize}
  \item Pozwalają na iterację od końca po elementach kontenera.
  \item Typ: \code{T::reverse\_iterator} i \code{T::const\_reverse\_iterator}
  \item Skomplikowane, bardzo trudne w użyciu i...
  \item dlatego nie mają większego znaczenia praktycznego.
  \item Przestroga: \red{lepiej nie używać!}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Algorytmy}

\begin{frame}

  \frametitle{Algorytmy}

  \begin{itemize}
  \item Algorytmy dla różnych kontenerów:
    \begin{itemize}
    \item sortowanie elementów (lepszej implementacji nie znajdziecie),
    \item wyszukiwanie elementów,
    \item iterowanie po elementach,
    \item usuwanie i dodawanie elementów.
    \end{itemize}
  \item Działają dla różnych kontenerów, bo kontenery mają ten sam
    interfejs:
    \begin{itemize}
      \item nazwy typów (np. \code{T::data\_value}),
      \item nazwy funkcji (np. \code{T::begin()}).
    \end{itemize}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{std::pair<A, B>}

\begin{frame}

  \frametitle{std::pair<A, B>}

  \begin{itemize}
  \item \code{\#include <utility>}
  \item Para p obiektów typów A i B: \code{std::pair<A, B> p;}
  \item p.first - pierwszy element, p.second - drugi element
  \item Globalna funkcja szablonowa \code{std::make\_pair} pozwala na
    tworzenie pary bez podania typów, kompilator wywnioskuje typy
    sam:\\ \code{std::make\_pair(1, "test");}
  \item Funkcja \code{tie} pozwala na wygodne przypisanie wartości z
    pary do osobnych zmiennych:\\ \code{std::tie(f, s) = p;}
  \item Przeniesienie pary polega na przeniesieniu każdego z obiektów
    składowych.
  \item Ma zdefiniowane globalne operatory: \code{!= < == > <= >=}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Obiekt funkcyjny}

\begin{frame}

  \frametitle{Obiekt funkcyjny}

  \begin{itemize}
  \item Obiekt funkcyjny nazywany jest też funktorem.
  \item Obiekt klasy, w której zdefiniowany jest operator wywołania
    funkcji: \code{operator()}
  \item Ten operator musi być \code{non-static} i najlepiej
    \code{const}.
  \item Ten operator można przeciążyć na wiele sposobów, ale nas
    interesuje operator, który można wykorzystać do porównania
    obiektów pewnej klasy A, elementów kontenera:\\ \code{bool
      operator () (const A \&a1, const A \&a2) const;}
  \item Kompilator będzie się starał wkompilować inline tę funkję.
  \item ZALETA: Obiektowi funkcyjnemu możemy podać dodatkowe dane w
    konstruktorze, potem używane w operatorze wywołania funkcji.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Obiekt funkcyjny - przykład}

\begin{frame}[fragile]

  \frametitle{Obiekt funkcyjny - przykład}

\begin{lstlisting}[language=C++]
struct CMP
{
  bool m_order;
  CMP(bool order): m_order(order) {}
  bool operator () (const A &e1,
                    const A &e2) const
  {
    bool s = e1.m_text < e2.m_text;
    return m_order ? !s : s;
  }
};
\end{lstlisting}

\end{frame}

%************************************************************************

\subsection{Pętle iteracyjne po staremu}

\begin{frame}

  \frametitle{Pętle iteracyjne po staremu}

  \verbatiminput{03-example1.cc}

\end{frame}

%************************************************************************

\subsection{Pętle iteracyjne po nowemu}

\begin{frame}

  \frametitle{Pętle iteracyjne po nowemu}

  \verbatiminput{03-example2.cc}

\end{frame}

# Conclusion

* Don't implement the basic data structures, because they are already
  there.

* Use the containers, and get better at using them.

* With the containers, you can build complex data structures.

* With the containers use the standard algorithms, because your own
  algorithm implementations will most likely perform worse.

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
