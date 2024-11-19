---
title: Doskonałe przekazywanie argumentów
---

# Wprowadzenie

Problemem do rozwiązania jest napisanie funkcji `f`, która wywołuje
funkcję `g` i **doskonale przekazuje** jej swój argument.  Doskonale,
czyli:

* bez kopiowania argumentu,

* z zachowaniem własności argumentu.

O typie parametru (w tym kwalifikatorach `const` i `volatile`) funkcji
`g` nic nie wiemy: może być dowolny.  Funkcja `g` może mieć też
przeciążenia i przeciążone szablony.  Chcemy napisać tylko jedną
implementację funkcji `f`, a więc musimy zaimplementować szablon
funkcji, żeby pozwolić na przyjmowanie argumentów dowolnego typu.  Ten
problem nazywamy **doskonałym przekazywaniem argumentu** (ang. perfect
argument forwarding).

Musimy zachować własności argumentu, żeby wyrażenie `f(<expr>)`
wywołało to samo przeciążenie funkcji `g` co wyrażenie `g(<expr>)`.
Problem sprowadza się do zachowania *kategorii* i *typu*
przekazywanego argumentu.

Jest to ujęcie problemu od C++11, ponieważ mowa o zachowaniu kategorii
argumentu: jeżeli funckja `f` otrzymała r-wartość (albo l-wartość), to
powinna przekazać do funkcji `g` też r-wartość (albo l-wartość).
Należy zachować kategorię, ponieważ r-wartość może wymagać specjalnego
traktowania (chodzi o przenoszenie wartości).

Problem też istniał w starym C++ (przed C++11), ale kategoria wartości
nie miała szczególnego znaczenia, bo nie można jej było zachować
podczas przekazywania.  Wówczas chodziło o zachowanie wyboru jednego z
dwóch przeciążeń funkcji `g` dla parametru typu l-referencja:

* stała, np. `void g(A &);`,

* niestała, np. `void g(const A &);`.

Zadaniem jest napisanie takiego szablonu funkcji:

```cpp
template<typename T>
void
f(qualifiers_a type_a a)
{
  g(a); // Is calling like this enough?
}
```

**PYTANIE**: Czy można napisać taki szablon funkcji `f`?  Jakie mają
być kwalifikatory `qualifiers_a` i jaki typ `type_a`?  Czy
kwalifikatorem może, czy musi być `const`?  Czy typem ma być `T`, `T
&`, czy `T &&`?

**ODPOWIEDŹ**: Można, ale tylko od C++11, ponieważ tylko od C++11
zachowanie kategorii ma znaczenie.

## Dlaczego to problem?

Zadanie jest problematyczne, bo argumentem wywołania funkcji może być
albo l-wartość, albo r-wartość.  Są dwa podproblemy.

### Podproblem #1

Problemem jest określenie typu parametru funkcji, żeby mógł on być
zawsze zainicjalizowany, bez względu na typ i kategorię argumentu.
Ten podproblem już jest częściowo rozwiązany przez użycie szablonu
funkcji, ponieważ wnioskowanie argumentów szablonu nie dopuszcza do
konwersji typów.

### Podproblem #2

Problemem jest utrata kategorii argumentu.  W ciele funkcji, wyrażenie
z nazwą parametru funkcji jest zawsze l-wartością, nawet jeżeli
parametr jest r-referencją (która została zainicjalizowana
r-wartością).  Zachowanie kategorii argumentu funkcji `f` podczas
przekazywania go do funkcji `g` ma znaczenie, bo też kategoria (a nie
tylko typ) argumentu ma wpływ na wybór przeciążenia funkcji `g`.

## Motywacja: fabryki obiektów

Funkcje szablonowe `std::make_unique` i `std::make_shared` są
fabrykami obiektów.  Tworzą one obiekty i muszą przekazać swoje
argumenty do konstruktora klasy w niezmienionej postaci.

