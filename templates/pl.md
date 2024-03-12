---
title: Szablony
---

# Szablony

Szablonowe mogą być:

* funkcje, 

* klasy, struktury, unie,

* składowe klasy (czyli funkcje i pola składowe klasy),

* typy (czyli aliasy typów),

* zmienne,

* koncepty.

Deklaracje i definicje szablonów rozpoczynają się słowem kluczowym
`template` z taką składnią:

```
template <lista parametrów>
```

Mówimy, że szablon jest sparametryzowany, bo ma listę parametrów.

## Lista parametrów

Parametry w liście są oddzielone przecinkami.  Deklaracja parametru
składa się z rodzaju i opcjonalnej nazwy parametru.  Rodzaje
parametrów to: typ, wartość, szablon.  Przykład listy parametrów:

```cpp
template <typename T, int N, template<typename> typename C>
```

### Rodzaj parametru: typ

Nazwijmy to prosto: **typowy parametr szablonu**.  I typowy on jest
też dlatego, że tego rodzaju parametr jest najczęstszy.  Typowy
parametr deklarujemy pisząc `typename T`.  Słowo kluczowe `typename`
mówi, że chodzi o typowy parametr, a `T` jest nazwą parametru.  Możemy
również równoważnie napisać `class T`, ale nowocześniej jest `typename
T`.

Podczas kompilacji za `T` może być podstawiony dowolny typ: wbudowany
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
kompilator jest w stanie **wywnioskować argument szablonu**:

```cpp
{% include_relative print1.cc %}
```

### Rodzaj parametru: wartość

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

### Rodzaj parametru: szablon

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
{% include_relative template.cc %}
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

Ten rodzaj parametru pozwala nam na przerwanie zależności cyklicznej
między typami szablonowymi:

{% highlight c++ %}
{% include_relative circular.cc %}
{% endhighlight %}

## Parametr a argument szablonu

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

# Podsumowanie

* Szablony są podstawą programowania uogólnionego w C++.

* Parametry szablonów są typowe, wartościowe albo szablonowe.

* Szablony funkcji są najciekawsze i najtrudniejsze pośród szablonów.

# Quiz

* Co to jest typowy parametr szablonu?

* Czego może być szablon?

* Argument a parametr szablonu.

<!-- LocalWords: lvalue lvalues rvalue -->
