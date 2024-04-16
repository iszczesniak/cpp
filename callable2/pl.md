---
title: Uogólnienie wyrażeń wywołania
---

# Wprowadzenie

Chielibyśmy, żeby wyrażenia wywołania mogły użyć:

* dowolnego callable w czasie kompilacji bez utraty wydajności,

* dowolnego callable w czasie uruchomienia, niestety już ze stratą
  wydajności,

* także funkcji składowej jako callable.

# Czas kompilacji czy uruchomienia

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

Użycie szablonu nie wyklucza użycia `std::function`, która może być po
prostu argumentem szablonu.

{% highlight c++ %}
{% include_relative passing4.cc %}
{% endhighlight %}

# Funkcja składowa klasy

Funkcja składowa klasy też jest callable, ale do jej wywołania
potrzebujemy dodatkowo **obiektu**, na rzecz którego funkcja będzie
wywołana.  Funkcję składową `f` możemy wywołać przez nazwę tak:
`o.f(lista argumentów)`, gdzie `o` jest nazwą obiektu, albo
`p->f(lista argumentów)`, gdzie `p` jest wskaźnikiem na obiekt.

Funkcję składową możemy przekazać, ale tylko przez wskaźnik, bo nie ma
referencji na funkcję składową, chociaż referencja do zwykłej funkcji
jest.  Typ wskaźnika na funkcję składową jest podobny do typu
wskaźnika na funkcję, ale deklarator `*` poprzedzamy zakresem klasy,
np. `A::`.  Adres funkcji składowej pobieramy operatorem adresowania,
np. `&A::foo`, bo nazwa funkcji składowej nie rozpadnie się
(ang. decay) na wskaźnik do niej (takiego rozpadu nie ma).

Składnia wywołania funkcji składowej przez wskaźnik nieco się różni od
składni wywołania funkcji.  Składnia jest taka: `(o.*p)(lista
argumentów)`, gdzie `o` jest obiektem, a `p` wskaźnikiem na funkcję
składową.  Ważne są nawiasy wokół `o.*p` i miejsce operatora
wyłuskania.

Przykład niżej pokazuje także użycie `std::function` razem ze
wskaźnikiem na funkcję składową.  Musimy użyć funkcji `std::bind`,
żeby przekazać obiekt, na rzecz którego funkcja będzie wywoływana.

{% highlight c++ %}
{% include_relative pointer-to-member.cc %}
{% endhighlight %}

Tę składnię łatwo pomylić ze składnią wywołania funkcji, do której
wskaźnik jest przechowywany jako pole składowe obiektu.  Oto przykład:

{% highlight c++ %}
{% include_relative member-pointer.cc %}
{% endhighlight %}

Użycie wkaźnika na funkcję składową jest zaawansowaną
funkcjonalnością, którą oczywiście stosuje się wyłącznie w
programowaniu obiektowym, ale którą także uwzględniono w programowaniu
uogólnionym, w funkcji `std::invoke`.

# `std::invoke`

Funkcja `std::invoke` wywołuje callable z użyciem podanych argumentów.
Wszystkie argumenty `std::invoke` są doskonale przekazywane.  Na
pierwszy rzut oka ta funkcja robi to samo, co zwykłe wywołanie
callable.  Oto przykład:

{% highlight c++ %}
{% include_relative invoke1.cc %}
{% endhighlight %}

Dlaczego więc wprowadzono tę funkcję?  Bo pozwala także na wywołanie
składowej klasy. Funkcja wprowadza ujednolicony sposób wywołania
dowolnego callable, co jest potrzebne w programowaniu uogólnionym.

Argumentami `std::invoke` przy wywołaniu funkcji składowej kolejno są:

* wskaźnik na funkcję składową,

* obiekt na rzecz którego wywoływana jest funkcja składowa,

* argumenty dla funkcji składowej.

Oto przykład:

{% highlight c++ %}
{% include_relative invoke2.cc %}
{% endhighlight %}

W przykładzie niżej, funkcja `f` wywołuje otrzymany callable, którym
może być także wskaźnik na funkcję składową.  Zaimplementowanie takiej
funkcjonalności samemu byłoby dosyć trudne, a my to osiągnęliśmy
jedynie korzystając z funkcji `std::invoke.`

{% highlight c++ %}
{% include_relative invoke3.cc %}
{% endhighlight %}

W przykładzie wyżej użyliśmy **szablonu wariadycznego**, żeby funkcja
`f` mogła przyjąć dowolną (także zerową) liczbę argumentów dla
wywoływanego callable.  Szablony wariadyczne, które jedynie wspominamy
tutaj, posiadają wiele szczegółów, ale najważniejszą cechą jest
posiadanie **dowolnej liczby parametrów**.

Są dwa problemy powyższego przykładu związane z użyciem `std::invoke`:

* konieczność użycia szablonu wariadycznego, co jest trudne i dlatego
  niewygodne,

* po argumentach dla callable nie można przekazać innych argumentów,
  bo wszysto do końca jest traktowane jako argumenty dla callable.

# `std::apply`

Funkcja `std::apply` pozwala na wywołanie dowolnego callable:

* bez użycia szablonu wariadycznego,

* z możliwością podania dodatkowych argumentów po argumentach dla
  callable.

Rozwiązanie jest proste: argumenty są przekazywane w krotce.  Krotkę
tworzymy z użyciem funkcji `std::forward_as_tuple`, żeby zachować
kategorię wartości wyrażeń elementów krotki.  Jeżeli wywołujemy
funkcję składową, to pierwszym elementem krotki powinien być obiekt,
na rzecz którego callable będzie wywołana.

{% highlight c++ %}
{% include_relative apply.cc %}
{% endhighlight %}

Funkcje `std::invoke`, `std::apply` i `std::forward_as_tuple` są
mechanizmami czasu kompilacji i nie wprowadzają żadnego narzutu
czasowego i pamięciowego.

# Przeciążenia

Niestety nie udało mi się użyć funkcji `std::invoke` i `std::apply` z
przeciążeniami:

{% highlight c++ %}
{% include_relative overloads.cc %}
{% endhighlight %}

# Doskonałe przekazywanie

Callable powinniśmy doskonałe przekazywać (może lepiej: doskonale
wywoływać).  Funkcji (`f` w przykładzie niżej) przekazujemy callable
jako argument, a funkcja powinna zachować kategorię wartości argumentu
przy wywoływaniu otrzymanego callable.  Zachowanie kategorii nie ma
znaczenia, kiedy przekazywana jest funkcja (bo funkcja zawsze jest
l-wartością), ale ma znaczenie, kiedy przekazujemy funktor albo
domknięcie, bo wtedy argument może być l-wartością albo r-wartością.

{% highlight c++ %}
{% include_relative forwarding.cc %}
{% endhighlight %}

# Podsumowanie

* Callable może być określane w czasie kompilacji albo uruchomienia.

* Do wywołania otrzymanego callable najlepiej jest użyć `std::invoke`.

* Typ `std::function` jest narzędziem czasu uruchomienia.

* Szablony funkcji `std::invoke` i `std::apply` są narzędziami czasu
  kompilacji.

# Quiz

* Do czego służy `std::function`?

* Jaka jest różnica między zwykłym wywołaniem funkcji, a wywołaniem z
  użyciem funkcji `std::invoke`?

* Jaka jest różnica między funkcjami `std::invoke` and `std::apply`?

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
