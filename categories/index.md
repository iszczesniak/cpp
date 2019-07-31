---
title: Expression categories
---

# Introduction

## The value of an expression

An expression is:

* a literal: `3.14`
* a variable ```x```
* an operator with operands: ```x + y```
* a function call: ```foo(x)```

**The value of an expression** is the result of evaluating an
  expression.

The value of an expression has:

* a type (e.g., ```int```, ```bool```, ```class A```) known at compile
  time,

* a value of the type (e.g., ```5```, ```false```, ```A()```) known at
  run time,

* a category (e.g., lvalue, rvalue) known at compile time.

{% highlight C++ %}
{% include_relative tmp-fun.cc %}
{% endhighlight %}

%************************************************************************

\subsection{Historia: CPL, C, C++98}

\begin{frame}

  \frametitle{Historia: CPL, C, C++98}

  Dwie kategorie wartości wyrażenia po raz pierwszy wprowadzono w
  języku CPL:
  \begin{itemize}
  \item lvalue (``left of assignment'' value),
  \item rvalue (``right of assignment'' value).
  \end{itemize}

  \vspace{0.25cm}

  W języku C wartości są ``lvalue'' (locator value), albo
  ``non-lvalue''.  Wartości ``lvalue'' posiadają miejsce w pamięci,
  np.~zmienne.

  \vspace{0.25cm}

  C++98 przyjęło definicję z C, ale nazwało ``non-lvalue'' jako
  ``rvalue''.

  \vspace{0.25cm}

  Po polsku mówimy \red{l-wartość} i \red{r-wartość}.
  
\end{frame}

%************************************************************************

\section{Szczegóły}

\subsection{Kategoria wartości wyrażenia}

\begin{frame}

  \frametitle{Kategoria wartości wyrażenia}

  Dwie podstawowe kategorie to: l-wartość i r-wartość.  Wyrażenie
  kategorii l-wartość nazywamy l-wartością, a wyrażenie kategorii
  r-wartość nazywamy r-wartością.

  \vspace{0.25 cm}

  Kategoria wartości wyrażenia określa, jakie operacje możemy dalej
  wykonać na opracowanym wyrażeniu.  Niektóre operacje możemy wykonać
  wyłącznie na l-wartości (np.~\code{&}), inne wyłącznie na r-wartości
  (np.~\code{+} dla typu \code{int}).
  
  \vspace{0.25 cm}

  Przykładowe operacje na wyrażeniu \code{x}:
  \begin{itemize}
  \item przypisanie: \code{x = 1}
  \item inicjalizacja referencji: \code{<typ referencyjny> y = x}
  \item pobranie adresu: \code{\&x}
  \item wyłuskanie: \code{*x}
  \item inkrementacja: \code{++x, x++}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Nowoczesny C++: zmiany, zmiany, zmiany}

\begin{frame}

  \frametitle{Nowoczesny C++: zmiany, zmiany, zmiany}

  W nowoczesnym C++ wprowadzono nowe kategorie wartości wyrażeń
  (pr-wartość, gl-wartość, x-wartość), jednak podstawą ciągle są
  l-wartości i r-wartości.

  \vspace{0.25cm}

  Aby precyzyjnie posługiwać się nowoczesnym C++ należy opanować
  podstawy kategorii wartości wyrażeń.  Na przykład, poniższe
  kryptyczne zdanie jest częścią definicji l-wartości w C++11!

  \vspace{0.25cm}

  \red{``Even if the variable's type is \emph{rvalue reference}, the
    expression consisting of its name is an \emph{lvalue
      expression}.''}

\end{frame}

%************************************************************************

\subsection{Kategoria l-wartość w C++}

\begin{frame}

  \frametitle{Kategoria l-wartość w C++}

  Jeżeli kategoria wartości wyrażenia to l-wartość, to można pobrać
  adres, czyli można wykonać: \code{\&(wyrażenie)}.

  \vspace{0.5cm}

  Przykłady l-wartości:

  \begin{itemize}
  \item nazwa zmiennej: \code{x}
  \item nazwa funkcji: \code{foo}
  \item literał ciągu znaków: \code{"Hello World!";}
  \item \code{++i}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Kategoria r-wartość w C++}

