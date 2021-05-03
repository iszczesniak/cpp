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
{% include_relative motivation3.cc %}
```

Łatwiej jest pozwolić kompilatorowi wywnioskować typ, zamiast domyślać
się (często błędnie) czy sprawdzać w dokumentacji.  Oto przykład:

```cpp
{% include_relative motivation2.cc %}
```

Czasami nie jesteśmy w stanie podać typu, bo go nie znamy, jak w
przypadku *domknięć*, czyli funktorów typów anonimowych, które są
wynikiem opracowania wyrażenia lambda.

```cpp
{% include_relative closure.cc %}
```

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

Oto przykłady:

```cpp
{% include_relative auto.cc %}
```

Jeżeli typem jest `auto &&`, to kompilator wywnioskuje, czy referencja
powinna być typu l-wartość czy r-wartość w zależności od kategorii
wartości wyrażenia inicjalizującego referencję.

Żeby zobaczyć wywnioskowany typ w czasie kompilacji, w kodzie
wprowadzono błąd, o którym kompilator informuje jednocześnie wypisując
interesujący nas typ.

# Wnioskowanie typu parametru wyrażenia lambda

# Wnioskowanie typu wartości zwracanej przez funkcję

# `auto` jako typ zmiennej deklarowanej w pętli for: przykład z
  dostępem do elementów std::map

# `decltype`
