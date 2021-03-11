---
title: Specjalizacja szablonów
---

Wprowadzenie
============

Szablon funkcji czy klasy może być **specjalizowany**.  Specjalizujemy
**szablon podstawowy**.  Szablon podstawowy deklaruje albo definiuje
funkcję albo klasę oraz parametry szablonu (liczbę i rodzaj
parametrów).  Specjalizacja szablonu też jest szablonem, ale już dla
argumentów określonych częściowo albo całkowicie.  Specjalizację
możemy poznać po nieco innej składni szablonu, ale ciągle występuje
słowo kluczowe `template`.

Specjalizacja może być **częściowa** (ang. partial specialization)
albo **całkowita** (ang. complete specialization).  Specjalizacja
szablonu funkcji nie może być częściowa, może być tylko całkowita.
Specjalizacja szablonu klasy może być częściowa albo pełna.

W przykładzie niżej różne funkcjonalności funkcji `foo` w zależności
od typu parametru zostały osiągnięte przez przeciążenia funkcji:

{% highlight c++ %}
{% include_relative generic1.cc %}
{% endhighlight %}

To samo zadanie możemy rozwiązać z użyciem szablonu i specjalizacji
dla typów `A` i `B`:

{% highlight c++ %}
{% include_relative generic2.cc %}
{% endhighlight %}

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu dla `N = 0`.
Nie ma *częściowej specjalizacji* szablonu funkcji, jest tylko *pełna
specjalizacja*, więc musimy jawnie podać także argument szablonu dla
parametru `T`, czyli `int`.

{% highlight c++ %}
{% include_relative print4.cc %}
{% endhighlight %}

# Składnia

# Podsumowanie

# Quiz

<!-- LocalWords: lvalue lvalues rvalue -->
