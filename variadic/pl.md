---
title: Szablon wariadyczny
---

# Wstęp

C++11 wprowadził **szablon wariadyczny** (ang. a variadic template),
który potrafi przyjąć dowolną liczbę argumentów szablonu, także
zerową.  Szablon wariadyczny jest mechanizmem czasu kompilacji, który
jest konkretyzowany, kiedy jest użyty.

Szablon wariadyczny poznamy po trójkropku `...` w liście parametrów
szablonu:

```cpp
{% include_relative intro.cc %}
```

W powyższym przykładzie trójkropek został użyty w definicji paczki
parametrów, a potem w rozwinięciu tej paczki.

# Paczka parametrów

**Paczkę parametrów** (ang. a parameter pack) definiujemy z użyciem
trójkropka, po którym następuje nazwa paczki, np. `p`.  Paczka `p`
składa się z parametrów p<sub>1</sub>, p<sub>2</sub>, ...,
p<sub>(n-1)</sub>, p<sub>n</sub>.  Paczka parametrów szablonu może być
szablonu albo funkcji.  Paczka parametrów jest używana w **rozwinięciu
paczki** albo **wyrażeniu złożenia**.

## Paczka parametrów szablonu

**Paczka parametrów szablonu** definiuje parametry szablonu tego
samego rodzaju: w przykładzie wyżej są typowe, a w przykładzie niżej
wartościowe.

```cpp
{% include_relative value_pack.cc %}
```

### Rozwinięcie paczki

Nazwę paczki z następującym trójkropkiem nazywa się rozwinięciem
paczki (ang. pack expansion).  Paczka parametrów szablonu jest
rozwijana do listy parametrów szablonu oddzielonych przecinkami:

```cpp
{% include_relative expansion.cc %}
```

W przykładach wyżej argumenty szablonu musiały być jawnie podane, bo
funkcje i konstruktor nie miały zdefiniowanych parametrów i
przekazanych argumentów wywołania, na podstawie których argumenty
szablonu mogły być wywnioskowane.  Argumenty dla parametrów szablonu w
paczce są wnioskowane na podstawie definicji **paczki parametrów
funkcji** i argumentów wywołania funkcji.

## Paczka parametrów funkcji

Paczka parametrów funkcji jest definiowana w liście parametrów funkcji
także z użyciem trójkropka: pierwsze podajemy nazwę paczki parametrów
szablonu, trójkropek, a następnie nazwę paczki parametrów funkcji.  Co
ciekawe, definicja paczki parametrów funkcji jest jednocześnie
rozwinięciem paczki parametrów szablonu.

```cpp
{% include_relative fun_par_pack.cc %}
```

W przykładzie wyżej funkcja przyjmuje argumenty przez wartość.  Żeby
funkcja przyjmowała argumenty przez referencję stałą, to należy
zdefiniować paczkę parametrów jako `const Args &... args`.

### Rozwinięcie paczki

Rozwinięcie paczki parametrów funkcji zapisujemy jako nazwa paczki z
następującym trójkropkiem.

```cpp
{% include_relative factory.cc %}
```

Paczkę parametrów szablonu można rozwijać w zgraniu (ang. lockstep) z
paczką parametrów funkcji, np. kiedy inicjalizujemy obiekty bazowe
parametrami konstruktora klasy wyprowadzonej:

```cpp
{% include_relative lockstep.cc %}
```

# Przetwarzanie rekurencyjne

Argumenty funkcji możemy przetwarzać rekurencyjnie z użyciem paczek
parametrów.  Sztuczka polega na zdefiniowaniu dwóch parametrów
funkcji: pierwszy jest zwykły, do przetworzenia przez bieżące
wywołanie, a drugi jest paczką do przetworzenia przez wywołanie
rekurencyjnego.  Paczka jest rozwijana w listę argumentów wywołania
rekurencyjnego.  W ten sposób paczka parametrów wywołania
rekrencyjnego nie ma już pierszego parametru z paczki bieżącego
wywołania.

```cpp
{% include_relative recursive.cc %}
```

# Wyrażenie złożenia

