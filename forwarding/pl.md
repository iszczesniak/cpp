---
title: Doskonałe przekazywanie argumentów
---

# Wprowadzenie

Problemem do rozwiązania jest napisanie funkcji `f`, która wywołuje
funkcję `g`.  Argument przekazany funkcji `f` ma zostać przekazany
funkcji `g` bez kopiowania i z *zachowaniem kategorii* tego argumentu.
Ten problem nazywamy **doskonałym przekazywaniem argumentu**
(ang. perfect argument forwarding).

O kwalifikatorach (const, volatile) i typie parametru funkcji `g` nic
nie wiemy.  Chcemy napisać tylko jedną implementację funkcji `f`
(czyli szablon funkcji), która nie kopiowałaby argumentu i
zachowywałaby jego kategorię wartości.

Zadaniem jest napisanie takiego szablonu funkcji:

{% highlight c++ %}
template<typename T>
void
f(qualifiers_a type_a a)
{
  g(a);
}
{% endhighlight %}

**PYTANIE**: Czy można napisać taki szablon funkcji `f`?  Jakie mają
być kwalifikatory `qualifiers_a` i jaki typ `type_a`?  Czy
kwalifikatorem może, czy musi być `const`?  Czy typem ma być `T`, `T
&`, czy `T &&`?

**ODPOWIEDŹ**: Można, ale tylko z C++11.  O tym później.

## Dlaczego to problem?

Zadanie jest problematyczne, bo argumentem wywołania funkcji może być
albo l-wartość, albo r-wartość.  Są dwa podproblemy.

### Podproblem #1

Problemem jest określenie typu parametru funkcji, żeby mógł on być
zawsze zainicjalizowany, bez względu na typ i kategorię argumentu.

### Podproblem #2

Problemem jest utrata kategorii argumentu.  W ciele funkcji, wyrażenie
z nazwą parametru funkcji jest zawsze l-wartością, nawet jeżeli
parametr jest r-referencją (która została zainicjalizowaną
r-wartością).  Zachowanie kategorii argumentu funkcji `f` podczas
przekazywania go do funkcji `g` ma znaczenie, bo też kategoria (nie
tylko typ) argumentu ma wpływ na wybór przeciążenia funkcji `g`.

## Motywacja: fabryki obiektów

Funkcje szablonowe `std::make_unique` i `std::make_shared` są
fabrykami obiektów.  Tworzą one obiekty i muszą przekazać swoje
argumenty do konstruktora klasy w niezmienionej postaci.

To jest przykład dla dwóch parametrów:

{% highlight c++ %}
template<typename T, typename A1, typename A2>
unique_ptr<T>
make_unique(qualifiers_a1 type_a1 a1,
            qualifiers_a2 type_a2 a2)
{
  return unique_ptr<T>(new T(a1, a2));
}
{% endhighlight %}

## Parametry i argumenty funkcji

* Parametry i argumenty funkcji to nie to samo!
* Parametr to zmienna dostępna w ciele funkcji.
* Argument to wyrażenie w wywołaniu funkcji.
* Parametry są *inicjalizowane* na podstawie argumentów.
* `foo(int x)`, gdzie `x` jest parametrem funkcji
* `foo(a)`, gdzie `a` jest argumentem wywołania funkcji

Argument może być l-wartością albo r-wartością, a parametr zawsze jest
l-wartością, bo ma nazwę (możemy pobrać jego adres).

# Możliwe rozwiązania

Możliwe rozwiązania z pominięciem kwalifikatora `volatile`.

* przez wartość: `T`
* przez stałą wartość: `const T`
* przez l-referencję: `T &`
* przez referencję stałą: `const T &`
* przez r-referencję: `T &&`
* przez r-referencję stałą: `const T &&`

Nie bierzemy pod uwagę rozwiązań:

* `const T`, bo jest to przekazanie przez wartość, jak w przypadku
  `T`, z deklaracją, że parametru nie będziemy zmieniać,

* `const T &&`, bo nie znam zastosowania tego typu referencji.

## Rozwiązanie: `T`

Wygląda tak:

{% highlight c++ %}
template<typename T>
void
f(T t)
{
  g(t);
}
{% endhighlight %}

Gdy wykonamy `f(1)`, a funkcja `g` będzie pobierać argumenty przez
referencję, to nie otrzyma referencji na oryginalny obiekt, a
referencję na parametr funkcji `f`, który jest kopią oryginalnego
obiektu.  **Złe rozwiązanie.**

Zatem zostają nam trzy przypadki z referencjami do rozważenia:

* `T &`
* `const T &`
* `T &&`

## Rozwiązanie: `T &`

Wygląda tak:
  
{% highlight c++ %}
template<typename T>
void
f(T &t)
{
  g(t);
}
{% endhighlight %}

Jeżeli argumentem wywołania funkcji `f` jest r-wartość, to kompilacja
nie powiedzie się, bo l-referencja nie może być zainicjalizowana
r-wartością.  **Złe rozwiązanie.**

Przykład:

{% highlight c++ %}
{% include_relative bad1.cc %}
{% endhighlight %}

## Rozwiązanie: `const T &`

Wygląda tak:
  
{% highlight c++ %}
template<typename T>
void
f(const T &t)
{
  g(t);
}
{% endhighlight %}

Teraz będzie się kompilować dla r-wartości, np. `f(1)`, ale jeżeli
funkcja będzie `void g(int &);`, to kod nie będzie się kompilował, bo
niestałej l-referencji nie można zainicjalizować stałą referencją.
**Złe rozwiązanie.**

Przykład:

{% highlight c++ %}
{% include_relative bad2.cc %}
{% endhighlight %}

## Rozwiązanie: `T &` razem z `const T &`

Możemy mieć dwa szablony: jeden dla `T &`, a drugi dla `const T &`.
Czyli mamy dwie definicje szablonu funkcji (dwa przeciążenia szablonu)
dla jednego parametru:

{% highlight c++ %}
template<typename T>
void
f(T &t)
{
  g(t);
}

template<typename T>
void
f(const T &t)
{
  g(t);
}
{% endhighlight %}

Ta implementacja rozwiąże podproblem #1, ale dla $n$ parametrów
potrzebujemy $2^n$ definicji funkcji!  **Złe rozwiązanie.**

Przykład:

{% highlight c++ %}
{% include_relative bad3.cc %}
{% endhighlight %}

# Prawidłowe rozwiązanie

Żeby rozwiązać podproblem #1 z C++11, typem parametru powina być
r-referencja bez kwalifikatorów.  Prawda objawiona:

{% highlight c++ %}
template<typename T>
void
f(T &&t)
{
  g(std::forward<T>(t));
}
{% endhighlight %}

Jeżeli `T` jest parametrem szablonu, to typ `T &&` parametru funkcji
nazywamy typem **referencji przekazującej** (ang. forwarding
reference).  Referencja przekazująca to nie r-referencja.

Prawda objawiona, bo dla typu parametru `T &&` funkcji szablonowej
wprowadzono specjalne zasady wnioskowania typu `T` w zależności od
kategorii argumentu, co jest dalej wyjaśnione.

Problem w tym, że parametr `t` jest l-wartością (bo ma nazwę `t`),
nawet jeżeli argumentem wywołania funkcji `f` była r-wartość.  W ten
sposób tracimy informację o kategorii wartości wyrażenia, które było
argumentem funkcji `f`.  Funkcja `std::forward` odzyskuje tę kategorię
wartości, czego szczegóły są wyjaśnione niżej.

**Podproblem #1 został rozwiązany referencją przekazującą.**

**Podproblem #2 został rozwiązany funkcją `std::forward`.**

## Referencja do referencji

W C++ nie ma typu *referencji do referencji*, ale takie typy mogą się
pojawić, jako efekt deklaracji referencji przekazującej, albo
definicji typów szablonowych z użyciem `using` czy `typedef`.

Jeżeli argumentem parametru szablonu `T` będzie `T &`, to wtedy typem
parametru funkcji, który został zadeklarowana jako referencja
przekazująca, będzie typ `T & &&`.  Co wtedy?

## Spłaszczanie typów referencji

