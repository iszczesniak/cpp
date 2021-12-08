---
title: std::weak_ptr
---

# Wprowadzenie

Mamy gwarancję, że zarządzane dane istnieją tak długo, jak długo
przynajmniej jeden wskaźnik inteligentny `shared_ptr` nimi
zarządzadza.  Tej gwarancji jednak nie zawsze potrzebujemy.  Czasami
wystarczy nam możliwości sprawdzenia czy zarządzane dane istnieją i,
jeżeli trzeba, bezpiecznego użycia ich.  Można powiedzieć, że
wystarczy nam *śledzenie danych* bez posiadania własności, czyli nie
wymagamy, aby dane istniały.

W C++ tę funkcjonalność dostarcza **słaby inteligentny wskaźnik**,
który jest zaimplementowany przez szablon klasy `std::weak_ptr`.
Funkcjonalność słabego wskaźnika jest powiązana ze wskaźnikiem typu
`share_ptr`, ponieważ słaby wskaźnik w pewien niepełny sposób
współdzieli zarządzane dane.  Poniższy przykład ilustruje i motywuje
potrzebę słabego wskaźnika.

# Motywacja

Implementujemy fabrykę zwracającą dane, które mogą być bardzo duże.
Fabryka powinna:

* stworzyć nowe dane, jeżeli nie istnieją,

* użyć wcześniej stworzonych danych, jeżeli jeszcze istnieją.

Fabryka powinna śledzić stworzone dane (bez posiadania ich) i
ewentualnie ich użyć.  Istnienie danych zależy od sposobu ich użycia
przez kod wywołujący fabrykę, czyli od tego, kiedy współdzielone
wskaźniki są niszczone.

Fabrykę najlepiej zaimplementować z użyciem słabych wskaźników.  Zanim
przedstawimy implementację fabryki, pierwsze omówimy podstawy słabych
wskaźników.

# Szczegóły

## `std::weak_ptr`

* `#include <memory>`

* Od C++11

* Szablon klasy, którego argumentem jest typ śledzonych danych.

* Słaby wskaźnik może być kopiowany i przenoszony, ale nie jest to
  takie ważne, jak przy `unique_ptr` i `shared_ptr`.

* Słaby wskaźnik jest tworzony od współdzielonego wskaźnika.

* Słaby wskaźnik nigdy nie niszczy zarządzanych danych.

* Żeby odwołać się do danych słabego wskaźnika, musimy stworzyć
  współdzielony wskaźnik.  Uda się, jeżeli dane istnieją.

* Zarządzane dane nie wiedzą, że są zarządzane, czyli typ zarządzanych
  danych nie musi być przygotowany w jakiś specjalny sposób, na
  przykład nie musi być wyprowadzony z jakiejś klasy bazowej.

## Użycie

Przykład niżej demonstruje użycie wskaźnika:

{% highlight c++ %}
{% include_relative basic.cc %}
{% endhighlight %}

## Tworzenie współdzielonego wskaźnika ze słabego wskaźnika

Problem.  W jaki sposób bezpiecznie (czyli bez zjawiska hazardu) użyć
dane słabego wskaźnika, jeżeli one istnieją?  Nawet jeżeli
sprawdziliśmy, że dane ciągle istnieją (używając funkcji `expired`),
to nie możemy użyć surowego wskaźnika, ponieważ może on już być
nieaktualny.  Na szczęście, `weak_ptr` nie pozwala na dostęp do
surowego wskaźnika, tak jak pozwalają na to `unique_ptr` i
`shared_ptr`, czyli z użyciem operatora wyłuskania (`operator *`),
operatora dostępu do składowej przez wskaźnik (`operator ->`) czy
funkcji `get`.

Rozwiązanie.  Zabezpiecz zarządzane dane (pozyskaj spółdzieloną
własność) poprzez stworzenie współdzielonego wskaźnika ze słabego
wskaźnika.  Możemy to zrobić na dwa sposoby:

* wywołać konstruktor `shared_ptr` ze słabym wskaźnikiem; konstruktor
  rzuci wyjątek, jeżeli dane słabego wskaźnika już nie istnieją,

* wywołać funkcję (składową słabego wskaźnika) `lock`, która zwróci
  współdzielony wskaźnik; współdzielony wskaźnik będzie pusty, jeżeli
  zarządzane dane już nie istnieją.

Oto przykład:

{% highlight c++ %}
{% include_relative snatch.cc %}
{% endhighlight %}

## Jak to działa

Struktura sterująca grupy współdzielonych wskaźników jest także
używana przez słabe wskaźniki, które także należą do grupy, ale bez
posiadania własności.

Struktura sterująca posiada nie tylko licznik odwołań (który
przechowuje liczbę współdzielonych wskaźników), ale także **licznik
słabych odwołań**, który przechowuje liczbę słabych wskaźników.

Wiemy, że dane zarządzane są niszczone, kiedy licznik odwołań osiągnie
zero.  Z kolei struktura sterująca jest niszczona, kiedy licznik
odwołań i licznik słabych odwołań osiągną zero.

# Implementacja przykładu motywującego

Oto implementacja:

{% highlight c++ %}
{% include_relative factory.cc %}
{% endhighlight %}

## Wydajność

Słaby wskaźnik zabiera dwa razy więcej pamięci, niż surowy wskaźnik,
ponieważ słaby wskaźnik posiada jako pola składowe:

* surowy wskaźnik do zarządzanych danych,

* surowy wskaźnik do struktury sterującej.

Dlaczego przechowywany jest surowy wskaźnik do zarządzanych danych,
skoro i tak nie mamy do niego dostępu?  Ponieważ jest potrzebny przy
tworzeniu współdzielonego wskaźnika.

Wiemy, że z powodu wydajności współdzielonych wskaźników, surowy
wskaźnik do zarządzanych danych nie może być częścią struktury
sterującej.  Tak więc słaby wskaźnik musi przechowywać ten surowy
wskaźnik jako swoje pole składowe.

# Podsumowanie

* Słaby wskaźnik śledzi zarządzane dane, ale ich nie posiada.

* Słaby wskaźnik zawsze tworzymy ze współdzielonego wskaźnika.

* Możemy stworzyć współdzielony wskaźnik ze słabego wskaźnika, jeżeli
  zarządzane dane ciągle istnieją.

* Słaby wskaźnik nigdy nie niszczy danych.

# Quiz

* Dlaczego potrzebujemy `weak_ptr`?

* Jaka jest różnica między `shared_ptr` i `weak_ptr`?

* Czy możemy stworzyć wskaźnik `weak_ptr` na podstawie wskaźnika
  `unique_ptr`?

{% include rid_pl %}

<!-- LocalWords: -->