Wyrażenie złożenia (ang. a fold expression, od C++17) jest przepisem
na wygenerowanie *docelowego (zamierzonego) wyrażenia* z użyciem
dowolnego **dwuargumentowego operatora `op`** i paczki parametrów.
Wyrażenie tak się nazywa, bo składa (jak obrus) docelowe wyrażenie
(to, które sami napisalibyśmy "ręcznie") do skompresowanego zapisu.
Wyrażenie złożenia jest rozwijane, konkretyzowane dla danej paczki
parametrów, co eliminuje potrzebę przetwarzania rekurencyjnego.
Wyrażenie złożenia poznajemy po trójkropku i nawiasach.  Są cztery
wersje: dwie jednoargumentowe i dwie dwuargumentowe, które używają
tego samego operatora `op`.

Częścią wyrażenia złożenia jest wyrażenie `E`, które używa paczki `p`.
Wyrażenie złożenia jest rozwijane przez konkretyzowanie wyrażenia `E`
dla kolejnych parametrów paczki `p`.  Wyrażenie `E` skonkretyzowane
dla parametru p<sub>i</sub> zapisujemy jako E<sub>i</sub>.

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
{% include_relative unary_left.cc %}
```

Przykład poniżej pokazuje konieczność użycia prawego wyrażenia:

```cpp
{% include_relative unary_right.cc %}
```

## Wersja dwuargumentowa

Wersje dwuargumentowe wymagają drugiego argumentu, którym jest
wyrażenie inicjalizujące `A`.

* wersja lewa `(A op ... op E)` -> ((A op E<sub>1</sub>) op ...)

* wersja prawa `(E op ... op A)` -> (... op (E<sub>n</sub> op A))

Strumienie wejścia-wyjścia są często wyrażeniem inicjalizującym
dwuargumentowego wyrażenia złożenia, jak w przykładzie niżej.
Wyrażenie musi być lewe, bo:

* pierwszym argumentem operatora przekierowania (`>>` czy `<<`) jest
  strumień (wejściowy czy wyjściowy),

* operator przekierowania zwraca strumień, który otrzymał jako pierwszy
  argument,

* strumień zwracany przez wyrażenie przekierowania staje się pierwszym
  argumentem kolejnego wyrażenia przekierowania.

```cpp
{% include_relative binary_left.cc %}
```

Oto przykład z prawym wyrażeniem:

```cpp
{% include_relative binary_right.cc %}
```

## Z dwuargumentowego do jednoargumentowego

Jeżeli dodalibyśmy wyrażenie `A` na początek paczki, to moglibyśmy
skorzystać z jednoargumentowego wyrażenia złożenia, ale byłoby to
niewygodne i mniej ekspresywne, jak pokazano niżej:

```cpp
{% include_relative force_unary.cc %}
```

## Krótki a trudny przykład: lista oddzielona przecinkami

Przykład niżej używa operatora przecinka, który jest nietypowy,
ponieważ łączy dwa niezależne wyrażenia.  Łączone wyrażenia nie mają
ze sobą nic wspólnego i są opracowywane niezależnie.  Przecinek
gwarantuje jedynie, że pierwsze będzie wykonane pierwsze wyrażenie,
zatem nawiasy z drugiego wyrażenia nie mogą mieć wpływu na kolejność
wykonania pierwszego wyrażenia.  W poniższym przykładzie, nawiasowanie
nie ma wpływu na wynik, ponieważ kolejność opracowania wyrażeń z
operatorem `<<` ustalają przecinki.

```cpp
{% include_relative comma.cc %}
```

Przykład niżej używa wersji lewej, gdzie `E` to `(std::cout << ", " <<
p)` a operatorem jest przecinek.  Jeżeli paczka `p` jest pusta, to
wyrażenie złożenia jest puste.  Jeżeli `p` ma jeden parametr, to
kompilator dokooptowuje dodatkowy pusty parametr, jeżeli taki istnieje
(dla operatora `,` jest nim `void()`), bo `op` wymaga dwóch
argumentów.  Żeby na początku nie wypisać samego przecinka, to
pierwszy parametr wypisujemy poza paczką (tak, jak w przetwarzaniu
rekurencyjnym), a wypisanie każdego parametru z paczki jest
poprzedzone wypisaniem przecinka.

```cpp
{% include_relative complex.cc %}
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
