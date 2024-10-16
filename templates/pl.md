---
title: Szablony
---

# Szablony

Szablon może być:

* funkcji,

* klasy, struktury, unii,

* składowej klasy (funkcji składowej, pola składowego),

* aliasu typu,

* zmiennej,

* konceptu.

Deklaracje i definicje szablonów rozpoczynają się słowem kluczowym
`template` z taką składnią:

```
template <lista parametrów>
```

Mówimy, że szablon jest *sparametryzowany*, bo ma listę parametrów.
Te parametry nazywamy **parametrami szablonu**.

Kiedy wywołujemy funkcję zdefiniowaną szablonem, to po jej nazwie
możemy podać **argumenty szablonu** w znakach `<>`.  Konkretyzacja
szablonu **podstawia** argument szablonu w miejsca wystąpienia
parametru w szablonie.

# Parametry szablonu

Parametry szablonu są zdefiniowane w liście parametrów, gdzie są
oddzielone przecinkami.  Definicja parametru ustala rodzaj i
opcjonalną nazwę parametru.  Rodzaje parametrów to: typ, wartość,
szablon.  Przykład listy parametrów:

```cpp
template <typename T, int N, template<typename> typename C>
```

## Rodzaj parametru: typ

Nazwijmy to prosto: **typowy parametr szablonu**.  I typowy on jest
też dlatego, że tego rodzaju parametr jest najczęstszy.  Typowy
parametr deklarujemy pisząc `typename T`.  Słowo kluczowe `typename`
mówi, że chodzi o typowy parametr, a `T` jest nazwą parametru.  Możemy
również równoważnie napisać `class T`, ale nowocześniej jest `typename
T`.

Konkretyzacja może podstawić za `T` dowolny typ: wbudowany
(np. `int`), użytkownika (np. `myclass`), a nawet `void`.  `T` nie
musi spełniać żadnych warunków, np. nie musi dziedziczyć z klasy
bazowej.  Wymagania dotyczące typu `T` wynikają z jego użycia w
definicji szablonu, czyli czy, na przykład:

* tworzymy domyślną wartość typu `T`, czyli `T{}`,

* dodajemy, używając `operator+`, wartości typu `T`,

* wyłuskujemy, używając `operator&`, wartość typu `T`,

* przekazujemy jakiejś funkcji, np. `push_back`, wartość typu `T`,

* piszemy do `std::ostream` wartość typu `T` z użyciem `operator<<`.

To jest przykład funkcji szablonowej z typowym parametrem, gdzie
kompilator jest w stanie **wywnioskować argument szablonu**, więc nie
musimy go jawnie podawać podczas wywołania funkcji:

```cpp
{% include_relative print1.cc %}
```

## Rodzaj parametru: wartość

Nazwijmy to prosto: **wartościowy parametr szablonu**.  Parametr tego
rodzaju deklarujemy pisząc `some_type I`, gdzie `some_type` jest
typem, np. `int`.  Typ `some_type` nie jest dowolny, tylko nieduży
zbiór typów jest dozwolony, a najczęściej używane są typy całkowite.
Podczas kompilacji za `I` podstawiana jest wartość tego typu, np. 1
dla parametru szablonu zadeklarowanego jako `int I`.

Przykład deklaracji wartościowego parametru szablonu:

```cpp
template <int N>
```

To jest przykład szablonu funkcji z wartościowym parametrem szablonu
`N`, którego *argument* musi być jawnie podany, bo kompilator nie jest
w stanie go wywnioskować:

```cpp
{% include_relative print2.cc %}
```

W przykładzie niżej mamy dwa przeciążone szablony funkcji
(przeciążone, bo mają tą samą nazwę).  Drugi szablon ma wartościowy
parametr szablonu `N`, którego argument musi być jawnie podany.  Ma
też typowy parametr szablonu `T`, którego argument może być
wywnioskowany:

{% highlight c++ %}
{% include_relative print3.cc %}
{% endhighlight %}

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez instrukcję warunkową czasu kompilacji
`if constexpr`:

{% highlight c++ %}
{% include_relative print4.cc %}
{% endhighlight %}

Jednym z dozwolonych typów dla wartościowych parametrów szablonu są
wskaźniki i referencje na funkcje:

```cpp
{% include_relative callback.cc %}
```

## Rodzaj parametru: szablon

Nazwijmy to tak: **szablonowy parametr szablonu**.  Parametr tego
rodzaju ma podstawiony typ szablonowy podczas konkretyzacji, a w
liście parametrów szablonu deklarujemy go tak:

```
template <lista parametrów parametru> typename T
```

A to przykład początku deklaracji lub definicji szablonu z szablonowym
parametrem:

```
template <template <lista parametrów parametru> typename T>
```

Przykładowy program:

{% highlight c++ %}
{% include_relative template1.cc %}
{% endhighlight %}

Za `__PRETTY_FUNCTION__` kompilator GCC podstawia nazwę funkcji i
argumenty szablonu, więc możemy przekonać się w jaki sposób funkcja
została skonkretyzowana.

W przykładzie niżej, za szablonowy parametr `C` może być podstawiony
dowolny typ szablonowy, którego pierwszy parametr jest typowy, a drugi
wartościowy.

{% highlight c++ %}
{% include_relative template2.cc %}
{% endhighlight %}

Szablonowy parametr to po prostu typowy parametr, ale który dodatkowo
pozwala na:

* *definicję interfejsu przyjmowanego typu*: argumentem tego parametru
   może być wyłącznie typ szablonowy spełniający zdefiniowany
   interfejs,

* *wydobycie argumentów z przyjętego typu*: z argumentu tego parametru
   (który jest na pewno typu szablonowego, bo spełnia interfejs),
   możemy wydobyć argumenty konkretyzacji.

Oto przykład:

{% highlight c++ %}
{% include_relative template3.cc %}
{% endhighlight %}

I kolejny przykład:

{% highlight c++ %}
{% include_relative template4.cc %}
{% endhighlight %}

Ten rodzaj parametru pozwala nam na przerwanie zależności cyklicznej
między typami szablonowymi:

{% highlight c++ %}
{% include_relative circular.cc %}
{% endhighlight %}

# Parametr a argument szablonu

Parametrem jest nazwa, np. `T`, którą używamy w deklaracji i definicji
szablonu.  Argumentem jest typ, wartość, albo szablon, który jest
podstawiany za parametr.  Argument możemy podać jawnie,
np. `print<100>()`, albo może być wnioskowany na podstawie argumentu
wywołania funkcji.

Ta terminologia jest analogiczna do terminologii **parametru funkcji**
i **argumentu wywołania funkcji**, ale ta analogia jest jedynie
powierzchowna.  Inicjalizacja parametru funkcji z użyciem argumentu
wywołania ma dużo szczegółów (jak na przykład konwersje między typami,
czy zasady inicjalizowania referencji), których podstawienie nie ma.
Podstawienie to skopiowanie tekstu argumentu do parametru ze
sprawdzeniem rodzaju argumentu (czy jest typem, wartością, czy typem
szablonowym).  Wniosek: **podstawienie to nie inicjalizacja**.

# Argumenty szablonu

Argumenty szablonu mogą być:

* wnioskowane przez kompilator (najczęściej stosowane),

* jawnie podane przez programistę (czasami niezbędne),

* domyślnie podane przez programistę (czasami wygodne).

Ten przykład pokazuje wyżej wymienione przypadki:

```cpp
{% include_relative intro.cc %}
```

Zanim przejdziemy do wnioskowania, pierwsze omówimy jawne podawanie
argumentów szablonów i domyślne argumenty szablonów.

## Jawnie podane argumenty szablonu

Kiedy korzystamy z kontenerów biblioteki standardowej (a każdy robił
to na pewno), jawnie podajemy argumenty szablonu jako część nazwy typu
używając `<>`, czyli składni `typ kontenera<lista argumentów>`:

