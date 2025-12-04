---
title: The `auto` type specifier
---

# Introduction

The `auto` type specifier requests the compiler to deduce the type
using the initializing expression.  The compiler puts the deduced type
in the place of `auto`.  This type specifier can be used in the type
definition of:

* a variable,

* a parameter of a function,

* a parameter of a lambda expression,

* what a function returns.

The `auto` type specifier allows us to write generic code, because we
no longer have to put a specific type, but can ask the compiler to
deduce it.

# Motivation

Writing types in legacy C++ was cumbersome, arduous and inviting
errors that a compiler sometimes was unable to catch.  Typically, to
iterate over a container of containers, we had to spell out the
iterator type.  Now it's easy to declare an iterator by defining its
type using the `auto` specifier.  Here's an example:

```cpp
{% include_relative motivation_iter.cc %}
```

Likewise, for a container of type `T` we can use the `size` function
that returns a value of type `T::size_t`, but it's easier to use
`auto`:

```cpp
{% include_relative motivation_size.cc %}
```

Czasami nie jesteśmy w stanie podać typu, bo go nie znamy, jak w
przypadku *domknięć*, czyli funktorów typów anonimowych, które są
wynikiem opracowania wyrażenia lambda.

```cpp
{% include_relative motivation_closure.cc %}
```

Na razie sprawa wydaje się prosta, bo deklarowanym typem jest tylko
`auto`, ale typ może zawierać dodatkowo także specyfikatory i
deklaratory.

# Wnioskowanie typu zmiennej

Wnioskowanie typu `auto` odbywa się zgodnie z zasadami wnioskowania
**typowych** argumentów szablonu.  Zasady dla wartościowych i
szablonowych argumentów szablonu nie obowiązują.

Inicjalizacja zmiennej wygląda tak:

```cpp
type name = expression;
```

Typ zmiennej może zawierać kwalifikatory `const` i `volatile`.
Dodatkowo może zawierać deklarator `&` typu referencyjnego i
deklarator `*` typu wskaźnikowego.  Interesuje nas sytuacja, kiedy typ
zmiennej zawiera specyfikator `auto`.  Na przykład:

```cpp
const auto &t = 1;
```

Kompilator traktuje taką inicjalizację zmiennej jak inicjalizację
parametru funkcji szablonowej, gdzie:

* `auto` jest traktowane jak nazwa typowego parametru szablonu,

* wyrażenie inicjalizujące jest traktowane jak argument wywołania
  funkcji.

Zadaniem kompilatora jest wywnioskowanie argumentu takiego urojonego
szablonu (urojonego, bo nie jest zapisany w kodzie, a jedynie go sobie
wyobrażamy) i podstawienie go w miejsce `auto`.

## Przykłady

W podanych przykładach stosowane są znane zasady wnioskowania
argumentów szablonów, ale warto przytoczyć kilka przykładów.

Żeby przekonać się, że rzeczywiście typy są wnioskowane, jak się
spodziewamy, możemy w przykładach wykorzystać poniższą sztuczkę.
Kompilacja zakończy się błędem, w którym będzie podany wywnioskowany
typ.

```cpp
{% include_relative show.cc %}
```

## Typ referencyjny lub wskaźnikowy

Możemy zadeklarować typ referencyjny do danej typu, który kompilator
ma sam wywnioskować.  Może to być zmienna, funkcja czy tablica języka
C.  Oto przykład:

```cpp
{% include_relative refs.cc %}
```

Podobnie dla wskaźników:

```cpp
{% include_relative pointers.cc %}
```

## Zwykły typ

Używając typu zwykłego (niereferencyjnego i niewskaźnikowego), możemy
inicjalizować zmienne bez podawania ich typu.  W ten sposób możemy
upewnić się, że zmienna będzie zawsze zainicjalizowana.

Jeżeli wyrażenie inicjalizujące jest typu wskaźnikowego, to
wywnioskowany typ będzie wskaźnikowy.  Tak będzie w przypadku rozpadu
nazwy funkcji i nazwy tablicy języka C, czy literału łańcuchowego.

Dla zwykłego typu inicjalizowanej zmiennej nigdy nie będzie
wywnioskowany typ referencyjny, bo wyrażenie inicjalizujące nigdy nie
jest typu referencyjnego.

