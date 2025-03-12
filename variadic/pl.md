---
title: Szablon wariadyczny
---

# Wstęp

C++11 wprowadził **szablon wariadyczny** (ang. a variadic template),
który potrafi przyjąć dowolną liczbę argumentów szablonu, także
zerową.  Szablon wariadyczny jest mechanizmem czasu kompilacji, który
jest konkretyzowany w miejscu użycia.

Szablon wariadyczny poznamy po trójkropku `...` w liście parametrów
szablonu:

```cpp
{% include_relative intro.cc %}
```

W powyższym przykładzie trójkropek został użyty w definicji paczki
parametrów, a potem w rozwinięciu tej paczki.

# Paczka parametrów

Trójkropek jest częścią definicji **paczki parametrów** (ang. a
parameter pack), po którym następuje nazwa paczki.  Paczka parametrów
szablonu może być szablonu albo funkcji.  Paczka parametrów jest
używana w **rozwinięciu** albo **wyrażeniu złożenia**.

## Paczka parametrów szablonu

Parametry szablonu w paczce są tego samego rodzaju: w przykładzie
wyżej są typowe, a w przykładzie niżej wartościowe.

```cpp
{% include_relative value_pack.cc %}
```

### Rozwinięcie paczki

Nazwę paczki z następującym trójkropkiem nazywa się rozwinięciem
paczki (ang. pack expansion).  Paczka parametrów szablonu jest
rozwijana do listy argumentów szablonu oddzielonych przecinkami:

```cpp
{% include_relative expansion.cc %}
```

W przykładach wyżej argumenty szablonu musiały być jawnie podane, bo
funkcje i konstruktor nie miały parametrów i argumentów wywołania, na
podstawie których argumenty szablonu mogły być wywnioskowane.
Argumenty dla parametrów szablonu w paczce są wnioskowane na podstawie
definicji **paczki parametrów funkcji** i argumentów wywołania
funkcji.

## Paczka parametrów funkcji

Paczka parametrów funkcji jest definiowana w liście parametrów funkcji
także z użyciem trójkropka: pierwsze podajemy nazwę paczki parametrów
szablonu, trójkropek, a następnie nazwę paczki parametrów funkcji.  Co
ciekawe, definicja paczki parametrów funkcji jest jednocześnie
rozwinięciem paczki parametrów szablonu.

```cpp
{% include_relative fun_par_pack.cc %}
```

W przykładzie wyżej funkcja przyjmuje argumenty przez wartość.  Może
też przyjmować przez referencję stałą, jeżeli paczkę zdefiniujemy jako
`const Args &... args`.

### Rozwinięcie paczki

Rozwinięcie paczki parametrów funkcji zapisujemy jako nazwa paczki z
następującym trójkropkiem.

```cpp
{% include_relative factory.cc %}
```

Paczkę parametrów szablonu można rozwijać w zgraniu (ang. lockstep) z
paczką parametrów funkcji, np. podczas inicjalizacji obiektów bazowych
parametrami konstruktora klasy wyprowadzonej:

```cpp
{% include_relative lockstep.cc %}
```

# Przetwarzanie rekurencyjne

Parametry paczki funkcji możemy przetwarzać rekurencyjnie.  Sztuczka
polega na zdefiniowaniu dwóch parametrów funkcji: pierwszy do
przetworzenia przez funkcję, a drugi jako paczka do przekazania jako
argument wywołania rekurencyjnego.  W ten sposób zmniejszamy liczbę
parametrów paczki funkcji o jeden za każdym wywołaniem rekurencyjnym.

```cpp
{% include_relative recursive.cc %}
```

# Wyrażenie złożenia

Wyrażenie złożenia (ang. a fold expression, od C++17) jest przepisem
na wygenerowanie wyrażenia z użyciem dowolnego **dwuargumentowego
operatora `op`** na podstawie paczki `p` parametrów funkcji.
Wyrażenie tak się nazywa, bo składa wyrażenie do skompresowanego
zapisu.  Wyrażenie złożenia jest przetwarzane w czasie kompilacji dla
danej paczki parametrów `p`, co eliminuje potrzebę przetwarzania
rekurencyjnego.  Wyrażenie złożenia poznajemy po `...` i nawiasach.
Są cztery wersje: dwie jednoargumentowe i dwie dwuargumentowe, ale
ciągle z użyciem tego samego operatora `op`.

Wyrażenie złożenia wymaga wyrażenia `expr`, które używa paczki `p`.
Wyrażenie `expr` jest opracowywane dla kolejnych parametrów paczki
`p`, która składa się z parametrów `p_1`, `p_2`, ...,
`p<sub>(n-1)</sub>`, p~n~.

Wersje jednoargumentowe wyrażenia złożenia, gdzie argumentem jest
`expr`:

* wersja lewostronna: `(... op expr)` -> `((p_1 op p_2) op ...)`

* wersja prawostronna: `(expr op ...)` -> `(... op (p_(n-1) op p_n))`

Wersja lewostronna przetwarza parametry paczki od lewej strony (do
prawej, czyli od `p_1` do `p_n`), a prawostronna od prawej (do lewej,
czyli od `p_n` do `p_1`).

Przykład niżej używa wersji prawostronnej, gdzie `expr` to `(std::cout
<< ", " << p)` a operatorem jest przecinek.  Jeżeli paczka `p` jest
pusta, to wyrażenie złożenia jest puste.  Jeżeli `p` ma jeden
parametr, to kompilator dokooptowuje dodatkowy pusty parametr, jeżeli
taki istnieje (dla operatora `,` jest nim `void()`), bo `op` wymaga
dwóch argumentów.

```cpp
{% include_relative fold1.cc %}
```

Wersje dwuargumentowe wymagają drugiego argumentu, którym jest
wyrażenie inicjalizujące `init`.

* wersja lewostronna `(init op ... op expr)` -> `((init op p_1) op p_2) op ...)`

* wersja prawostronna `(expr op ... op init)` -> `(init op (p_1 op (p_2 op ...)`

Oto przykład z wersją lewostronną:

```cpp
{% include_relative fold2.cc %}
```

# Przykład: własności obiektu

```cpp
{% include_relative props.cc %}
```

# Podsumowanie

* Szablon wariadyczny przyjmuje dowolną liczbę argumentów.

* Paczka parametrów jest używana w rozwinięciach albo w wyrażeniach
  złożenia.

* Wariadyczne mogą być listy:

  - dziedziczenia i inicjalizacji,

  - parametrów szablonu i argumentów szablonu,

  - parametrów funkcji i argumentów funkcji.

# Quiz

* Czy paczka parametrów szablonu może przyjąć argumenty różnego
  rodzaju?

* Czy paczka parametrów może być pusta?

* Co to jest wyrażenie złożenia?
