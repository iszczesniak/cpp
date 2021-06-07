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

Implementujemy fabrykę, która zwraca `shared_ptr` do pewnych danych,
które mogą być bardzo duże.  Fabryka powinna:

* stworzyć nowe dane, jeżeli nie istnieją,

* użyć wcześniej stworzone dane, jeżeli jeszcze istnieją.

Fabryka powinna śledzić stworzone dane (bez posiadania ich) i
ewentualnie ich użyć.  Istnienie danych zależy od sposobu ich użycia
przez kod wywołujący fabrykę, czyli od tego, czy kiedy obiekty
`shared_ptr` są niszczone.

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

## How it works

The control data structure of the shared pointer group is also used by
the weak pointers, which also belong to the group, but without
claiming ownership.

Just as a shared pointer, a weak pointer has a raw pointer to the
control data structure.

A managing structure not only has a reference count, but also a *weak
count*, which keeps the number of weak pointers.

We know that the managed data is destroyed, when the reference count
reaches zero.

The control data structure is destroyed when both the reference count
and the weak count reach zero.

# The implementation of the motivating example

Here's the implementation:

{% highlight c++ %}
{% include_relative factory.cc %}
{% endhighlight %}

## Performance

A weak pointer takes twice as much memory as a raw pointer, because it
has:

* the raw pointer to the managed data,

* the raw pointer to the control data structure.

What do we need the raw pointer to the managed data for if we cannot
access it directly?  Beause it will be needed to produce a shared
pointer.

As for a shared pointer, the same applies to a raw pointer: the raw
pointer to the managed data could be a part of the control data
structure, but getting to the managed data would be slower, because an
extra indirect access would be needed.

# Conclusion

* A weak pointer tracks the managed data without claiming the
  ownership.

* We *always* produce a weak pointer from a shared pointer.

* We can produce a shared pointer from a weak pointer if possible,
  i.e., if the managed data exist.

* A weak pointer never destroys the managed data.

# Quiz

* What do we need type `weak_ptr` for?

* What's the difference between `shared_ptr` and `weak_ptr`?

* Can we create an object of type `weak_ptr` based on an object of
  type `unique_ptr`?

{% include rid %}

<!-- LocalWords: inlined multithreaded -->
<!-- LocalWords: performant rvalue suboptimal -->
