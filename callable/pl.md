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
określony interfejs, czyli jakiego typu są parametry i wynik callable.

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
porównania**, czyli **operatora `<`**.  Jest kilka operatorów
porównania, które mogą być zdefiniowane dla typu klasowego: `==`,
`!=`, `<`, `<=`, `>`, `=>`, `<=>`, ale dla ustalenia porządku miedzy
elementami najważniejszy jest operator `mniejszy od`, czyli `<`.

Operator `<` zdefiniowaliśmy jako funkcję składową, dla której
pierwszym operandem jest obiekt `*this`, a drugim jest parametr
składowej.  Składowy operator porównania powinien być stały (bo nie
powinien zmieniać pierwszego operandu) i powinien pobierać drugi
operand przez referenceję stałą (bo nie powinien zmieniać drugiego
operandu).

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Funkcja `std::sort` używa operatora `<`, jeżeli nie przakażemy jej
callable porównania jako ostatni argument wywołania.  Tak naprawdę
funkcja `std::sort` używa obiektu typu `std::less`, która to z kolei
używa operatora `<`.  Dla porównania sortowanych elementów,
implementacja funkcji `std::sort` nie używa bezpośrednio `<`, bo to
ograniczałoby możliwość adaptacji sortowania przez programistę.
Zamiast tego używa callable.

Możemy uzyskać identyczny efekt jak w przykładzie wyżej, jeżeli
przekażemy jako callable obiekt struktury `std::less<A>`.  Jeżeli tego
nie zrobimy, zostanie on domyślnie użyty.

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

Funkcja `std::sort` nie musi zawsze używać operatora `<`.  Możemy użyć
dowolnego callable.  Możemy sortować w kolejności rosnącej, jeżeli
użyjemy obiektu struktury `std::greater`.  Ten typ używa operatora
`>`, więc musimy go zdefiniować, zamiast operatora `<`.

{% highlight c++ %}
{% include_relative motivation4.cc %}
{% endhighlight %}

Callable może być przekazywany nie tylko funkcji, ale też
konstruktorowi, który może przechować callable w polu składowym.  Tak
robi, na przykład, kolejka priorytetowa biblioteki standardowej
(`std::priority_queue`).  Poniżej jest nasz roboczy przykład z kolejką
priorytetową, który będziemy dalej zmieniać.

{% highlight c++ %}
{% include_relative pq.cc %}
{% endhighlight %}

# Typy callable

Callable może być:

* funkcją (użytą przez wskaźnik albo referencję),

* funktorem (użytą przez wartość, referencję albo wskaźnik).

## Funkcja

Wyrażenie, które jest tylko nazwą funkcji (bez operatora wywołania)
może być potraktowane jako adres tej funkcji, co nazywam rozpadem
funkcji na wskaźnik.  Możemy pobrać adres funkcji z użyciem operatora
adresowania, np. `&foo`.  Te dwa sposoby pobrania adresu są
równoważne, co jest trochę niespójne, bo powinien być tylko jeden
sposób.

Używając tego adresu możemy wywołać funkcję.  Jedyne operacje możliwe
na wskaźniku do funkcji to: pobranie adresu funkcji i wywołanie
funkcji.

W przykładzie niżej posługujemy się funkcją przez wskaźnik i
referencję.

{% highlight c++ %}
{% include_relative function.cc %}
{% endhighlight %}

Tutaj sortujemy malejąco z użyciem wskaźnika na funkcję:

{% highlight c++ %}
{% include_relative sort_foo.cc %}
{% endhighlight %}

Domyślnie kolejka priorytetowa sortuje malejąco, czyli zwraca
największe elementy.  W przykładzie niżej przekazujemy wskaźnik na
funkcję porównującą, żeby ustalić porządek rosnący w kolejce
priorytetowej.

{% highlight c++ %}
{% include_relative pq_foo.cc %}
{% endhighlight %}

## Funktor

Funktor to obiekt, który ma zdefiniowany operator wywołania `()`
(ang. call operator).  Zaletą funktora, w porównaniu z funkcją, jest
możliwość przekazania dodatkowych danych, która są przechowywane w
polach składowych funktora.