{% highlight c++ %}
{% include_relative explicit.cc %}
{% endhighlight %}

Tej składni możemy też użyć przy wywołaniu funkcji szablonowej (a nie
tylko przy definiowaniu typu, np. kontenera), co jest przydatne w
dwóch przypadkach:

* chcemy innych argumentów niż te wnioskowane przez kompilator, co
  zrobiliśmy w przykładzie wyżej z funkcją `print`,

* musimy jawnie podać argumenty, bo kompilator nie jest ich w stanie
  wywnioskować.

Kompilator wnioskuje argumenty szablonu na podstawie wyrażeń, które są
przekazywane w wyrażeniu wywołania funkcji (kiedy wywołujemy funkcję)
czy konstruktora (kiedy tworzymy obiekt).  Jeżeli nie jest w stanie
wywnioskować argumentów, to musimy jawnie je podać.

Przykład niżej pokazuje implementację fabryki obiektów.  Argument
wywołania fabryki przekazujemy do konstruktora obiektu, którego typ
jest określony przez argument szablonu.  Kompilator nie jest w stanie
określić typu obiektu, więc musimy go jawnie podać.

{% highlight c++ %}
{% include_relative explicit2.cc %}
{% endhighlight %}

### Kolejność argumentów

Kolejność argumentów szablonu ma znaczenie (tak jak w przypadku
argumentów wywołania funkcji), bo argumenty są pozycyjne, czyli od
pozycji argumenty zależy to, o który argument nam chodzi.  Tak więc
jeżeli chcemy podać drugi argument, to musimy podać też pierwszy
argument.

Jeżeli w powyższym przykładzie z fabryką zmienimy kolejność
argumentów, to typ argumentu wywołania konstruktora będziemy musieli
także podać jawnie, chociaż mógłby być wywnioskowany.  Po zmianie
kolejności musimy jawnie podać pierwszy argument, bo zapragnęliśmy
podać drugi argument:

{% highlight c++ %}
{% include_relative explicit3.cc %}
{% endhighlight %}

## Domyślne argumenty szablonu

Parametr szablonu (każdego rodzaju: typowy, wartościowy i szablonowy)
może mieć zdefiniowany domyślny argument, który będzie użyty jeżeli
nie podaliśmy argumentu jawnie i jeżeli kompilator nie jest w stanie
go wnioskować (bo, np., nie ma argumentu funkcji).  Domyślny argument
jest opcjonalny.

Domyślny argument podajemy po nazwie parametru z użyciem `=`.  Oto
przykład:

{% highlight c++ %}
{% include_relative default.cc %}
{% endhighlight %}

### Domyślne callable

Czasami trzeba przekazać callable jakiejś funkcji, ale nie zawsze to
callable jest wymagane.  Nie chcemy przekazywać wskaźnika i sprawdzać
w czasie uruchomienia, czy jest on `nullptr`, albowiem niewydajne i
nieciekawe.  Chcemy, żeby callable było wkompilowane, a w szczególnym
przypadku, żeby callable nie wprowadzało narzutu, jeżeli nie jest
wymagane.  Do tego właśnie przydaje się domyślny argument szablonu.

Rozwiązanie: typ callable jest parametrem szablonu z domyślnym
argumentem, którym jest pusty callable, czyli struktura z operatorem
wywołania o pustym ciele.  Musimy też podać domyślną wartość callable
(argumentu wywołania funkcji), czyli `{}` (bezargumentowe tworzenie
obiektu).  Oto super przykład:

{% highlight c++ %}
{% include_relative empty_callable.cc %}
{% endhighlight %}

# Podsumowanie

* Szablony są podstawą programowania uogólnionego w C++.

* Parametry szablonów są typowe, wartościowe albo szablonowe.

* Szablony funkcji są najciekawsze i najtrudniejsze pośród szablonów.

# Quiz

* Co to jest typowy parametr szablonu?

* Czego może być szablon?

* Argument a parametr szablonu.

<!-- LocalWords: lvalue lvalues rvalue -->
