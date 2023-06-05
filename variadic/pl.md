# Wstęp

C++11 wprowadził **szablon wariadyczny** (ang. a variadic template),
który potrafi przyjąć dowolną liczbę argumentów szablonu, także
zerową.  Szablon wariadyczny jest statycznie typowanym mechanizmem
czasu kompilacji, który jest konkretyzowany w miejscu użycia.

Szablon wariadyczny poznamy po trójkropku `...` w liście parametrów
szablonu:

```cpp
{% include_relative intro.cc %}
```

# Paczka parametrów

Trójkropek jest częścią definicji **paczki parametrów** (ang. a
parameter pack), po którym następuje (bez oddzielającej spacji) nazwa
paczki.  Paczka parametrów szablonu może być szablonu albo funkcji.
Paczka parametrów jest używana wyłącznie w **rozwinięciu**.

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
`const Args &...args`.

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

# Skrócony zapis szablonu

Definicję paczki parametrów funkcji możemy skrócić przez użycie
specyfikatora typu `auto`:

```cpp
{% include_relative abbreviated.cc %}
```

# Doskonałe przekazywanie

Funkcja może przyjmować przez referencję przekazującą argumenty, które
doskonale przekażemy, jak w przykładzie niżej.  To jest też jedna z
motywacji wprowadzenia szablonu wariadycznego, implementacja funkcji
`std::make_unique`.

```cpp
{% include_relative forwarding.cc %}
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

Wyrażenie złożenia (ang. a fold expression) przetwarza paczkę
parametrówm, co eliminuje potrzebę przetważania rekurencyjnego.  Są
cztery takie wyrażenia, każde ujęte w nawiasy, gdzie `e` jest
wyrażeniem, `op` operatorem, a `args` nazwą paczki parametrów funkcji
:

* `(e op ... op args)` -> `(((e op p_1) op p_2) op ...) op p_n`

```cpp
{% include_relative fold.cc %}
```

# Przykład: własności obiektu

```cpp
{% include_relative props.cc %}
```