To jest przykład dla dwóch parametrów:

```cpp
template<typename T, typename A1, typename A2>
unique_ptr<T>
make_unique(qualifiers_a1 type_a1 a1,
            qualifiers_a2 type_a2 a2)
{
  return unique_ptr<T>(new T(a1, a2));
}
```

## Parametry i argumenty funkcji

* Parametry i argumenty funkcji to nie to samo!
* Parametr to zmienna dostępna w ciele funkcji.
* Argument to wyrażenie w wywołaniu funkcji.
* Parametry są *inicjalizowane* na podstawie argumentów.
* `void foo(int x);`, gdzie `x` jest parametrem funkcji
* `foo(a);`, gdzie `a` jest argumentem wywołania funkcji

Argument może być l-wartością albo r-wartością, a parametr zawsze jest
l-wartością, bo ma nazwę (możemy pobrać jego adres).

# Możliwe rozwiązania

Możliwe rozwiązania z pominięciem kwalifikatora `volatile`.

* przez wartość: `T`
* przez stałą wartość: `const T`
* przez l-referencję: `T &`
* przez stałą referencję: `const T &`
* przez r-referencję: `T &&`
* przez stałą r-referencję: `const T &&`

Nie bierzemy pod uwagę rozwiązań:

* `const T`, bo jest to przekazanie przez wartość, jak w przypadku
  `T`, z deklaracją, że parametru nie będziemy zmieniać,

* `const T &&`, bo nie znam zastosowania tego typu referencji.

## Rozwiązanie: `T`

Wygląda tak:

```cpp
template<typename T>
void
f(T t)
{
  g(t);
}
```

Gdy wykonamy `f(1)`, a funkcja `g` będzie pobierać argumenty przez
referencję, to nie otrzyma referencji na oryginalny obiekt, a
referencję na parametr funkcji `f`, który jest kopią oryginalnego
obiektu.  **Złe rozwiązanie.**

Zatem zostają nam trzy przypadki z referencjami do rozważenia:

* `T &`
* `const T &`
* `T &&`

## Rozwiązanie: `T &`

Wygląda tak:
  
```cpp
template<typename T>
void
f(T &t)
{
  g(t);
}
```

Jeżeli argumentem wywołania funkcji `f` jest r-wartość, to kompilacja
nie powiedzie się, bo l-referencja nie może być zainicjalizowana
r-wartością.  **Złe rozwiązanie.**

Przykład:

```cpp
{% include_relative bad1.cc %}
```

## Rozwiązanie: `const T &`

Wygląda tak:
  
```cpp
template<typename T>
void
f(const T &t)
{
  g(t);
}
```

Teraz będzie się kompilować dla r-wartości, np. `f(1)`, ale jeżeli
parametr funkcji `g` będzie niestałą l-referencją, to kod nie będzie
się kompilował, bo niestałej l-referencji nie można zainicjalizować
stałą referencją.  **Złe rozwiązanie.**

Przykład:

```cpp
{% include_relative bad2.cc %}
```

## Rozwiązanie: `T &` razem z `const T &`

Możemy mieć dwa przciążenia szablonów podstawowych: jeden dla `T &`, a
drugi dla `const T &`:

```cpp
template<typename T>
void
f(T &t)
{
  g(t);
}

template<typename T>
void
f(const T &t)
{
  g(t);
}
```

Ta implementacja rozwiąże podproblem #1, ale dla `n` parametrów
potrzebujemy `2^n` przeciążeń szablonów podstawowych!  W starym C++
było to jedyne możliwe rozwiązanie, więc wówczas było akceptowalne.
Kompatybilność wstecz jest zachowana: kompilator C++11 będzie
poprawnie kompilował stary kod (bez r-referencji).

Jednak w C++11 to rozwiązanie nie jest w stanie doskonale przekazać
r-wartości, bo nie uwzględnia ono przeciążenia z r-referencją.  **Od
C++11 jest to złe rozwiązanie.**

