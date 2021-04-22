---
title: Uogólnienie callable
---

# Callable a czas kompilacji czy uruchomienia

Callable może być określone (przez podanie referencji, wskaźnika czy
obiektu) w czasie **uruchomienia**, albo **kompilacji**.

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
też brak narzutu wydajnościowego użycia domknięcia, co można sprawdzić
z użyciem Code Explorer lub narzędziem `objdump`.

{% highlight c++ %}
{% include_relative compile2.cc %}
{% endhighlight %}

# Typ przyjmowanego callable

Typ przyjmowanego (przez funkcję czy konstruktor) callable określamy
jako typ parametru funkcji czy konstruktora.  Ten typ możemy
zdefiniować na trzy sposoby: *dokładnie*, z użyciem *`std::function`*,
lub *szablonowo*.

## Dokładnie zdefiniowany typ callable

Możemy dokładnie określić typ przyjmowanego callable jako typ
wskaźnika lub referencji na funkcję, jak w przykładzie niżej.  Co
ciekawe, wyrażenie z domknięciem (w przykładzie jest to `[]{cout <<
"World!\n";}`) może być niejawnie rzutowane na wskaźnik na funkcję
domknięcia, dlatego ten przykład się kompiluje.

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

Dwie ważne funkcjonalności `std::function`:

* Obiekt klasy `std::function` opakowuje i przechowuje przez wartość
  przekazany callable (więc callable jest kopiowany), udostępniając
  ujednolicony interfejs (jeden składowy operator wywołania)
  niezależny od typu przechowywanego callable.

* Obiekt klasy `std::function` może mieć zmieniany callable w czasie
  uruchomienia; te callable mogą mieć różne typy, ale muszą mieć ten
  sam interfejs.

Ta funkcjonalność `std::function` niestety jest okupiona narzutem
wydajnościowym pośredniego wywołania i kopiowania callable.  Jeżeli
tej funkcjonalności nie potrzebujemy, to nie powinniśmy używać
`std::function`.

{% highlight c++ %}
{% include_relative passing3.cc %}
{% endhighlight %}

## Szablonowy typ callable

Typ callable może być parametrem szablonu.  Wtedy na etapie kompilacji
funkcja jest konkretyzowana dla tego konkretnego callable, co
przekłada się na maksymalną wydajnośc, bo kod wynikowy generowany jest
"na miarę".

Użycie szablonu nie wyklucza użycie `std::function`, która może być po
prostu argumentem szablonu.

{% highlight c++ %}
{% include_relative passing4.cc %}
{% endhighlight %}

## Wydajność

Przykład niżej demonstruje wydajność użycia różnego rodzaju callable
dla kolejki priorytetowej i sortowania.  Proszę skompilować program z
opcją `-O3` i porównać wyniki.

{% highlight c++ %}
{% include_relative timing.cc %}
{% endhighlight %}

# Funkcja składowa klasy

Funkcja składowa klasy też jest callable, ale do jej wywołania
potrzebujemy dodatkowo **obiektu**, na rzecz którego funkcja będzie
wywołana.  Funkcję składową możemy wywołać przez nazwę tak: `o.f()`
albo `p->f()`, gdzie `o` jest nazwą obiektu, `p` jest wskaźnikiem na
obiekt, a `f` jest nazwą funkcji składowej, którą możemy wywołać bez
argumentów.

Używając wskaźnika możemy przekazać funkcję składową jako callable.  W
odróżnieniu od zwykłych funkcji, nie ma referencji na funkcję
składową.  Typ wskaźnika na funkcję składową jest podobny do typu
wskaźnika na funkcję, ale deklarator `*` poprzedzamy zakresem klasy,
np. `A::`.  Adres funkcji składowej pobieramy operatorem adresowania,
np. `&A::foo`.

Składnia wywołania funkcji składowej przez wskaźnik nieco się różni od
składni wywołania funkcji.  Składnia jest taka: `(o.*p)(lista
argumentów)`, gdzie `o` jest obiektem, a `p` wskaźnikiem na funkcję
składową.  Ta różnica to dodatkowe nawiasy wokół `o.*p`, które są
potrzebne, bo `o.*p(lista argumentów)` mogłoby sugerować też znaczyć
wywołania funkcji przez wskaźnik

Użycie wkaźnika na funkcję składową jest zaawansowaną
funkcjonalnością, którą raczej rzadko się stosuje i tylko w
programowaniu obiektowym.

{% highlight c++ %}
{% include_relative member.cc %}
{% endhighlight %}

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
