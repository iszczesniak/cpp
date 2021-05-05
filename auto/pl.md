---
title: Specyfikator typu `auto`
---

# Wprowadzenie

Specyfikator typu `auto` oznacza, że kompilator ma wywnioskować typ na
podstawie typu wyrażenia inicjalizującego.  W miejsce specyfikatora
`auto` kompilator wstawia wywniowskowany typ.  Specyfikator można użyć
w deklaracji typu:

* zmiennej,

* parametru wyrażenia lambda,

* wartości zwracanej przez funkcję.

Specyfikator typu `auto` pozwala na pisanie uogólnionego kodu, bo nie
musimy podawać konkretnego typu, a prosimy kompilator o
wywniowskowanie go na podstawie kodu.

# Motywacja

Pisanie typów w starym C++ było niewygodne, pracochłonne, a przy tym
łatwo można było popełnić błędy, których kompilator czasami nie był w
stanie wychwycić.  Typowym przykładem była konieczność podawania typów
iteratorów do złożonych struktur danych.  Teraz łatwo używać
iteratorów deklarując ich typ jako `auto`.  Oto przykład:

```cpp
{% include_relative motivation_iter.cc %}
```

Możemy powiedzieć, że jeżeli nie wiemy (i nie chcemy wiedzieć albo nie
chcemy użyć), jakiego typu funkcja zwraca wartość, to możemy użyć
specyfikatora typu `auto`, tak jak zrobiliśmy wyżej używając funkcji
`begin`.  Kolejnym częstym przypadkiem jest użycie funkcji `size`
kontenerów, która zwraca wartość typu `T::size_type`, ale łatwiej jest
nam użyć `auto`.  Na przykład:

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

```
<typ zmiennej> <nazwa zmiennej> = <wyrażenie inicjalizujące>;
```

Typ zmiennej może zawierać specyfikatory `const` i `volatile`.
Dodatkowo może zawierać deklarator `&` typu referencyjnego i
deklarator `*` typu wskaźnikowego.  Interesuje nas sytuacja, kiedy typ
zmiennej zawiera specyfikator `auto`.  Na przykład:

```cpp
const auto &t = 1;
```

Kompilator traktuje taką inicjalizację zmiennej, jak inicjalizację
parametru funkcji szablonowej, gdzie:

* `auto` jest traktowane jak nazwa typowego parametru szablonu,

* argument wywołania funkcji jest wyrażeniem inicjalizującym.

Zadaniem kompilatora jest wywnioskowanie argumentu takiego urojonego
szablonu (urojonego, bo nie jest zapisany w kodzie, a jedynie go sobie
wyobrażamy) i podstawienie go w miejsce `auto`.

## Przykłady

W podanych przykładach stosowane są znane zasady wnioskowania
argumentów szablonów, ale warto przytoczyć kilka przykładów.

Żeby przekonać się, że rzeczywiście typy są wnioskowane, jak się
spodziewamy, możemy w przykładach wykorzystać poniższą sztuczkę.
Kompilacja zakończy się błędem, w który będzie podany wywnioskowany
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

Możemy także wykorzystać referencję przekazującą: `auto &&`.  Ten typ
to nie r-referencja, ponieważ wynikowym typem może być dowolny typ
referencyjny: l-referencja, referencja stała albo r-referencja.  Oto
przykład:

```cpp
{% include_relative forwarding_reference.cc %}
```

Z referencji przekazującej możemy skorzystać, kiedy chcemy
zainicjalizować referencję do elementu zwracanego przez funkcję, ale
nie znamy zarówno typu jak i kategorii zwracanej wartości:

```cpp
{% include_relative forwarding_reference2.cc %}
```

## Zwykły typ

Używając typu zwykłego (niereferencyjnego i niewskaźnikowego), możemy
inicjalizować zmienne bez podawania ich typu.  W ten sposób możemy
upewnić się, że zmienna będzie zawsze zainicjalizowana.

Jeżeli wyrażenie inicjalizujące jest typu wskaźnikowego, to
wywnioskowany typ będzie wskaźnikowy.  Tak będzie w przypadku rozpadu
nazwy funkcji i nazwy tablicy języka C.

```cpp
{% include_relative normal.cc %}
```

# Wnioskowanie typu parametru w wyrażeniu lambda

W wyrażeniu lambda możemy podać parametry dla operatora wywołania.  I
tam możemy użyć `auto`.  Wtedy składowa operatora wywołania jest
szablonowa, gdzie `auto` służy jako typowy parametr szablonu funkcji.
Wywołanie tej funkcji składowej z argumentami różnych typów powoduje
konkretyzację szablonu i generowanie nowych przeciążeń dla tego samego
domknięcia.  Oto przykład to ilustrujący, po którym doświadczony
programista C++ potrafi zwątpić:

```cpp
{% include_relative lambda.cc %}
```

# Wnioskowanie typu wartości zwracanej przez funkcję

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

# `auto` jako typ zmiennej deklarowanej w pętli for: przykład z
  dostępem do elementów std::map

# `decltype`
