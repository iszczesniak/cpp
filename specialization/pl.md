---
title: Specjalizacja szablonów
---

# Wprowadzenie

Możemy **specjalizować** szablon funkcji czy klasy.  Szablon, który
specjalizujemy nazywamy **szablonem podstawowy** (ang. primary
template), żeby odróżnić go od specjalizacji, która też jest
szablonem.  Specjalizacja nadpisuje definicję szablonu podstawowego.
Nie można dalej specjalizować specjalizacji.

Szablon podstawowy deklaruje albo definiuje funkcję albo klasę oraz
parametry szablonu (liczbę i rodzaj parametrów).  Specjalizacja musi
mieć tą samą nazwę (funkcji albo klasy) i dostarczyć argumenty dla
specjalizowanego szablonu podstawowego.

Specjalizacja szablonu też jest szablonem, ale już dla częściowo albo
całkowicie określonych argumentów.  Specjalizację możemy poznać po
nieco innej składni szablonu, ale ciągle występuje słowo kluczowe
`template`.

Specjalizacja może być **częściowa** (ang. partial specialization)
albo **całkowita** (ang. complete specialization).  Specjalizacja
szablonu funkcji nie może być częściowa, może być tylko całkowita.
Specjalizacja szablonu klasy może być częściowa albo całkowita.

# Specjalizacja szablonu funkcji

Szablon funkcji może być specjalizowany tylko całkowicie, czyli dla
ustalonych wszystkich argumentów szablonu podstawowego: szablon
specjalizacji nie ma już parametrów, więc jego lista parametrów jest
pusta.  Tak więc deklaracje i definicje specjalizacji szablonów
funkcji rozpoczynają się słowem kluczowym `template` i pustą listą
parametrów:

```
template <>
```

Potem następuje definicja szablonu funkcji, która wygląda jak
definicja zwykłej funkcji, bo nie używamy w niej (czyli w liscie
parametrów funkcji i ciele funkcji) nazw parametrów szablonu
podstawowego, a jedynie ich ustalonych wartości (np. `int`, `1` czy
`std::list`).  Ale jest pewna różnica.

Różnica dotyczy nazwy funkcji.  W specjalizacji podajemy listę
argumentów szablonu podstawowego po nazwie funkcji, czego w definicji
zwykłej funkcji nie robimy.

Oto przykład:

{% highlight c++ %}
{% include_relative foo1.cc %}
{% endhighlight %}

Szablon podstawowy i specjalizację możemy także deklarować.  Jeżeli
zadeklarujemy szablon podstawowy, ale go nie zdefiniujemy, to nie
będzie podstawowej implementacji tego szablonu funkcji.  Będziemy
mogli specjalizować szablon i używać go wyłącznie dla tych
specjalizacji.  Pokazuje to przykład niżej.

Listę argumentów szablonu podstawowego możemy pominąć, jeżeli
kompilator jest w stanie wywnioskować te argumenty na podstawie listy
parametrów funkcji.  W przykładzie niżej pominęliśmy listę argumentów
(`<A>`) szablonu podstawowego po nazwie funkcji `foo` w deklaracji i
definicji specjalizacji.

{% highlight c++ %}
{% include_relative foo2.cc %}
{% endhighlight %}

Nie możemy częściowo specializować szablonów funkcji.  Specjalizacja
częściowa polegałaby na wprowadzeniu parametru dla specjalizacji, ale
nie jest to dozwolone, jak pokazuje przykład niżej.

{% highlight c++ %}
{% include_relative complete.cc %}
{% endhighlight %}

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu.  W
specjalizacji szablonu musimy podać argument `0` parametru `N`, bo
kompilator nie jest w stanie go wywnioskować.  Argument `int`
parametru `T` może być wywnioskowany, więc nie jest podany.

{% highlight c++ %}
{% include_relative print.cc %}
{% endhighlight %}

## Przeciążanie funkcji a szablony

Czy możemy się obyć bez szablonów?  W przykładzie niżej funkcja `foo`
jest przeciążona, żeby w zależności od argumentu wywołania funkcji
dostarczyć inną implementację.