Jeżeli pojawi się typ referencji do referencji, to kompilator zamieni
taki typ na referencję według zasady:

* `cv1 T & cv2 T &` na `cv12 T &`
* `cv1 T & cv2 T &&` na `cv12 T &`
* `cv1 T && cv2 T &` na `cv12 T &`
* `cv1 T && cv2 T &&` na `cv12 T &&`

Zbiory `cv1`, `cv2`, `cv12` oznaczają zbiory kwalifikatorów, do
których mogą należeć `const` i `volatile`.  Zbiór `cv12` jest sumą
zbiorów `cv1` i `cv2`.

Przykład spłaszczania referencji:

{% highlight c++ %}
{% include_relative collapse.cc %}
{% endhighlight %}

## Wnioskowanie

Jaki będzie wywnioskowany argument dla parametru `T` szablonu, jeżeli
jest on użyty w deklaracji referencji przekazującej?

Jeżeli argumentem funkcji `f` jest:

* l-wartość typu A, to `T = A &`,

* r-wartość typu A, to `T = A`.

## Funkcja `std::forward`

Funkcja szablonowa `std::forward` przyjmuje l-wartość `t` typu $T$ i
zależności od argumentu szablonu zwraca:

* r-referencję na `t` dla `std::forward<T>(t)`
* l-referencję na `t` dla `std::forward<T &>(t)`

Funkcji `std::forward` używa się w definicji pewnej funkcji
szablonowej `f`, gdzie trzeba odzyskać kategorię wyrażenia, które było
argumentem wywołania funkcji szablonowej `f`.

Przykład:

{% highlight c++ %}
{% include_relative forward.cc %}
{% endhighlight %}

# Rozbudowany przykład

Zdefiniujemy różne przeciążenia dla funkcji `g`.  Funkcja `g` będzie
przyjmowała też drugi parametr, który pozwoli nam stwierdzić, czy
kompilator wybrał to przeciążenie, które się spodziewaliśmy.  W
funkcji `main` wywołujemy każde przeciążenie funkcji.

Piszemy funkcję `f`, która doskonale przekazuje swój argument do
funkcji `g`.

Przykład:

{% highlight c++ %}
{% include_relative perfect.cc %}
{% endhighlight %}

Co się stanie, jeżeli usuniemy funkcję `forward` z funkcji `f`?  Wtedy
będą przekazywane zawsze l-wartości do funkcji `g`.  Można sprawdzić.

# Podsumowanie

* Problem doskonałego przekazywania argumentów występuje w
  programowaniu generycznym z użyciem szablonów.

* Jako typ parametru funkcji używamy: `T &&t`, gdzie `T` jest
  parametrem szablonu, a `t` parametrem funkcji.

* Aby przekazać parametr do innej funkcji, używamy funkcji
  `std::forward`, która odzyskuje kategorię wartości wyrażenia.

<!-- LocalWords: expr -->
<!-- LocalWords: lvalue lvalues rvalue -->
<!-- LocalWords: rvalue -->

<!-- LocalWords: deklaratora -->
<!-- LocalWords: deklaratorem -->

<!-- LocalWords: inicjalizowana -->
<!-- LocalWords: inicjalizowaną -->
<!-- LocalWords: inicjalizowane -->
<!-- LocalWords: inicjalizującego -->
<!-- LocalWords: inicjalizującym -->

<!-- LocalWords: wyoptymalizowana -->
<!-- LocalWords: wyoptymalizowane -->
<!-- LocalWords: wyoptymalizowanie -->

<!-- LocalWords: zainicjalizowana -->
<!-- LocalWords: zainicjalizowaną -->
<!-- LocalWords: zainicjalizowane -->

<!-- LocalWords: binds -->
<!-- LocalWords: nullptr -->
<!-- LocalWords: object -->
<!-- LocalWords: overload -->
<!-- LocalWords: name names -->
<!-- LocalWords: member -->
<!-- LocalWords: move -->
<!-- LocalWords: reference references -->
<!-- LocalWords: refer refers -->
<!-- LocalWords: resolution -->
<!-- LocalWords: title -->
