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
{% include_relative motivation1.cc %}
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

<!-- LocalWords: callable inlined -->