\begin{frame}

  \frametitle{Kategoria r-wartość w C++}

  Jeżeli wyrażenie nie jest l-wartością, to jest r-wartością.  Nie
  można pobrać adresu r-wartości.

  \vspace{0.5cm}

  Przykłady r-wartości:

  \begin{itemize}
  \item literał: \code{1}
  \item \code{std::string("Hello World!");}
  \item \code{i++}
  \item wywołanie funkcji: \code{foo()}, jeżeli \code{int foo();}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Konwersja z l-wartości na r-wartość}

\begin{frame}

  \frametitle{Konwersja z l-wartości na r-wartość}

  L-wartość może być poddana standardowej konwersji do r-wartości.

  \vspace{0.5cm}

  Na przykład, operator \code{+} dla typu \code{int} wymaga r-wartości
  jako swoich operandów, dlatego poniższy przykład jest poprawny, bo
  l-wartości, którymi są wyrażenia \code{x} i \code{y}, zostaną
  poddane konwersji do r-wartości.

  \vspace{0.5cm}

  \code{int x, y;}

  \code{x + y;}

  \vspace{0.5cm}

  Nie ma niejawnej konwersji z r-wartości do l-wartości.

\end{frame}

%************************************************************************

\subsection{Przykład: operator ++}

\begin{frame}

  \frametitle{Przykład: operator \code{++}}

  Operator inkrementacji (\code{++}) jako argumentu wymaga
  \red{l-wartości}.  Wyrażenie z operatorem \code{++} jest:

  \begin{itemize}
  \item \red{l-wartością} dla operatora prefixowego, np.~\code{++i},
    bo operator wykonuje działanie na obiekcie \code{i}, a potem
    zwraca l-referencję na ten obiekt,
  \item \red{r-wartością} dla operatora sufixowego, np.~\code{i++}, bo
    operator tworzy kopię obiektu \code{i}, wykonuje działanie na
    obiekcie \code{i}, a potem zwraca stworzoną kopię obiektu.
  \end{itemize}

  Dlatego \code{++++i} kompiluje się, a \code{i++++} już nie.
  
\end{frame}

%************************************************************************

\subsection{Obiekty tymczasowe}

\begin{frame}

  \frametitle{Obiekty tymczasowe}

  Obiekt tymczasowy (ang.~temporary) jest tworzony przy:

  \begin{itemize}
    \item opracowywaniu wyrażenia: \code{1 + 2, string("T") + "4";}
    \item przekazywaniu argumentu wywołania funkcji:\\
      \code{void foo(const A \&);}\\
      \code{foo(A());}
    \item zwracaniu wartości funkcji: \code{string x = foo();}
    \item rzucaniu wyjątku: \code{throw A();}
  \end{itemize}

  \vspace{0.25cm}

  Obiekty tymczasowe w C++98 były zawsze kopiowane.

  \vspace{0.25cm}

  Obiekty tymczasowe w C++11 mogą być \emph{przenoszone}, bo
  wyrażenia, w których są tworzone (np.~jako argument wywołania
  funkcji) są r-wartością, którą można wskazać r-referencją.

\end{frame}

%************************************************************************

\subsection{Funkcje a kategorie wartości wyrażeń}

\begin{frame}

  \frametitle{Funkcje a kategorie wartości wyrażeń}

  Funkcja o nazwie \code{foo} może być użyta w wyrażeniu na dwa
  sposoby:

  \begin{itemize}
  \item użycie tylko nazwy:
    \begin{itemize}
    \item przykładowe wyrażenie: \code{foo},
    \item w tym przypadku \code{foo} jest l-wartością, bo na nazwę,
    \item możemy pobrać adres l-wartości, więc \code{&foo} jest OK,
    \end{itemize}
  \item wywołanie funkcji:
    \begin{itemize}
    \item przykładowe wyrażenie: \code{foo(argumenty)},
    \item kategoria wartości wyrażenia wywołania funkcji zależy od
      typu wartości zwracanej przez funkcję:
      \begin{itemize}
      \item jeżeli typem jest l-referencja, to wyrażenie jest
        l-wartością, np.: jeżeli \code{int &foo();}, to \code{foo()}
        jest l-wartością,
      \item jeżeli typ nie jest referencyjny, to wyrażenie jest
        r-wartością: np.: jeżeli \code{int foo();}, to \code{foo()}
        jest r-wartością.
      \end{itemize}
    \end{itemize}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Typy niepełne a kategorie wartości wyrażeń}