Przykład:

```cpp
{% include_relative bad3.cc %}
```

# Prawidłowe rozwiązanie: T &&

Od C++11, żeby rozwiązać podproblem #1, typ parametru powinien być
zadeklarowany jako r-referencja bez kwalifikatorów.

Prawda objawiona:

```cpp
template<typename T>
void
f(T &&t)
{
  g(std::forward<T>(t));
}
```

Jeżeli `T` jest parametrem szablonu, to parametr funkcji typu `T &&`
nazywamy **referencją przekazującą** (ang. forwarding reference).
Mimo, że deklarowanym typem jest r-referencja, to na etapie kompilacji
typ r-referencji może zostać przekształcony do typu l-referencji.

Prawda objawiona, bo dla referencji przekazującej wprowadzono w C++11
specjalne zasady wnioskowania typu `T` w zależności od kategorii
argumentu, co jest dalej wyjaśnione.

Problem w tym, że parametr `t` jest l-wartością (bo ma nazwę `t`),
nawet jeżeli argumentem wywołania funkcji `f` była r-wartość.  W ten
sposób tracimy informację o kategorii wartości wyrażenia, które było
argumentem wywołania funkcji `f`.  Funkcja `std::forward` odzyskuje tę
kategorię wartości, czego szczegóły są wyjaśnione niżej.

**Podproblem #1 został rozwiązany referencją przekazującą.**

**Podproblem #2 został rozwiązany funkcją `std::forward`.**

## Wnioskowanie dla referencji przekazującej

Jaki będzie wywnioskowany argument dla parametru `T` szablonu, jeżeli
jest on użyty w deklaracji referencji przekazującej?

Jeżeli argumentem funkcji `f` jest:

* l-wartość typu A, to `T = A &`,

* r-wartość typu A, to `T = A`.

### Konstruktor a referencja przekazująca

Wnioskowanie argumentów szablonu jest stosowane nie tylko przy
wywołaniu szablonów funkcji, ale także przy wywołaniu konstruktora
typu szablonowego.  Konstruktor dla typu szablonowego może mieć
parametr `T &&`, gdzie `T` jest parametrem szablonu, dla którego mogą
być użyte zasady wnioskowania dla referencji przekazującej.