W przykładzie niżej definiujemy prosty typ funktora, tworzymy funktor
i wywołujemy go.  Funktor jest callable, bo możemy go wywołać.
Ponieważ operator `()` został zdefiniowany jako stały, to możemy go
wywołać także na rzecz obiektów stałych.

{% highlight c++ %}
{% include_relative functor1.cc %}
{% endhighlight %}

W funktorze możemy przechowywać dane:

{% highlight c++ %}
{% include_relative functor2.cc %}
{% endhighlight %}

Funktor działa jak funkcja, kiedy nie przechowuje danych.  Na
przykład, typy `std::less` i `std::greater` zachowują się jak funkcje,
bo nie przechowują danych.  Takie typy funktora nie spowalniają
programu: konstruktor i destruktor są puste, a operator porównania
jest wkompilowywany w miejsce wywołania.  Szybciej się nie da.

Domyślnie kolejka priorytetowa zwraca największy element, bo do
porównania używa klasy funktora `std::less`.  Poniżej użyjemy funktora
klasy `std::greater`, żeby kolejka zwracała najmniejszy element.

{% highlight c++ %}
{% include_relative pq_ro.cc %}
{% endhighlight %}

Możemy także zdefiniować własny typ funktora, który działa jak
funkcja:

{% highlight c++ %}
{% include_relative pq_fo1.cc %}
{% endhighlight %}

W tym przykładzie w czasie uruchomienia przekazujemy konstruktorowi
funktora argument (dodatkową daną do obliczeń), który mówi o porządku
(rosnącym bądź malejącym):

{% highlight c++ %}
{% include_relative pq_fo2.cc %}
{% endhighlight %}

# Domknięcie

**Domknięcie** jest funktorem, który jest wynikiem opracowania
**wyrażenia lambda**.  Lambda (w skrócie od wyrażenia lambda) jest
*syntaktycznym skrótem* wygodnego tworzenia funktorów w porównaniu z
pisaniem klasy funktora.  Moglibyśmy się obejść bez lambd, bo tą
samą funkcjonalność mają klasy funktora.  Lambdy są po prostu
wygodne.

Ponieważ domknięcie jest obiektem, to musi mieć typ, ale zwykle go nie
potrzebujemy, więc możemy powiedzieć, że domknięcie jest typu
anonimowego.  Możemy pozyskać typ domknięcia z użyciem operatora
`decltype`.

## Składnia

Wyrażenia lambda mają wiele szczegółów, których nie omówimy.  Jednak
większość lambd ma taką składnię:

`[lista przechwytywania](lista parametrów) mutable {ciało}`

Listy przechwytywania i parametrów używają przecinków do oddzielenia
pozycji.  Jeżeli lista parametrów jest pusta, to `()` można pominąc.
Nawet jeżeli lista przechwytywania i ciało są puste, to `[]` i `{}`
nie mogą być pominięte.

Lista przechwytywania może zawierać:

* deklarator domyślnego przechwytywania: `=` albo `&` (czyli nie oba
  znaki), np. `[=]`, `[&]`, ale nie `[&, =]`,

* nazwy przechwytywanych zmiennych, które mogą być opcjonalnie
  poprzedzone deklaratorem `&`, np. `[&x]`,

* deklaracje zmiennych `name-in-closure = variable-name`, które mogą,
  ale nie muszą być poprzedzone deklaratorem `&`, e.g., `[&x = y]`.

Lista parametrów jest listą parametrów funkcji, tak jak dla zwykłej
funkcji.

Specyfikator `mutable` jest opcjonalny.  Domyślnie składowa funkcja
operatorowa `()` domknięcia jest stała, ale możemy ją zadeklarować
jako niestałą z użyciem specyfikatora `mutable`.

Dlatego najprostszą lambdą jest `[]{}`.  Tutaj tworzymy domknięcie i
wywołujemy je w jednym wyrażeniu:

{% highlight c++ %}
{% include_relative capture1.cc %}
{% endhighlight %}

Wyrażenie `[]{}()`, które tworzy i wywołuje domknięcie, jest
równoważne temu kodowi:

{% highlight c++ %}
{% include_relative capture1a.cc %}
{% endhighlight %}

## Semantyka

Lambda tworzy typ funktora (strukturę albo klasę) i obiekt tej klasy.
Podstawowe fakty:

* Przechwycone zmienne są tworzone jako pola składowe funktora i są
  inicjalizowane przez konstruktor domknięcia.

