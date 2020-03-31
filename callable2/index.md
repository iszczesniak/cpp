---
title: Callable - kontynuacja
---

# Wprowadzenie

Callable jest wykorzystywane jako metoda dostarczenia fragmentu kodu
do innego miejsca kodu.  Wywołanie callable ma ustaloną składnię
(czyli składnię wyrażenia wywołania) i określony interfejs, czyli
jakiego typu są argumenty i wynik callable.

Biblioteka standardowa używa (przekazuje, zapisuje jako pole składowe)
callable **przez wartość**, więc **kopiowanie callable powinno być
szybkie**.  Callable przekazywane do standardowych algorytmów,
np. `std::sort`, i standardowych kontenerów,
np. `std::priority_queue`, powinno się szybko kopiować.  To oznacza,
że callable nie powinno posiadać dużo danych do skopiowania.

Callable używamy najczęściej przez wartość, tak jak robi to biblioteka
standardowa, ale można też używać callable przez referencję albo
wskaźnik.

# Callable a czas kompilacji czy uruchomienia

Callable może być określone (o który callable dokładnie chodzi) w
czasie **uruchomienia**, albo **kompilacji**.

## Callable w czasie uruchomienia

Jeżeli callable jest ustalane w czasie uruchomienia, to kod callable
będzie wywołany i nie będzie wkompilowany (ang. inlined) w miejsce
wywołania, no bo nie wiadomo co wkompilować.  Proszę sprawdzić kod
wynikowy przykładu niżej (z Code Explorer lub z użyciem narzędzia
`objdump`).

{% highlight c++ %}
{% include_relative run.cc %}
{% endhighlight %}

## Callable w czasie kompilacji

Jeżeli w czasie kompilacji callable jest znane i nie zmienia się w
czasie uruchomienia, to może ono być wkompilowane w miejscu wywołania.
Jeżeli chcemy użyć inne callable, to musimy zmienić kod źródłowy.  Oto
przykład:

{% highlight c++ %}
{% include_relative compile1.cc %}
{% endhighlight %}

Przykład niżej pokazuje wkompilowanie domknięcia.  Przykład pokazuje
też brak narzutu wydajnościowego użycia domknięcia.

{% highlight c++ %}
{% include_relative compile2.cc %}
{% endhighlight %}

# Typ przyjmowanego callable

Typ przyjmowanego callable określamy jako typ parametru funkcji czy
konstruktora.  Ten typ możemy zdefiniować *dokładnie*, z użyciem
*`std::function`*, lub *szablonowo*.

## Dokładnie zdefiniowany typ callable

Możemy dokładnie określić typ przyjmowanego callable jako typ
wskaźnika na funkcję, jak w przykładzie niżej.  Co ciekawe, wyrażenie
z domknięciem (w przykładzie jest to `[]{cout << "World!\n";}`) może
być niejawnie rzutowane na wskaźnik na funkcję domknięcia, dlatego ten
przykład się kompiluje.

{% highlight c++ %}
{% include_relative passing1.cc %}
{% endhighlight %}

Możemy też określić typ przyjmowanego callable jako konkretny typ
funktora.

{% highlight c++ %}
{% include_relative passing2.cc %}
{% endhighlight %}

## `std::function` jako callable

Klasa szablonowa `std::function` dale możliwość przekazywania
dowolnego callable: wskaźnika, funktora czy domknięcia, pod warunkiem,
że callable ma wymagane typy parametrów i wyniku, które podajemy jako
argument szablonu.

Obiekt klasy `std::function` opakowuje i przechowuje przez wartość
przekazany callable (więc callable jest kopiowany), udostępniając
ujednolicony interfejs (jeden składowy operator wywołania) niezależnie
od typu przechowywanego callable.

Obiekt klasy `std::function` może mieć zmieniany callable w czasie
uruchomienia, a te callable mogą mieć różne typy.

{% highlight c++ %}
{% include_relative passing3.cc %}
{% endhighlight %}

## Szablonowy typ callable

`std::function` może być też argumentem szablonu.

<!-- LocalWords: callable -->