Problem w tym, że nie mamy szablonu, który mógłby być zastosowany dla
dowolnego typu i dlatego dla argumentu `.2` typu `double` jest
wywołane przeciążenia dla typu `int`.

{% highlight c++ %}
{% include_relative overloads.cc %}
{% endhighlight %}

Możemy dołożyć szablon podstawowy do przykładu, jak pokazano niżej.
Mamy szablon dla dowolnego typu i przeciążenie dla typu `A`.  Czy dla
wywołania funkcji `foo` z argumentem `A()` będzie użyty szablon czy
przeciążenie?  A dokładnie mówiąc przeciążenie funkcji szablonowej
(czyli funkcji, która otrzymaliśmy po konkretyzacji podstawowego
szablonu funkcji dla `T = A`) czy przeciążenie zwykłej funkcji?
**Przeciążenie zwykłej funkcji zawsze ma pierwszeństwo.**

{% highlight c++ %}
{% include_relative mix1.cc %}
{% endhighlight %}

Możemy dodać także specjalizację dla `T = A`, ale i tak zostanie
wybrane przeciążenie zwykłej funkcji.  Podczas wyboru przeciążenia,
kompilator nie rozważa specjalizacji, a jedynie przeciążenia zwykłych
funkcji i przeciążenia funkcji szablonowych.  Tak więc dodanie
specjalizacji i tak nie namówi kompilator na jej użycie.

{% highlight c++ %}
{% include_relative mix2.cc %}
{% endhighlight %}

## Kiedy potrzebujemy specjalizacji

Wydaje się, że specjalizacja szablonu jest zbędna, bo tą samą
funkcjonalność uzyskaliśmy przeciążając zwykłą funkcję.  Jest jednak
funkcjonalność specjalizacji, której nie osiągniemy przez
przeciążenia.

Specjalizacja szablonów pozwala na zdefiniowanie przez użytkownika
funkcji dla kodu, który został już dołączony w pliku nagłówkowym,
np. biblioteki szablonowej.  Biblioteka deklaruje szablon funkcji,
którą potrzebuje, a definicję specjalizacji czy nawet szablonu
podstawowego można pozostawić użytkownikowi.  Tak może wyglądać plik
nagłówkowy `library.hpp`:

{% highlight c++ %}
{% include_relative library.hpp %}
{% endhighlight %}

Tak może wyglądać użycie biblioteki:

{% highlight c++ %}
{% include_relative need.cc %}
{% endhighlight %}

Jeżeli przeciążenie funkcji zdefiniujemy po dołączeniu biblioteki, to
funkcja `goo` nie będzie go znała i nie użyje go.  Funkcja wie
natomiast, że może użyć szablonu funkcji `foo`, bo jej szablon
podstawowy został zadeklarowany.

Możemy też przenieść definicję przeciążenia funkcji `foo` przed
dyrektywę `#include`, żeby funkcja `goo` mogła skorzystać z
przeciążenia, ale lepiej nie wprowadzać takiego nieporządku.

# Specjalizacja szablonów typów użytkownika

Możemy zadeklarować albo zdefiniować szablon typu użytkownika, czyli
struktury, klasy i unii.  Ten szablon podstawowy możemy specjalizować.

Szablon podstawowy i jej specjalizacje mają jedynie wspólną nazwę
typu, a ich interfejsy (składowe dostępne użytkownikowi),
implementacje i wielkości w pamięci mogą się całkowicie różnić.

Przykładem specjalizacji typu w bibliotece standardowej jest
specjalizacja `std::vector<bool>`, czyli kontenera `std::vector` dla
typu `bool`.  Ta specjalizacja ma podobny interfejs, ale zupełnie inną
implementację.

W przykładzie niżej definiujemy szablon podstawowy typu `A` z jedną
funkcją składową `foo`.  Specjalizacja dla argumentu `double` nie ma
funkcji `foo`, a dziedziczy po std::pair i ma funkcję `goo`.

{% highlight c++ %}
{% include_relative struct.cc %}
{% endhighlight %}


# Podsumowanie

# Quiz

<!-- LocalWords: lvalue lvalues rvalue -->
