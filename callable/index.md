---
title: Callable, sth to call
---

# Introduction

In C we use a function pointer to ship a piece of code (e.g., that
establishes order between objects) to some other piece of code (e.g.,
a sorting function).  In C++ a generalization of a function is
something that we can call, and that something we call a *callable*.
Calling a callable has the syntax of calling a function, and the
function interface: we know the types of the arguments and the return
value.

The goal of that generalization is to:

* avoid calling a function indirectly, i.e., using a pointer, so that
  a function being called can be inlined (i.e., compiled into the
  place of call),

* allow for keeping some extra (which are not passed as call
  arguments) data, which we cannot do with a function pointer.

The standard library is using (passing, keeping as a member field)
callables **by value** (i.e., not by reference), so **copying a
callable should be fast**.  Callables passed to standard algorithms
(e.g., `std::sort`) and standard containers (e.g.,
`std::priority_queue`) should be copied fast.  That means, a callable
should not keep a lot of data that should be copied.

Callable is frequentlu used by value (as the standard library does),
but it can be used by reference or by pointer too.

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