\begin{frame}[fragile]

  \frametitle{Typy niepełne a kategorie wartości wyrażeń}

  Jeżeli typ nie został w pełni zdefiniowany, bo został jedynie
  zadeklarowany, albo częściowo zdefiniowany jako klasa abstrakcyjna,
  to typ taki nazywamy \red{typem niepełnym} (ang.~incomplete type).

  \vspace{0.25 cm}

  Wyrażenia typu niepełnego mogą mieć tylko kategorię l-wartość.

  \vspace{0.25 cm}

  {\scriptsize
  \lstinputlisting[]{incomplete.cc}
  }

\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}

  \item Kategoria wartości odnosi się do wyrażenia, a nie wartości
    pewnego typu (np.~klasy A albo typu \code{int}).

  \item Wartość pewnego typu (np.~klasy A albo typu \code{int}) nie ma
    kategorii wartości.

  \item Kategoria wartości wyrażenia określa, jakie operacje można
    dalej wykonać na wyrażeniu.

  \item Każde wyrażenie jest l-wartością albo r-wartością.

  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Dziękuję}

\begin{frame}[plain]

  \begin{center}
    \huge Dziękuję za uwagę.
  \end{center}

\end{frame}

\end{document}

%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************
%************************************************************************

\section{}

\begin{frame}

  \frametitle{}

  \begin{itemize}
  \item
  \end{itemize}

\end{frame}
% -*- coding: utf-8 -*-

\documentclass[compress]{beamer}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage{color}
\usepackage{listings}

\input{beamer.tex}
\input{listings.tex}

\begin{document}

%************************************************************************

\title{Kategorie wartości wyrażeń}

\author{dr inż.~Ireneusz Szcześniak}

\date{jesień 2018 roku}

\begin{frame}[plain]
  \titlepage
\end{frame}

%************************************************************************

\section{Wprowadzenie}

\subsection{Wartość wyrażenia}

\begin{frame}

  \frametitle{Wartość wyrażenia}

  Wyrażeniem jest:
  \begin{itemize}
  \item literał: \code{3.14}
  \item zmienna: \code{x}
  \item operator z operandami: \code{x + y}
  \item wywołanie funkcji: \code{foo(x)}
  \end{itemize}

  \vspace{0.5cm}

  \red{Wartość wyrażenia} jest wynikiem opracowania wyrażenia.

  \vspace{0.5cm}
  
  Wartość wyrażenia ma:

  \begin{itemize}
  \item typ (np.~int, bool, klasa A) - znany w czasie kompilacji,
  \item wartość typu (np.~5, false, A()) - znana w czasie uruchomienia,
  \item kategorię (l-wartość lub r-wartość) - znana w czasie kompilacji.
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Historia: CPL, C, C++98}

\begin{frame}

  \frametitle{Historia: CPL, C, C++98}

  Dwie kategorie wartości wyrażenia po raz pierwszy wprowadzono w
  języku CPL:
  \begin{itemize}
  \item lvalue (``left of assignment'' value),
  \item rvalue (``right of assignment'' value).
  \end{itemize}

  \vspace{0.25cm}

  W języku C wartości są ``lvalue'' (locator value), albo
  ``non-lvalue''.  Wartości ``lvalue'' posiadają miejsce w pamięci,
  np.~zmienne.

  \vspace{0.25cm}

  C++98 przyjęło definicję z C, ale nazwało ``non-lvalue'' jako
  ``rvalue''.

  \vspace{0.25cm}

  Po polsku mówimy \red{l-wartość} i \red{r-wartość}.
  
\end{frame}

%************************************************************************

\section{Szczegóły}

\subsection{Kategoria wartości wyrażenia}

