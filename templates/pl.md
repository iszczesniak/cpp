---
title: Szablony
---

# Szablony

Szablon może być:

* funkcji,

* klasy, struktury, unii,

* składowej klasy (funkcji składowej, pola składowego),

* aliasu typu,

* zmiennej,

* konceptu.

Deklaracje i definicje szablonów rozpoczynają się słowem kluczowym
`template` z taką składnią:

```cpp
template <parameter list>
```

Mówimy, że szablon jest *sparametryzowany*, bo ma parametry, które
nazywamy **parametrami szablonu**.  Parametr jest zdefiniowany w
liście parametrów (`parameter list` powyżej) i ma nazwę, którą
następnie używamy w deklaracji czy definicji szablonu.

Kiedy używamy szablonu (np. wywołujemy funkcję zdefiniowaną
szablonem), to po jego nazwie możemy podać **argumenty szablonu** w
znakach `<>`.  **Konkretyzacja** szablonu **podstawia** argument
szablonu w miejsca wystąpienia parametru szablonu.  Mówimy także, że
parametr przyjmuje argument.

Terminy parametru i argumentu szablonu są analogiczne do terminów
**parametru i argumentu funkcji**, ale ta analogia jest jedynie
powierzchowna.  Inicjalizacja parametru funkcji z użyciem argumentu
funkcji ma dużo szczegółów (jak na przykład konwersje typów czy
inicjalizacja referencji), które nie odnoszą się do podstawienia.
Podstawienie jedynie sprawdza czy argument jest poprawny, czyli że
jest typem, wartością czy typem szablonowym, zgodnie z **rodzajem
parametru**.  Wniosek: **podstawienie to nie inicjalizacja**.

# Parametry szablonu

Parametry szablonu są zdefiniowane w liście parametrów, gdzie są
oddzielone przecinkami.  Definicja parametru ustala rodzaj i
opcjonalną nazwę parametru.  Rodzaje parametrów to: typ, wartość,
szablon.  Przykład poniżej ma trzy parametry: `T` typowego rodzaju,
nienazwany parametr wartościowego rodzaju i `C` szablonowego rodzaju.

```cpp
template <typename T, int, template<typename> typename C>
```

## Rodzaj parametru: typ

Nazwijmy to prosto: **typowy parametr szablonu**.  I typowy on jest
też dlatego, że tego rodzaju parametr jest najczęstszy.  Typowy
parametr definiujemy pisząc `typename T`.  Słowo kluczowe `typename`
mówi, że chodzi o typowy parametr, a `T` jest nazwą parametru.  Możemy
również równoważnie napisać `class T`, ale nowocześniej jest `typename
T`.

Konkretyzacja może podstawić za `T` dowolny konkretny typ: typ
wbudowany (np. `int`), typ użytkownika (np. `A`), typ szablonowy
(np. `vector<int>`), a nawet `void`.  Konkretny, czyli nie szablon
typu.  `T` nie musi spełniać żadnych warunków, np. nie musi
dziedziczyć z klasy bazowej.  Wymagania dotyczące typu `T` wynikają z
jego użycia w definicji szablonu, czyli czy, na przykład:

* tworzymy domyślną wartość typu `T`, czyli `T{}`,

* dodajemy, używając `operator+`, wartości typu `T`,

* wyłuskujemy, używając `operator&`, wartość typu `T`,

* przekazujemy jakiejś funkcji, np. `push_back`, wartość typu `T`,

* piszemy do `std::ostream` wartość typu `T` z użyciem `operator<<`.

To jest przykład funkcji szablonowej z typowym parametrem, gdzie
kompilator jest w stanie **wywnioskować argument szablonu**, więc nie
musimy go jawnie podawać podczas wywołania funkcji:

```cpp
{% include_relative print1.cc %}
```

## Rodzaj parametru: wartość

Nazwijmy to prosto: **wartościowy parametr szablonu**.  Parametr tego
rodzaju definiujemy pisząc `some_type I`, gdzie `some_type` jest
typem, np. `int`.  Typ `some_type` nie jest dowolny, tylko nieduży
zbiór typów jest dozwolony, a najczęściej używane są typy całkowite.
Podczas kompilacji za `I` podstawiana jest wartość tego typu, np. 1
dla parametru szablonu zdefiniowanego jako `int I`.

Przykład definicji wartościowego parametru szablonu:

```cpp
template <int N>
```

To jest przykład szablonu funkcji z wartościowym parametrem szablonu
`N`, którego argument musi być jawnie podany, bo kompilator nie jest w
stanie go wywnioskować:

```cpp
{% include_relative print2.cc %}
```

W przykładzie niżej mamy dwa przeciążenia szablonu funkcji
(przeciążenia, bo mają tą samą nazwę).  Drugi szablon ma wartościowy
parametr szablonu `N` i typowy parametr szablonu `T`, którego argument
może być wywnioskowany:

```cpp
{% include_relative print3.cc %}
```

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez instrukcję warunkową czasu kompilacji
`if constexpr`:

```cpp
{% include_relative print4.cc %}
```

Jednymi z dozwolonych typów wartościowych parametrów szablonu są
wskaźniki i referencje na funkcje:

```cpp
{% include_relative callback.cc %}
```

## Rodzaj parametru: szablon

Nazwijmy to tak: **szablonowy parametr szablonu**.  Taki parametr
przyjmuje (jako swój argument) szablon typu o wymaganym interfejsie.
Definicja szablonowego parametru `T` definiuje (przez listę parametrów
`parameter-list`) interfejs dopuszczalnych szablonów typu:

```cpp
template <parameter-list> typename T
```

Tutaj używamy parametu `T`:

```cpp
template <template <parameter-list> typename T>
```

W przykładzie niżej, za szablonowy parametr `C` może być podstawiony
dowolny typ szablonowy, którego pierwszy parametr jest typowy, a drugi
wartościowy.

```cpp
{% include_relative template1.cc %}
```

Za `__PRETTY_FUNCTION__` kompilator (Clang, GCC) podstawia nazwę
funkcji z argumentami szablonu, więc możemy sprawdzić w jaki sposób
szablon funkcji został skonkretyzowany.

Szablonowy parametr pozwala wywnioskować argumenty skonkretyzowanego
typu szablonowego:

```cpp
{% include_relative template2.cc %}
```

Szablonowy parametr pozwala przerwać zależność cykliczną między typami
szablonowymi:

```cpp
{% include_relative circular.cc %}
```

# Argumenty szablonu

Argumenty szablonu mogą być:

* wnioskowane przez kompilator (najczęściej stosowane),

* jawnie podane przez programistę (czasami niezbędne),

* domyślnie podane przez programistę (czasami wygodne).

Ten przykład pokazuje wyżej wymienione przypadki:

```cpp
{% include_relative intro.cc %}
```

Zanim przejdziemy do wnioskowania, pierwsze omówimy jawne i domyślne
argumenty szablonu.

## Jawnie podane argumenty szablonu

Kiedy korzystamy z kontenerów biblioteki standardowej (a każdy robił
to na pewno), możemy jawnie podać argumenty szablonu jako część nazwy
typu używając `<>`, czyli składni `typ<lista argumentów>`:

```cpp
{% include_relative explicit1.cc %}
```

Tej składni możemy też użyć przy wywołaniu funkcji szablonowej
(robiliśmy to już wyżej), co jest niezbędne w dwóch przypadkach:

* chcemy innych argumentów niż te wnioskowane przez kompilator,

* musimy jawnie podać argumenty, bo kompilator nie byłby w stanie ich
  wywnioskować.

Kompilator wnioskuje argumenty szablonu na podstawie wyrażeń, które są
przekazywane jako argumenty wywołania funkcji (kiedy wywołujemy
funkcję) czy konstruktora (kiedy tworzymy obiekt).  Jeżeli kompilator
nie jest w stanie wywnioskować argumentów szablonu, to musimy jawnie
je podać.

Przykład niżej pokazuje implementację fabryki obiektów.  Argument
wywołania `factory` przekazujemy do konstruktora obiektu, którego typ
jest określony przez argument szablonu.  Kompilator nie jest w stanie
określić typu tworzonego obiektu, więc musimy go jawnie podać.

```cpp
{% include_relative explicit2.cc %}
```

### Kolejność argumentów

Kolejność argumentów szablonu ma znaczenie (tak jak w przypadku
argumentów wywołania funkcji), bo argumenty są pozycyjne, czyli od
pozycji argumenty zależy to, o który argument nam chodzi.  Tak więc
jeżeli chcemy podać drugi argument, to musimy podać też pierwszy
argument.

Jeżeli w powyższym przykładzie z fabryką zmienimy kolejność
argumentów, to typ argumentu wywołania konstruktora będziemy musieli
także podać jawnie, chociaż mógłby być wywnioskowany.  Po zmianie
kolejności musimy jawnie podać pierwszy argument, bo zapragnęliśmy
podać drugi argument:

```cpp
{% include_relative explicit3.cc %}
```

## Domyślne argumenty szablonu

Parametr szablonu (każdego rodzaju: typowy, wartościowy i szablonowy)
może mieć zdefiniowany domyślny argument, który będzie użyty jeżeli
nie podaliśmy argumentu jawnie i jeżeli kompilator nie jest w stanie
go wnioskować (bo, np., nie ma argumentu funkcji).  Domyślny argument
jest opcjonalny.

Domyślny argument podajemy po nazwie parametru z użyciem `=`.  Oto
przykład:

```cpp
{% include_relative default.cc %}
```

### Domyślne callable

Czasami trzeba przekazać callable jakiejś funkcji, ale nie zawsze to
callable jest wymagane.  Nie chcemy przekazywać wskaźnika i sprawdzać
w czasie uruchomienia, czy jest on `nullptr`, albowiem niewydajne i
nieciekawe.  Chcemy, żeby callable było wkompilowane, a w szczególnym
przypadku, żeby callable nie wprowadzało narzutu, jeżeli nie jest
wymagane.  Do tego właśnie przydaje się domyślny argument szablonu.

Rozwiązanie: typ callable jest parametrem szablonu z domyślnym
argumentem, którym jest pusty callable, czyli struktura z operatorem
wywołania o pustym ciele.  Musimy też podać domyślną wartość callable
(argumentu wywołania funkcji), czyli `{}` (bezargumentowe tworzenie
obiektu).  Oto super przykład:

```cpp
{% include_relative empty_callable.cc %}
```

# Podsumowanie

* Szablony są podstawą programowania uogólnionego w C++.

* Parametry szablonów są typowe, wartościowe albo szablonowe.

* Szablony funkcji są najciekawsze i najtrudniejsze pośród szablonów.

# Quiz

* Co to jest typowy parametr szablonu?

* Czego może być szablon?

* Argument a parametr szablonu.

<!-- LocalWords: lvalue lvalues rvalue -->