* Lista parametrów wyrażenia lambda staje się listą parametrów
  składowego operatora `()` domknięcia.

* Składowy operator `()` domknięcia jest stały, chyba że użyto
  specyfikatora `mutable`.

* Ciało wyrażenia lambda staje się ciałem składowego operatora `()`
  domknięcia.

* Typ zwracanej wartości składowego operatora `()` domknięcia jest
  wnioskowany na podstawie wyrażenia, które jest argumentem instrukcji
  powrotu użytego w ciele.  Jeżeli nie użytko instrukcji powrotu, to
  typem zwracanej wartości jest `void`.

Lista przechwytywania określa, jak w ciele funkcji zapewnić dostęp do
wartości zmiennych z zakresu wyrażenia lambda.  Zakres jest fragmentem
kodu, w którym dostępne są zmienne.  Zakres może być globalny, klasy,
funkcji, czy bloku.

Lista przechwytywania może być pusta.  W takim przypadku w ciele
dostępne są jedynie parametry z listy parametrów.  Oto przykład:

{% highlight c++ %}
{% include_relative capture2.cc %}
{% endhighlight %}

Powyższy kod jest równoważny poniższemu:

{% highlight c++ %}
{% include_relative capture2a.cc %}
{% endhighlight %}

## Ways of capturing variables

A variable can be captured by value or by reference.  When a variable
is captured by value, the closure keeps in its member field a copy of
the value of the captured variable, i.e., the member field was
initialized by copying the value of the captured variable.  To capture
a variable by value, put its name in the capture list.

When a variable is captured by reference, the closure keeps in its
member field a reference to the captured variable, i.e., the member
reference was initialized with the captured variable.  To capture a
variable by reference, put its name in the capture list, and preceeded
it by an ampersand.

For example:

{% highlight c++ %}
{% include_relative capture3.cc %}
{% endhighlight %}

The code above is equivalent to this code:

{% highlight c++ %}
{% include_relative capture3a.cc %}
{% endhighlight %}

### Default capture policy

The capture list can begin with the default policy of capturing
variables either by value or by reference.  If a default capture
policy is given, *all variables* used in the body are captured, and we
do not have to list them.

We set the default capture-by-value policy with `=`.  For example:

{% highlight c++ %}
{% include_relative capture4.cc %}
{% endhighlight %}

The code above is equivalent to this code:

{% highlight c++ %}
{% include_relative capture4a.cc %}
{% endhighlight %}

We set the default capture-by-reference policy with `&`.  Please note
that in the example below, and the next example too, the call operator
can be const, because we are not modifying a member reference, but a
variable to which the member reference is bound.

{% highlight c++ %}
{% include_relative capture5.cc %}
{% endhighlight %}

The code above is equivalent to this code:

{% highlight c++ %}
{% include_relative capture5a.cc %}
{% endhighlight %}

We can specify the default capture policy, and then list those
variables that should be captured differently.  Also, for the member
fields, we do not have to use the names of the captured variables, but
we can give any name.

{% highlight c++ %}
{% include_relative capture6.cc %}
{% endhighlight %}

## Closure Examples

Since a closure has some type, but we just don't care about it, we
write:

`auto c = closure expression;`

By using the `auto` type, we let the compiler deduce (this process is
called *type deduction*) the type of `c` based on the type of the
closure expression.  Even though there is the `=` sign, the line above
is not an *assignment expression*, but an *initialization statement*.
That entails that the closure is not copied, but created directly in
the memory location of `c` with copy elision.

Here's an example of using a lambda with a priority queue:

{% highlight c++ %}
{% include_relative pq_lambda1.cc %}
{% endhighlight %}

Here we pass an argument to a closure:

{% highlight c++ %}
{% include_relative pq_lambda2.cc %}
{% endhighlight %}

# Conclusion

A callable is a generalization of a function.  A callable can be:

* a function pointer,

* a functor.

Lambdas are nifty and succinct: we can create closures with little
writing, and with less room for mistakes (lambdas are less
error-prone).

# Quiz

* In what way are functors more capable than functions?

* What's the difference between a functor and a closure?

* Are lambdas indispensable?

{% include rid_pl %}

<!-- LocalWords: callable inlined -->