Ale jest tu pewien niuans, którego nie potrafię uzasadnić
([temp.deduct.call#3]).  Parametr konstruktora typu `T &&`:

* jest referencją przekazującą, jeżeli `T` jest parametrem szablonu
  konstruktora,

* nie jest referencją przekazującą, jeżeli `T` jest parametrem
  szablonu typu.

Oto przykład:

```cpp
{% include_relative constructor.cc %}
```
    
## Referencja do referencji

W C++ nie ma typu *referencji do referencji*, ale takie typy mogą się
pojawić, jako efekt deklaracji referencji przekazującej, albo
definicji typów szablonowych z użyciem `using` czy `typedef`.

Jeżeli argumentem parametru szablonu `T` będzie `A &`, to wtedy typem
parametru funkcji, który został zadeklarowana jako referencja
przekazująca, będzie typ `A & &&`.  Co wtedy?

### Spłaszczanie typów referencyjnych

Jeżeli pojawi się typ referencji do referencji, to kompilator zamieni
taki typ na referencję według zasady:

* `cv1 A & cv2 &` -> `cv1 A &`
* `cv1 A & cv2 &&` -> `cv1 A &`
* `cv1 A && cv2 &` -> `cv1 A &`
* `cv1 A && cv2 &&` -> `cv1 A &&`

Zbiory `cv1` i `cv2` oznaczają zbiory kwalifikatorów, do których mogą
należeć `const` i `volatile`.  Zbiór `cv2`, który określałby
kwalifikatory zagnieżdżonego typu referencyjnego (tego z lewej
strony), jest pomijany, ponieważ typy referencyjne nie mają
kwalifikatorów.

Spośród powyższych czterech przypadków, dla referencji przekazującej
może wystąpić jedynie kombinacja `& &&`, kiedy argumentem funkcji jest
l-wartość.  Wtedy referencja przekazująca jest spłaszczana do
l-referencji, żeby można ją było zainicjalizować l-wartością.

Wyczerpujący test spłaszczania referencji z pominięciem `volatile`:

```cpp
{% include_relative collapse.cc %}
```

## Funkcja `std::forward`

Funkcja szablonowa `std::forward` przyjmuje l-wartość `t` typu `T` i w
zależności od argumentu szablonu zwraca:

* r-wartość dla `std::forward<T>(t)`
* l-wartość dla `std::forward<T &>(t)`

Funkcji `std::forward` używamy w definicji funkcji szablonowej, kiedy
trzeba odzyskać kategorię argumentu wywołania funkcji.

Przykład:

```cpp
{% include_relative forward.cc %}
```

### Przypadek wariadyczny

Funkcja może przyjmować przez referencję przekazującą dowolną liczbę
argumentów, które doskonale przekażemy, jak w przykładzie niżej.  To
jest też jedna z motywacji wprowadzenia szablonu wariadycznego:
implementacja funkcji `std::make_unique`.

```cpp
{% include_relative variadic1.cc %}
```

A tu skrócony zapis z użyciem specyfikatora `auto`:

```cpp
{% include_relative variadic2.cc %}
```

# Referencja przekazująca jako pole składowe

Referencją przekazującą może być polem składowym szablonowego typu
danych.

```cpp
{% include_relative field1.cc %}
```

# Rozbudowany przykład

Zdefiniujemy różne przeciążenia dla funkcji `g`.  Funkcja `g` będzie
przyjmowała też drugi parametr, który pozwoli nam stwierdzić, czy
kompilator wybrał to przeciążenie, które się spodziewaliśmy.  W
funkcji `main` wywołujemy każde przeciążenie funkcji.

Piszemy funkcję `f`, która doskonale przekazuje swój argument do
funkcji `g`.

Przykład:

```cpp
{% include_relative perfect.cc %}
```

Tutaj ten sam przykład, ale sprawdzający argument funkcji (ten drugi)
zamieniliśmy na sprawdzający argument szablonu.  Teraz sprawdzamy typ
w czasie kompilacji z użyciem `static_assert`:

```cpp
{% include_relative perfect2.cc %}
```

Co się stanie, jeżeli usuniemy funkcję `forward` z funkcji `f`?  Wtedy
będą przekazywane zawsze l-wartości do funkcji `g`.  Można sprawdzić.

# Podsumowanie

* Problem doskonałego przekazywania argumentów występuje w
  programowaniu uogólnionym z użyciem szablonów.

* Chodzi o przekazanie argumentów przez referencję (aby uniknąć
  kopiowania bądź przenoszenia) i wywołanie właściwego przeciążenia
  funkcji.

* Żeby doskonale przekazać argument wywołania funkcji, używamy
  referencji przekazującej i funkcji `std::forward`.

# Quiz

* Jakie są dwa podproblemy doskonałego przekazywania argumentów?

* Do czego służy funkcja `std::forward`?

* Co to jest referencja przekazująca?

<!-- LocalWords: inicjalizowane -->

<!-- LocalWords: podproblem -->
<!-- LocalWords: podproblemy -->

<!-- LocalWords: zainicjalizować -->
<!-- LocalWords: zainicjalizowana -->
<!-- LocalWords: zainicjalizowany -->

<!-- LocalWords: forwarding -->
<!-- LocalWords: main -->
<!-- LocalWords: reference -->
<!-- LocalWords: template -->
<!-- LocalWords: title -->
<!-- LocalWords: typedef -->
<!-- LocalWords: using -->
<!-- LocalWords: volatile -->
