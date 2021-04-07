---
title: Semantyka przeniesienia
---

# Wprowadzenie

Semantyka przeniesienia dotyczy wyłącznie danych typów klasowych (do
tego zaliczają się także struktury i unie), więc będziemy mówić o
przenoszeniu obiektów, a nie danych.  Obiekt jest daną typu klasowego,
czyli danymi interpretowanymi zgodnie z definicją klasy.  Stan obiektu
nazywamy **wartością obiektu**.

Definicja wartości obiektu zależy od implementacji klasy.  Zwykle
wartością obiektu jest stan obiektów bazowych i składowych.  Jednak na
stan obiektu nie muszą składać się niektóre dane, np. dane podręczne
(ang. cache data).

Wartość obiektu może być kopiowana podczas:

* inicjalizacji: `T t(<expr>);`

* przypisania: `t = <expr>;`

W inicjalizacji i przypisaniu rozróżniamy obiekt źródłowy (wyrażeń
`<expr>` wyżej) i docelowy (zmiennych `t` wyżej).  Obiekt docelowy
jest inicjalizowany obiektem źródłowym.  Obiekt docelowy jest po lewej
stronie operatora przypisania, a źródłowy po prawej.

Fakty o kopiowaniu obiektów:

* Kopiowanie jest czasochłonne, kiedy obiekty są duże.

* Kopiowanie obiektów jest implementowane przez:

  * *konstruktor kopiujący* podczas inicjalizacji,
  
  * *kopiujący operator przypisania* podczas przypisania.

Obiekty źródłowe i docelowe mogą być gdziekolwiek, czyli w dowolnym
obszarze pamięci, nie tylko na stosie czy stercie.  Na przykład,
obiekt źródłowy może być na stosie, a obiekt docelowy w obszarze
pamięci dla danych statycznych i globalnych.  Obiekt nie powinien
wiedzieć, w jakim obszarze pamięci się znajduje.

Kopiowanie może być problemem w zależności od tego czy jest potrzebne
czy nie.  Nie jest problemem, jeżeli jest potrzebne, np. kiedy musimy
wykonać kopię obiektu do zmian, bo oryginału nie możemy zmieniać.

Kopiowanie jest problemem, kiedy jest zbędne, czyli wtedy, kiedy
obiekt źródłowy po kopiowaniu nie jest potrzebny.  Zbędne kopiowanie
pogarsza wydajność: kod będzie działał poprawnie, ale mógłby być
szybszy.

# Semantyka przeniesienia

Semantyka przeniesienia pozwala na przeniesienie wartości z obiektu
źródłowego do docelowego kiedy kopiowanie nie jest potrzebne.  Została
ona wprowadzona w C++11, ale jej potrzeba była zauważona w latach
dziewięćdziesiątych.  Przenoszenie jest jak ratowanie ładunku
(wartości) z tonącego statku (obiektu, który wkrótce zostanie
zniszczony).

Semantyka przeniesienia jest stosowana:

* podczas inicjalizacji i przypisania,

* kiedy wyrażenie obiektu źródłowego jest r-wartością,

* kiedy typ obiektu docelowego ma zaimplementowaną semantykę
  przeniesienia.

Semantyka przeniesienia jest implementowana przez:

* **konstruktor przenoszący** (dla inicjalizacji),

* **przenoszący konstruktor przypisania** (dla przypisania).

## Jak to działa

* To nie magia.  Obiekt nie jest przenoszony bit po bicie do innego
  miejsca.  Użytkownik zna każdy szczegół i ma pełną kontrolę.

* Tylko wartość jest przenoszona.  Obiekt źródłowy i obiekt docelowy
  pozostają tam, gdzie były, bo będą one niszczone tak jak zwykle.

* Po przeniesieniu obiekt źródłowy musi być spójny, ale stan nie musi
  być określony (np. jakiś pusty).  Obiekt musi być spójny, bo obiekt
  będzie niszczony.

## Konstruktor: kopiujący i przenoszący

Klasa może mieć kopiujący lub przenoszący konstruktor.  Może mieć oba
albo żadnego.  Konstruktor kopiujący i przenoszący możemy nazwać
przeciążeniami konstruktora.

Konstruktor przenoszący klasy `T` ma jeden parametr typu `T &&`.

### Prosty przykład

W przykładzie niżej klasa ma zdefiniowane oba konstruktory:

{% highlight c++ %}
{% include_relative constructors.cc %}
{% endhighlight %}

### Implementacja przeciążeń konstruktora

Konstruktor przenoszący powinien inicjalizować obiekty bazowe i
składowe z użyciem konstruktorów przenoszących.  Dlatego w liście
inicjalizacyjnej obiektów bazowych i składowych konstruktora
przenoszącego powinny być przekazywane r-wartości jako wyrażenia
inicjalizacyjne, żeby wpłynąć na wybór przeciążeń konstruktorów
obiektów bazowych i składowych.  Do tego celu używamy funkcji
`std::move`, jak pokazano w przykładzie niżej, w którym dla porównania
zaimplementowano także konstruktor kopiujący.

