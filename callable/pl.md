---
title: Callable, coś do wywołania
---

# Wprowadzenie

W języku C sposobem na dostarczenie fragmentu kodu (np. ustalającego
porządek między elementami) do wywołania przez jakiś inny fragment
kodu (np. funkcję sortującą) jest dostarczenie wskaźnika na funkcję do
wywołania.  W C++ uogólnieniem wskaźnika na funkcję jest "coś", co
możemy wywołać, co z angielskiego jest nazywane *callable*.  Wywołanie
callable ma ustaloną składnię (czyli składnię wyrażenia wywołania) i
określony interfejs, czyli jakiego typu są argumenty i wynik callable.

Uogólnienie ma na celu:

* pominięcie pośredniego (czyli przez wskaźnik) wywołania funkcji, na
  rzecz wkompilowania (ang. inlining) funkcji w miejsce wywołania,

* możliwość dostarczenia dodatkowych danych do obliczeń, czego nie
  jesteśmy w stanie wykonać ze wskaźnikiem na funkcję.

Biblioteka standardowa używa (przekazuje, zapisuje jako pole składowe)
callable **przez wartość**, więc **kopiowanie callable powinno być
szybkie**.  Callable przekazywane do standardowych algorytmów,
np. `std::sort`, i standardowych kontenerów,
np. `std::priority_queue`, powinno się szybko kopiować.  To oznacza,
że callable nie powinno posiadać dużo danych do skopiowania.

Callable używamy najczęściej przez wartość, tak jak robi to biblioteka
standardowa, ale można też używać callable przez referencję albo
wskaźnik.

## Motywacja

W poniższym sortowaniu porównywane są liczby całkowite, dla których
jest ustalony porządek (liniowy) z użyciem operatora `<`:

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

W przykładzie niżej sortujemy obiekty typu klasowego.  Żeby kompilacja
powiodła się, musimy zdefiniować porządek z użyciem **operatora
porównania**, czyli **operatora `<`**.  Operator zdefiniowaliśmy jako
funkcję składową, która drugi operand operatora `<` przyjmuje jako
argument wywołania funkcji (pierwszym operandem jest obiekt `*this`).
Składowy operator porównania powinien być stały (bo nie powinien
zmieniać pierwszego operandu) i powinien pobierać drugi operand przez
referenceję stałą (bo nie powinien zmieniać drugiego operandu).

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Funkcja `std::sort` używa operatora `<`, jeżeli nie przakażemy jej
callable porównania jako ostatni argument wywołania.  Możemy uzyskać
identyczny efekt jak w przykładzie wyżej, jeżeli przekażemy jako
callable obiekt struktury `std::less<A>`, która używa operatora `<`.

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

Możemy sortować w kolejności rosnącej, jeżeli użyjemy *funktora*
struktury `std::greater`.  Struktura `std::greater` używa operatora
`>`, więc musimy go zdefiniować, zamiast operatora `<`.

{% highlight c++ %}
{% include_relative motivation4.cc %}
{% endhighlight %}

Nie musimy jednak polegać na operatorze `<`.  Funkcji `std::sort`
możemy przekazać callable, na czym możemy wykonać operator wywołania
`()`.  Callable może być przekazywane przez wartość albo referencję.

Callable może być przekazywany nie tylko funkcji, ale też
konstruktorowi, który może przechować callable w polu składowym.  Tak
robi, na przykład, kolejka priorytetowa biblioteki standardowej
(`std::priority_queue`).

Poniżej jest nasz roboczy przykład z kolejką priorytetową, który
będziemy dalej zmieniać.

{% highlight c++ %}
{% include_relative pq.cc %}
{% endhighlight %}

# Typy callable

Callable może być:

* wskaźnikiem na funkcję,

* funktorem.

## Wskaźnik na funkcję

Wyrażenie, które jest tylko nazwą funkcji (bez operatora wywołania)
traktowane jest jako adres tej funkcji.  Używając tego adresu możemy
wywołać funkcję.  Jedyne operacje możliwe na wskaźniku do funkcji to:
pobranie adresu funkcji i wywołanie funkcji.

{% highlight c++ %}
{% include_relative function.cc %}
{% endhighlight %}

Domyślnie kolejka priorytetowa zwraca największy element.  W
przykładzie niżej przekazujemy wskaźnik na funkcję porównującą, żeby
ustalić porządek rosnący w kolejce priorytetowej.

{% highlight c++ %}
{% include_relative pq_foo.cc %}
{% endhighlight %}

## Funktor

Funktor to obiekt, który ma zdefiniowany operator wywołania `()`
(ang. call operator).  Zaletą funktora, w porównaniu z funkcją, jest
możliwość przekazania dodatkowych danych, która są przechowywane w
polach składowych funktora.

W najprostszym przypadku, funktor może pełnić rolę funkcji.  Na
przykład, domyślnie kolejka priorytetowa zwraca największy element, bo
do porównania używa klasy funktora \code{std::less<T>}.  Poniżej
użyjemy funktora klasy \code{std::greater<T>}, żeby kolejka zwracała
najmniejszy element.

{% highlight c++ %}
{% include_relative pq_ro.cc %}
{% endhighlight %}

Możemy także zdefiniować własny typ funktora:

{% highlight c++ %}
{% include_relative pq_fo1.cc %}
{% endhighlight %}

W tym przykładzie w czasie uruchomienia przekazujemy konstruktorowi
funktora argument (dodatkową daną do obliczeń), który mówi o porządku
(rosnącym bądź malejącym):

{% highlight c++ %}
{% include_relative pq_fo2.cc %}
{% endhighlight %}

### Domknięcie

Domknięcie (ang. closure) jest funktorem, który jest wynikiem
opracowania wyrażenia lambda.

{% highlight c++ %}
{% include_relative pq_lambda1.cc %}
{% endhighlight %}

A tu wersja z dodatkowym argumentem domknięcia przekazywanym w czasie
uruchomienia:

{% highlight c++ %}
{% include_relative pq_lambda2.cc %}
{% endhighlight %}

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

Dwie ważne funkcjonalności `std::function`:

* Obiekt klasy `std::function` opakowuje i przechowuje przez wartość
  przekazany callable (więc callable jest kopiowany), udostępniając
  ujednolicony interfejs (jeden składowy operator wywołania)
  niezależny od typu przechowywanego callable.

* Obiekt klasy `std::function` może mieć zmieniany callable w czasie
  uruchomienia, a te callable mogą mieć różne typy.

Ta funkcjonalność `std::function` niestety jest okupiona narzutem
wydajnościowym pośredniego wywołania i kopiowania callable.  Jeżeli
tej funkcjonalności nie potrzebujemy, to nie używamy `std::function`.

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

# Wydajność

Przykład niżej demonstruje wydajność użycia różnego rodzaju callable
dla kolejki priorytetowej i sortowania.  Proszę skompilować program z
opcją `-O3`.

{% highlight c++ %}
{% include_relative timing.cc %}
{% endhighlight %}

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