\begin{frame}

  \frametitle{Kategoria wartości wyrażenia}

  Dwie podstawowe kategorie to: l-wartość i r-wartość.  Wyrażenie
  kategorii l-wartość nazywamy l-wartością, a wyrażenie kategorii
  r-wartość nazywamy r-wartością.

  \vspace{0.25 cm}

  Kategoria wartości wyrażenia określa, jakie operacje możemy dalej
  wykonać na opracowanym wyrażeniu.  Niektóre operacje możemy wykonać
  wyłącznie na l-wartości (np.~\code{&}), inne wyłącznie na r-wartości
  (np.~\code{+} dla typu \code{int}).
  
  \vspace{0.25 cm}

  Przykładowe operacje na wyrażeniu \code{x}:
  \begin{itemize}
  \item przypisanie: \code{x = 1}
  \item inicjalizacja referencji: \code{<typ referencyjny> y = x}
  \item pobranie adresu: \code{\&x}
  \item wyłuskanie: \code{*x}
  \item inkrementacja: \code{++x, x++}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Nowoczesny C++: zmiany, zmiany, zmiany}

\begin{frame}

  \frametitle{Nowoczesny C++: zmiany, zmiany, zmiany}

  W nowoczesnym C++ wprowadzono nowe kategorie wartości wyrażeń
  (pr-wartość, gl-wartość, x-wartość), jednak podstawą ciągle są
  l-wartości i r-wartości.

  \vspace{0.25cm}

  Aby precyzyjnie posługiwać się nowoczesnym C++ należy opanować
  podstawy kategorii wartości wyrażeń.  Na przykład, poniższe
  kryptyczne zdanie jest częścią definicji l-wartości w C++11!

  \vspace{0.25cm}

  \red{``Even if the variable's type is \emph{rvalue reference}, the
    expression consisting of its name is an \emph{lvalue
      expression}.''}

\end{frame}

%************************************************************************

\subsection{Kategoria l-wartość w C++}

\begin{frame}

  \frametitle{Kategoria l-wartość w C++}

  Jeżeli kategoria wartości wyrażenia to l-wartość, to można pobrać
  adres, czyli można wykonać: \code{\&(wyrażenie)}.

  \vspace{0.5cm}

  Przykłady l-wartości:

  \begin{itemize}
  \item nazwa zmiennej: \code{x}
  \item nazwa funkcji: \code{foo}
  \item literał ciągu znaków: \code{"Hello World!";}
  \item \code{++i}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Kategoria r-wartość w C++}

\begin{frame}

  \frametitle{Kategoria r-wartość w C++}

  Jeżeli wyrażenie nie jest l-wartością, to jest r-wartością.  Nie
  można pobrać adresu r-wartości.

  \vspace{0.5cm}

  Przykłady r-wartości:

  \begin{itemize}
  \item literał: \code{1}
  \item \code{std::string("Hello World!");}
  \item \code{i++}
  \item wywołanie funkcji: \code{foo()}, jeżeli \code{int foo();}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Konwersja z l-wartości na r-wartość}

\begin{frame}

  \frametitle{Konwersja z l-wartości na r-wartość}

  L-wartość może być poddana standardowej konwersji do r-wartości.

  \vspace{0.5cm}

  Na przykład, operator \code{+} dla typu \code{int} wymaga r-wartości
  jako swoich operandów, dlatego poniższy przykład jest poprawny, bo
  l-wartości, którymi są wyrażenia \code{x} i \code{y}, zostaną
  poddane konwersji do r-wartości.

  \vspace{0.5cm}

  \code{int x, y;}

  \code{x + y;}

  \vspace{0.5cm}

  Nie ma niejawnej konwersji z r-wartości do l-wartości.

\end{frame}

%************************************************************************

\subsection{Przykład: operator ++}

\begin{frame}

  \frametitle{Przykład: operator \code{++}}

  Operator inkrementacji (\code{++}) jako argumentu wymaga
  \red{l-wartości}.  Wyrażenie z operatorem \code{++} jest:

  \begin{itemize}
  \item \red{l-wartością} dla operatora prefixowego, np.~\code{++i},
    bo operator wykonuje działanie na obiekcie \code{i}, a potem
    zwraca l-referencję na ten obiekt,
  \item \red{r-wartością} dla operatora sufixowego, np.~\code{i++}, bo
    operator tworzy kopię obiektu \code{i}, wykonuje działanie na
    obiekcie \code{i}, a potem zwraca stworzoną kopię obiektu.
  \end{itemize}

  Dlatego \code{++++i} kompiluje się, a \code{i++++} już nie.
  