```cpp
{% include_relative normal.cc %}
```

## `decltype`

Specyfikator typu `decltype` dostarcza typ zmiennej czy wyrażenia,
który możemy wykorzystać do deklaracji typu innej zmiennej.
Dostarczony typ może być dowolny, także referencyjny.  Ale chwileczkę,
czy przypadkiem nie było powiedziane, że wyrażenia nigdy nie są typu
referencyjnego?  Także te, które przekazujemy do `decltype`?  Tak, ale
w przypadku `decltype` deklarator `&` najwyższego rzędu nie jest
usuwany.  Tak powiada standard.

```cpp
{% include_relative decltype.cc %}
```

Jeżeli chcemy, żeby `decltype` dostarczył dla zmiennej typ jej
wyrażenia inicjalizacyjnego, to używamy `decltype(auto)`.  To nie to
samo, co `auto`, w którym stosowane są zasady wnioskowania typowego
argumentu szablonu.  Oto przykłady:

```cpp
{% include_relative decltype_auto.cc %}
```

# Specyfikator `auto` w pętli `for`

Specyfikator `auto` możemy użyć w pętli `for` dla określenia typu
elementu, którym będziemy się posługiwać w ciele pętli.  Chociaż jest
to częsty i wygodny sposób, to nie musimy z niego korzystać i możemy
podać typ jawnie.  Ale trzeba uważać, żeby nie popełnić błędu.

Przykład niżej pokazuje, jak można popełnić błąd, który jest trudny do
wychwycenia.  To jest błąd, który sam popełniłem, a którego nie
rozumiałem przez długi czas.  W przykładzie błędnie napisany jest typ
zmiennej: `const pair<int, string> &`.  Wydaje się, że jest dobrze, bo
chcemy iterować używając referencji stałej do elementów kontenera, a
wiemy, że elementem kontenera jest para klucza i wartości.  Program
jednak nie działa prawidłowo.  Gdzie jest błąd?

Błąd jest w typie pierwszego elementu pary: klucze w kontenerze są
typu stałego, a my zażądaliśmy typu niestałego.  Zatem typ zmiennej
pętli powinien być `const pair<const int, string> &`.  Ten drobny błąd
powoduje, że kompilator tworzy tymczasową parę elementów typu `int`
oraz `string` i inicjalizuje ją przez kopiowanie wartości z pary w
kontenerze.  W ten sposób mamy, co chcieliśmy, czyli referencję stałą
do pary żądanego typu.

Problem w tym, że ta para wkrótce wyparuje, bo jest alokowana na
stosie jako zmienna lokalna ciała pętli.  Problem, bo w wektorze
zapisujemy referencję do ciągu znaków w parze, a ta referencja już po
zakończeniu iteracji odnosi się do nieistniejącego obiektu.  Wypisując
zawartość wektora widzimy tą samą wartość, bo obiekty były tworzone na
stosie w tym samym miejscu, a my widzimy ostatnią wartość.

Ponieważ w kontenerach nie możemy przechowywać referencji (`const
string &`), to użyliśmy `std::reference_wrapper<const string>`.
Moglibyśmy użyć po prostu wskaźników, ale `std::reference_wrapper`
możemy używać jak referencji (chodzi o składnię i semantykę).

```cpp
{% include_relative for_auto.cc %}
```

# Typ wyniku funkcji i `auto`

Funkcja (zwykła albo szablonowa) może mieć zadeklarowany typ zwracanej
wartości z użyciem specyfikatora `auto`.  W definicji tego typu mogą
być także użyte specyfikatory `const` i `volatile` oraz deklaratory
`&` i `*`.

Typ `auto` jest wnioskowany zgodnie z zasadami wnioskowania
**typowego** argumentu szablonu na podstawie wyrażenia instrukcji
powrotu, które pełni rolę wyrażenia inicjalizującego dla zwracanej
wartości.  Sytuacja jest analogiczna do inicjalizacji parametru
funkcji szablonowej, z tą różnicą, że zwracana wartość nie ma nazwy.

Oto kilka przykładów:

```cpp
{% include_relative return.cc %}
```

## Doskonałe zwracanie wyniku funkcji

Piszemy callable `f`, które wywołuje jakiś inny callable `g`.  Nie
znamy typu wyniku zwracanego przez `g`, ale chcemy, żeby `f` zwracała
tą samą daną, jaką otrzymała od funkcji `g`.  Jest to problem
doskonałego zwracania wyniku funkcji, a którym chodzi o:

* zapobiegnięcie kopiowaniu albo przenoszeniu danej,

* zachowanie kategorii wartości wyrażenia wywołania funkcji `g`, czyli
  wyrażenie wywołania funkcji `f` ma mieć tę samą kategorię.

Problem sprowadza się do tego, żeby zadeklarowany typ wyniku `f` był
taki sam jak dla `g`.  Konstruktor (kopiujący albo przenoszący) dla
zwracanej danej nie będzie wywołany, bo:

* jeżeli `g` zwraca wynik przez referencję, to `f` ma zwracać też
  przez referencję tego samego typu (l-referencję, referencję stałą
  czy r-referencję), a wtedy do kopiowania czy przenoszenia nie
  dochodzi,

* jeżeli wynik zwracany jest przez wartość, to konstruktor zostanie
  unikniony.

W poprawnej implementacji, funkcja `f` powinna mieć zadeklarowany typ
wracanej wartości jako `decltype(auto)`, a wyrażenie wywołania funkcji
`g` powinno być argumentem instrukcji powrotu funkcji `f`.
Specyfikator `decltype(auto)` gwarantuje nam identyczny typ.
Specyfikator `auto` wnioskowałby typ, a tego nie chcemy.

Oto przykład:

```cpp
{% include_relative return_decltype.cc %}
```

Domyślnie w wyrażeniu lambda typ zwracanej wartości jest wnioskowany
na podstawie wyrażenia instrukcji powrotu, ale możemy zażądać
doskonałego zwracania wyniku (tego samego typu, który zwraca funkcja
`g`):

```cpp
{% include_relative return_decltype2.cc %}
```

# Wyrażenia lambda i `auto`

Specyfikatora `auto` możemy użyć w definicji typu parametru i
zwracanej wartości.

## Typ parametru

W wyrażeniu lambda możemy podać parametry dla operatora wywołania.  I
tam możemy użyć `auto`.  Wtedy składowa operatora wywołania jest
szablonowa, gdzie `auto` służy jako typowy parametr szablonu funkcji.
Wywołanie tej funkcji składowej z argumentami różnych typów powoduje
konkretyzację szablonu i generowanie nowych przeciążeń dla tego samego
domknięcia.  Oto przykład to ilustrujący, po którym weteran
programowania w C++ może zwątpić:

```cpp
{% include_relative lambda_par.cc %}
```

## Typ zwracanej wartości

Domyślnym typem zwracanym przez operator wywołania funkcji domknięcia
jest `auto`.  Z użyciem `->` możemy jednak zdefiniować typ zwracanego
wyniku jako `decltype(auto)`, żeby zadbać o doskonałe zwracanie
wyniku.

```cpp
{% include_relative lambda_ret.cc %}
```

# Skrócony zapis szablonu

Zapis szablonu możemy skrócić o nagłówek, jeżeli typ parametru funkcji
zdefiniujemy z użyciem specyfikatora `auto`:

```cpp
{% include_relative abs.cc %}
```

Jeżeli chcemy, żeby dwa parametry były tego samego typu, to
specyfikator `auto` o to nie zadba, bo jego wystąpienia tworzą różne
parametry szablonu:

```cpp
{% include_relative max.cc %}
```

Definicję paczki parametrów funkcji możemy skrócić przez użycie
specyfikatora typu `auto`, jak w przykładzie niżej.  Jednak w tym
przykładzie, parametr `T` musi być zdefiniowany, bo jego argumentu
kompilator nie jest w stanie wywnioskować (nie ma parametru funkcji z
użyciem tego parametru szablonu), a dodatkowo jego nazwą posługujemy
się w ciele funkcji.

```cpp
{% include_relative factory.cc %}
```

# Podsumowanie

* Specyfikator `auto` pozwala na wnioskowanie typu.

* W pętli `for` warto używać specyfikatora `auto`.

* W wyrażeniu lambda można użyć typu `auto` dla parametru.

# Quiz

* Gdzie możemy użyć specyfikatora `auto`?

* Jaka jest różnica między specyfikatorami `auto` i `decltype(auto)`?

* Na czym polega doskonałe zwracanie wartości?
