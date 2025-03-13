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
operatora `op`** i paczki parametrów.  Wyrażenie tak się nazywa, bo
składa docelowe wyrażenie (to, które sami napisalibyśmy "ręcznie") do
skompresowanego zapisu.  Wyrażenie złożenia jest konkretyzowane w
czasie kompilacji dla danej paczki parametrów, co eliminuje potrzebę
przetwarzania rekurencyjnego.  Wyrażenie złożenia poznajemy po `...` i
nawiasach.  Są cztery wersje: dwie jednoargumentowe i dwie
dwuargumentowe, ale ciągle z użyciem tego samego operatora `op`.

Paczka `p` składa się z parametrów p<sub>1</sub>, p<sub>2</sub>, ...,
p<sub>(n-1)</sub>, p<sub>n</sub>.  Wyrażenie złożenia wymaga wyrażenia
`E`, które używa paczki `p`.  Wyrażenie `E` opracowane dla parametru
p<sub>i</sub> zapisujemy jako E<sub>i</sub>.

## Wersja jednoargumentowa

Wersje jednoargumentowe wyrażenia złożenia, gdzie argumentem jest `E`:

* wersja lewa: `(... op E)` -> ((E<sub>1</sub> op E<sub>2</sub>) op ...)

* wersja prawa: `(E op ...)` -> (... op (E<sub>(n-1)</sub> op E<sub>n</sub>))

Wersja lewa przetwarza parametry paczki od lewej strony (do prawej,
czyli od p<sub>1</sub> do p<sub>n</sub>), a prawa od prawej (do lewej,
czyli od p<sub>n</sub> do p<sub>1</sub>).  Zatem wersja lewa
przetwarza argumenty tak, jakby operator miał wiązanie lewe, a prawa
tak, jakby miał wiązanie prawe.

Dla działania łącznego (np. dodawania) nie ma znaczenia, czy
przetwarzamy od lewej czy od prawej strony, więc oba wyrażenia
złożenia (lewe i prawe) zwrócą ten sam wynik.  Jeżeli jednak działanie
nie jest łączne, to trzeba wybrać właściwą wersję wyrażenia.  W
przykładzie niżej odejmowanie nie jest łączne i ma wiązanie lewe, więc
powinniśmy użyć lewego wyrażenia złożenia.

```cpp
{% include_relative unary1.cc %}
```

Przykład poniżej pokazuje konieczność użycia prawego wyrażenia:

```cpp
{% include_relative unary2.cc %}
```

## Wersja dwuargumentowa

Wersje dwuargumentowe wymagają drugiego argumentu, którym jest
wyrażenie inicjalizujące `A`.

* wersja lewa `(A op ... op E)` -> ((A op E<sub>1</sub>) op ...)

* wersja prawa `(E op ... op A)` -> (... op (E<sub>n</sub> op A))

Jeżeli dodalibyśmy wyrażenie `A` na początek paczki, to moglibyśmy
skorzystać z jednoargumentowego wyrażenia złożenia, ale byłoby to
niewygodne i mniej ekspresywne, jak pokazano niżej:

```cpp
{% include_relative force_unary.cc %}
```

Przykład niżej używa wersji prawej, gdzie `E` to `(std::cout << ", "
<< p)` a operatorem jest przecinek.  Jeżeli paczka `p` jest pusta, to
wyrażenie złożenia jest puste.  Jeżeli `p` ma jeden parametr, to
kompilator dokooptowuje dodatkowy pusty parametr, jeżeli taki istnieje
(dla operatora `,` jest nim `void()`), bo `op` wymaga dwóch
argumentów.

```cpp
{% include_relative complex.cc %}
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