{% highlight c++ %}
{% include_relative ctor-impl.cc %}
{% endhighlight %}
  
## Operator przypisania: kopiujący i przenoszący

Klasa może mieć kopiujący lub przenoszący operator przypisania.  Może
mieć oba albo żadnego.  Operator kopiujący i przenoszący możemy nazwać
przeciążeniami operatora.

Przenoszący operator przypisa klasy `T` ma jeden parametr typu `T &&`.

### Prosty przykład:

W przykładzie niżej klasa ma zdefiniowane dwa przeciążenia operatora
przypisania:

{% highlight c++ %}
{% include_relative operators.cc %}
{% endhighlight %}

### Typ wyniku przenoszącego operatora przypisania

Jeżeli `a` i `b` są typu `T`, to wyrażenie `a = b = T()` powinno
przenieść wartość z obiektu tymczasowego `T()` do `b`, a następnie
powinno skopiować wartość z `b` do `a`.  To wyrażenie jest
opracowywane od prawej do lewej strony, ponieważ operator przypisania
ma wiązanie prawostronne.

Dlatego przenoszący operator przypisania powinien zwracać
l-referencję, a nie r-referencję.  Jeżeli operator zwracałby
r-referencję, to wtedy to wyrażenie przenosiłoby wartość z obiektu
tymczasowego `T()` do `b` (tak jak należy), ale potem przenosiłoby
wartość z `b` do `a`, a nie kopiowało, czego byśmy oczekiwali.

Co ciekawe, ponieważ wyrażenie z wywołaniem przenoszącego operatora
przypisania jest r-wartością (ponieważ zwraca l-referencję), to możemy
go użyć do inicjalizacji l-referencji: `T &l = T() = T();`, mimo że `T
&l = T();` się nie kompiluje.

### Implementacja przeciążeń operatora przypisania

Przenoszący operator przypisania powinien przypisywać obiektom bazowym
i składowym z użyciem przenoszących operatorów przypisania.  Dlatego
wyrażeniami źródłowymi operatorów przypisania dla obiektów bazowych i
składowym powinny być r-wartości, żeby wpłynąć na wybór przeciążeń
operatorów przypisania.  Do tego celu używamy funkcji `std::move`, jak
pokazano w przykładzie niżej, w którym dla porównania zaimplementowano
także kopiujący operator przypisania.

{% highlight c++ %}
{% include_relative assign-impl.cc %}
{% endhighlight %}

## Wybór przeciążenia

Wybór przeciążenia (kopiującego albo przenoszącego) konstruktora czy
operatora przypisania zależy od kategorii wartości wyrażenia
źródłowego i dostępności przeciążeń.  Stosowane są tu zasady wyboru
przeciążenia funkcji w zależności od referencyjnego typu parametru
przeciążenia.

## Składowe specjalne

Składowymi specjalnymi są:

* konstruktor domyślny (bezargumentowy),

* konstruktor kopiujący i kopiujący operator przypisania,

* konstruktor przenoszący i przenoszący operator przypisania,

* destruktor.

Składowa specjalna może być niezadeklarowana (ang. undeclared) albo
zadeklarowana (ang. declared).  Funkcja może być zadeklarowana:

* **jawnie przez programistę** (ang. explicitely) jako:

  * *dostarczona przez użytkownika* (ang. user-defined): programista
     dostarcza implementację,

  * *domyślnie zaimplementowana* (ang. defaulted): programista żądą
     domyślnej implementacji,

  * *usunięta* (ang. deleted): programista deklaruje składową jako
     usuniętą.

* **niejawnie przez kompilator** (ang. implicitely) jako:

  * *domyślnie zaimplementowana* (ang. defaulted): kompilator dołącza
     domyślą implementację bez żądania programisty,

  * *usunięta* (ang. deleted): kompilator deklaruje składową jako
     usuniątą bez żądania programisty.

Jeżeli składowa jest zadeklarowana jako usunięta (nieważne, czy jawnie
czy niejawnie), to jest brana pod uwagę w wyborze przeciążenia, ale
kiedy jest wybrana, to kompilacja kończy się błędem.

### Jawnie domyślna składowa

Programista może jawnie zażądać domyślnej implementacji składowej
specjalnej z użyciem `= default`:

{% highlight c++ %}
{% include_relative default.cc %}
{% endhighlight %}

### Domyślna implementacja

Wszystkie obiekty bazowe i składowe w domyślnej implementacji:

* konstruktora bezargumentowego są inicjalizowane bezargumentowo,

* konstruktora kopiującego są inicjalizowane przez kopiowanie,

* kopiującego operatora przypisania są przypisywane przez kopiowanie,

