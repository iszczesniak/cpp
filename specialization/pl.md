---
title: Specjalizacja szablonów
---

Wprowadzenie
============

Możemy **specjalizować** szablon funkcji czy klasy.  Szablon, który
specjalizujemy nazywamy **szablonem podstawowy**, żeby odróżnić go od
specjalizacji, która też jest szablonem.  Specjalizacja nadpisuje
definicję szablonu podstawowego.  Nie da się specjalizować dalej
specjalizacji.

Szablon podstawowy deklaruje albo definiuje funkcję albo klasę oraz
parametry szablonu (liczbę i rodzaj parametrów).  Specjalizacja musi
mieć tę samą nazwę (klasy albo funkcji) i dostarczyć argumentów dla
specjalizowanego szablonu podstawowego.

Specjalizacja szablonu też jest szablonem, ale już dla częściowo albo
całkowicie określonych argumentów.  Specjalizację możemy poznać po
nieco innej składni szablonu, ale ciągle występuje słowo kluczowe
`template`.

Specjalizacja może być **częściowa** (ang. partial specialization)
albo **całkowita** (ang. complete specialization).  Specjalizacja
szablonu funkcji nie może być częściowa, może być tylko całkowita.
Specjalizacja szablonu klasy może być częściowa albo pełna.

# Specjalizacja szablonu funkcji

Szablon funkcji może być tylko całkowicie specjalizowany, dlatego
szablon specjalizacji nie ma parametrów: lista jest pusta.

Deklaracje i definicje szablonów rozpoczynają się słowem kluczowym
`template` z taką składnią:

```
template <>
```


W przykładzie niżej różne funkcjonalności funkcji `foo` w zależności
od typu parametru zostały osiągnięte przez przeciążenia funkcji:

{% highlight c++ %}
{% include_relative generic1.cc %}
{% endhighlight %}

To samo zadanie możemy rozwiązać z użyciem szablonu i specjalizacji
dla typów `A` i `B`, jak w przykładzie niżej.  

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
