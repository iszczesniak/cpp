---
title: Callable, coś do wywołania
---

# Wprowadzenie

W języku C sposobem na dostarczenie fragmentu kodu (np. ustalającego
porządek między elementami) do wywołania przez jakiś inny fragment
kodu (np. funkcję sortującą) jest dostarczenie wskaźnika na funkcję do
wywołania.  Uogólnieniem wskaźnika na funkcję jest "coś", co możemy
wywołać, co z angielskiego jest nazywane *callable*.

Uogólnienie ma na celu:

* pominięcie pośredniego (czyli przez wskaźnik) wywołania funkcji, na
  rzecz wkompilowania (ang. inlining) funkcji w miejsce wywołania,

* możliwość dostarczenia dodatkowych danych do obliczeń, czego nie
  jesteśmy w stanie wykonać ze wskaźnikiem na funkcję.

## Motywacja

W poniższym sortowaniu porównywane są liczby całkowite, dla których
jest ustalony porządek (liniowy) z użyciem operatora `<`:

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

W przykładzie niżej sortujemy obiekty typu klasowego.  Żeby kompilacja
powiodła się, musimy zdefiniować porządek z użyciem operatora `<`.
Operator zdefiniowaliśmy jako funkcję składową, która drugi operand
operatora `<` przyjmuje jako argument wywołania funkcji (pierwszym
operandem jest obiekt `*this`).  Składowy operator porównania powinien
być stały (bo nie powinien zmieniać pierwszego operandu) i powinien
pobierać drugi operand przez referenceję stałą (bo nie powinien
zmieniać drugiego operandu).

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Funkcja `std::sort` domyślnie używa operatora `<`, bo domyślną
wartością trzeciego argumentu wywołania tej funkcji jest domyślna
(ang. default-constructed) wartość obiektu struktury `std::less<A>`,
która używa właśnie operatora `<`.  Identyczny efekt uzyskamy, jeżeli
jawnie podamy trzeci argument:

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
konstruktorowi klasy, który może przechować callable w polu składowym.
Tak robi, na przykład, kolejka priorytetowa biblioteki standardowej
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
(ang. call operator).

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