* konstruktora przenoszącego są inicjalizowane przez przenoszenie,

* przenoszącego operatora przypisania są przypisywane przez
  przenoszenie,

* destruktora są niszczone.

### Jawnie usunięta składowa

Programista może jawnie usunąć składową z użyciem `= delete`:

{% highlight c++ %}
{% include_relative delete.cc %}
{% endhighlight %}

### Zasady dla składowych specjalnych

Wszystkie składowe specjalne są niejawnie domyślnie zaimplementowane,
ale:

* konstruktor bezargumentowy będzie niezadeklarowany, jeżeli
  którykolwiek konstruktor będzie jawnie zadeklarowany,

* konstruktor kopiujący i kopiujący operator przypisania będą
  **niejawnie usunięte** (więc będą brały udział w wyborze
  przeciążenia), jeżeli konstruktor przenoszący lub przenoszący operator
  przypisania został **jawnie zadeklarowany**: programista będzie musiał
  jawnie zadeklarować kopiujące składowe specjalne, jeżeli są wymagane,

* konstruktor przenoszący i przenoszący operator przypisania będą
  **niezadeklarowane** (więc nie będą brały udziału w wyborze
  przeciążenia), jeżeli konstruktor kopiujący, kopiujący operator
  przypisania lub destruktor będą **jawnie zadeklarowane**: stary kod
  będzie nadal działał i nie będzie miał niejawnie dostarczonej domyślnej
  implementacji semantyki przeniesienia (czyli przenoszących składowych
  specjalnych).

Te zasady mają na celu bezproblemową integrację semantyki
przeniesienia zarówno w starym, jak i nowym kodzie.  Na przykład,
stary kod (np. `std::pair`), który nie zarządza swoimi zasobami w
jakiś nietypowy sposób (który wymagałby implementacji konstruktora
kopiującego, kopiującego operatora przypisania lub destruktora),
będzie miał dostarczoną domyślną implementację semantyki
przeniesienia.

## Move-only types

A move-only type can only be moved: it cannot be copied.  This is an
example of a move-only type:

{% highlight c++ %}
{% include_relative move-only.cc %}
{% endhighlight %}

# Implications of the move semantics

## Initialization of function parameters

A function parameter is initialized with the argument expression.  For
a parameter of a non-reference (i.e., we pass the argument by value)
class type, the constructor overload resolution will depend on the
category of the argument expression and the overload availability, as
usual for [a function overloaded with reference
types](../references#reference-type-and-function-overload-resolution).

## Implicit move of returned values

If [the return value optimization
(RVO)](../memory/#return-value-optimization) cannot be used, then the
value of the returned object will be *implicitly moved*, if the
returned object is destroyed when returning from the function.  The
return instruction `return t;` is implicitly converted to `return
std::move(t);`.

Only the return expression consisting of a variable name is implicitly
moved (converted from an lvalue to an rvalue), and other expressions
are not.

We shouldn't explicitly use the `std::move` function (e.g., `return
std::move(t);`) in the return statement whenever we can, because it
disables the RVO.

There are two cases described below in which the RVO cannot be used,
but the returned value will be implicitly moved.

#### Case 1

When we return a function parameter.  A function parameter is
allocated and initialized in a location on the stack that is different
from the location for the return value.  A function parameter is
destroyed when returning from the function, so we can move the value
from it to the location for the return value.  The return expression
is the name of the parameter only, so the implicit move can take
place.

{% highlight c++ %}
{% include_relative implicit1.cc %}
{% endhighlight %}


#### Case 2

When we return a base object of a local object.  The local object is
too big to be initialized in the location for the return value, which
is of the size of the base object.  The local object is destroyed when
returning from the function, so we can move the value from its base
object to the location for the return value.  Only the value of the
base object will be moved, which is called *object slicing*, because
we slice off the value of the base object.  The return expression is
the name of the local object only, so the implicit move can take
place.

{% highlight c++ %}
{% include_relative implicit2.cc %}
{% endhighlight %}

If the local object was static, the value would have to be copied, not
moved.
  
## The `std::swap` function

Let's end with how it all began.  Function `std::swap` is the reason
for the work on the move semantics that started in the 1990's.  This
function showed that it's more efficient to move than to copy.

Function `std::swap` takes by reference two arguments, and swaps their
values.  This function is implemented in the standard library, but in
the example below we also have an example implementation to show
what's going on:

{% highlight c++ %}
{% include_relative swap.cc %}
{% endhighlight %}

# Conclusion

* The move semantics was introduced in C++11.

* The move semantics is used when copying is unnecessary.

* The move semantics is a performance boost.

* Only the values of rvalues can be moved.

* A compiler can ship the default implementation of the move semantics.

* A programmer doesn't have to know about the move semantics, but it
  will be used by a compiler anyway.

# Quiz

* What do we need the move semantics for?

* How does the move sementics work?

* What's a move-only type?

{% include rid %}

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