\end{frame}

%************************************************************************

\subsection{Obiekty tymczasowe}

\begin{frame}

  \frametitle{Obiekty tymczasowe}

  Obiekt tymczasowy (ang.~temporary) jest tworzony przy:

  \begin{itemize}
    \item opracowywaniu wyrażenia: \code{1 + 2, string("T") + "4";}
    \item przekazywaniu argumentu wywołania funkcji:\\
      \code{void foo(const A \&);}\\
      \code{foo(A());}
    \item zwracaniu wartości funkcji: \code{string x = foo();}
    \item rzucaniu wyjątku: \code{throw A();}
  \end{itemize}

  \vspace{0.25cm}

  Obiekty tymczasowe w C++98 były zawsze kopiowane.

  \vspace{0.25cm}

  Obiekty tymczasowe w C++11 mogą być \emph{przenoszone}, bo
  wyrażenia, w których są tworzone (np.~jako argument wywołania
  funkcji) są r-wartością, którą można wskazać r-referencją.

\end{frame}

%************************************************************************

\subsection{Funkcje a kategorie wartości wyrażeń}

\begin{frame}

  \frametitle{Funkcje a kategorie wartości wyrażeń}

  Funkcja o nazwie \code{foo} może być użyta w wyrażeniu na dwa
  sposoby:

  \begin{itemize}
  \item użycie tylko nazwy:
    \begin{itemize}
    \item przykładowe wyrażenie: \code{foo},
    \item w tym przypadku \code{foo} jest l-wartością, bo na nazwę,
    \item możemy pobrać adres l-wartości, więc \code{&foo} jest OK,
    \end{itemize}
  \item wywołanie funkcji:
    \begin{itemize}
    \item przykładowe wyrażenie: \code{foo(argumenty)},
    \item kategoria wartości wyrażenia wywołania funkcji zależy od
      typu wartości zwracanej przez funkcję:
      \begin{itemize}
      \item jeżeli typem jest l-referencja, to wyrażenie jest
        l-wartością, np.: jeżeli \code{int &foo();}, to \code{foo()}
        jest l-wartością,
      \item jeżeli typ nie jest referencyjny, to wyrażenie jest
        r-wartością: np.: jeżeli \code{int foo();}, to \code{foo()}
        jest r-wartością.
      \end{itemize}
    \end{itemize}
  \end{itemize}

\end{frame}

%************************************************************************

\subsection{Typy niepełne a kategorie wartości wyrażeń}

\begin{frame}[fragile]

  \frametitle{Typy niepełne a kategorie wartości wyrażeń}

  Jeżeli typ nie został w pełni zdefiniowany, bo został jedynie
  zadeklarowany, albo częściowo zdefiniowany jako klasa abstrakcyjna,
  to typ taki nazywamy \red{typem niepełnym} (ang.~incomplete type).

  \vspace{0.25 cm}

  Wyrażenia typu niepełnego mogą mieć tylko kategorię l-wartość.

  \vspace{0.25 cm}

  {\scriptsize
  \lstinputlisting[]{incomplete.cc}
  }

\end{frame}

%************************************************************************

\section{Koniec}

\subsection{Podsumowanie}

\begin{frame}

  \frametitle{Podsumowanie}

  \begin{itemize}

  \item Kategoria wartości odnosi się do wyrażenia, a nie wartości
    pewnego typu (np.~klasy A albo typu \code{int}).

  \item Wartość pewnego typu (np.~klasy A albo typu \code{int}) nie ma
    kategorii wartości.

  \item Kategoria wartości wyrażenia określa, jakie operacje można
    dalej wykonać na wyrażeniu.

  \item Każde wyrażenie jest l-wartością albo r-wartością.

  \end{itemize}

\end{frame}
