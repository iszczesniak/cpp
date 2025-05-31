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
definicja zwykłej funkcji, bo nie używamy w niej (czyli w liście
parametrów funkcji i ciele funkcji) nazw parametrów szablonu
podstawowego, a jedynie ich ustalonych wartości (np. `int`, `1` czy
`std::list`).  Ale jest pewna różnica.

Różnica dotyczy nazwy funkcji.  W specjalizacji podajemy listę
argumentów szablonu podstawowego po nazwie funkcji, czego w definicji
zwykłej funkcji nie robimy.

Oto przykład:

```cpp
{% include_relative foo1.cc %}
```

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

```cpp
{% include_relative foo2.cc %}
```

Nie możemy częściowo specjalizować szablonów funkcji.  Specjalizacja
częściowa polegałaby na wprowadzeniu parametru dla specjalizacji, ale
nie jest to dozwolone, jak pokazuje przykład niżej.

```cpp
{% include_relative complete.cc %}
```

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu.  W
specjalizacji szablonu musimy podać argument `0` parametru `N`, bo
kompilator nie jest w stanie go wywnioskować.  Argument `int`
parametru `T` może być wywnioskowany, więc nie jest podany.

```cpp
{% include_relative print.cc %}
```

## Przeciążanie funkcji a szablony

Czy możemy się obyć bez szablonów?  W przykładzie niżej funkcja `foo`
jest przeciążona, żeby w zależności od argumentu wywołania funkcji
dostarczyć inną implementację.

Problem w tym, że nie mamy szablonu, który mógłby być zastosowany dla
dowolnego typu i dlatego dla argumentu `.2` typu `double` jest
wywołane przeciążenia dla typu `int`.

```cpp
{% include_relative overloads.cc %}
```

Możemy dołożyć szablon podstawowy do przykładu, jak pokazano niżej.
Mamy szablon dla dowolnego typu i przeciążenie dla typu `A`.  Czy dla
wywołania funkcji `foo` z argumentem `A()` będzie użyty szablon czy
przeciążenie?  A dokładnie mówiąc przeciążenie funkcji szablonowej
(czyli funkcji, która otrzymaliśmy po konkretyzacji podstawowego
szablonu funkcji dla `T = A`) czy przeciążenie zwykłej funkcji?
**Przeciążenie zwykłej funkcji zawsze ma pierwszeństwo.**

```cpp
{% include_relative mix1.cc %}
```

Możemy dodać także specjalizację dla `T = A`, ale i tak zostanie
wybrane przeciążenie zwykłej funkcji.  Podczas wyboru przeciążenia,
kompilator nie rozważa specjalizacji, a jedynie przeciążenia zwykłych
funkcji i przeciążenia funkcji szablonowych.  Tak więc dodanie
specjalizacji i tak nie namówi kompilator na jej użycie.

```cpp
{% include_relative mix2.cc %}
```

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

```cpp
{% include_relative library.hpp %}
```

Tak może wyglądać użycie biblioteki:

```cpp
{% include_relative need.cc %}
```

Jeżeli przeciążenie funkcji zadeklarujemy po dołączeniu biblioteki, to
funkcja `goo` nie będzie go znała i nie użyje go.  Funkcja wie
natomiast, że może użyć szablonu funkcji `foo`, bo jej szablon
podstawowy został zadeklarowany.

Możemy też przenieść definicję przeciążenia funkcji `foo` przed
dyrektywę `#include`, żeby funkcja `goo` mogła skorzystać z
przeciążenia, ale lepiej nie wprowadzać takiego nieporządku.

# Specjalizacja szablonów typów użytkownika

Możemy zadeklarować lub zdefiniować szablon typu użytkownika, czyli
struktury, klasy i unii.  Ten szablon podstawowy możemy specjalizować
całkowicie lub częściowo.  Szablon podstawowy i jej specjalizacje mają
jedynie wspólną nazwę typu, a ich interfejsy (składowe dostępne
użytkownikowi), implementacje i wielkości w pamięci mogą się
całkowicie różnić.

Przykładem specjalizacji typu w bibliotece standardowej jest
`std::vector<bool>`, czyli kontenera `std::vector` dla typu `bool`.
Ta specjalizacja ma podobny interfejs jak szablon podstawowy
`std::vector`, ale zupełnie inną implementację.

## Przykład całkowitej specjalizacji

Niżej definiujemy szablon podstawowy typu `A` z jedną funkcją składową
`foo`.  Całkowita specjalizacja dla argumentu `double` nie ma funkcji
`foo`, a ma funkcję `goo` i dziedziczy po `std::pair`.  Całkowita
specjalizacja typu ma identyczną składnię, jak całkowita specjalizacja
funkcji.

```cpp
{% include_relative struct_complete.cc %}
```

## Częściowa specjalizacja i przykład

W częściowej specjalizacji szablonu typu wprowadzamy parametr, który
używamy w definicji argumentu szablonu podstawowego.  Lista parametrów
specjalizacji nie jest już pusta, jak w przypadku całkowitej
specjalizacji.

W przykładzie niżej deklarujemy szablon podstawowy typu `A` z typowym
parametrem `T`, a następnie definiujemy dwie specjalizacje, obie z
parametrem `T`.  Parametry `T` trzech szablonów nie mają ze sobą nic
wspólnego, ponieważ mają lokalny zakres.

Pierwsza specjalizacja definiuje implementację typu `A` dla
przypadków, kiedy argumentem szablonu podstawowego jest `std::vector`.
Pozwalamy na dowolny typ elementów wektora poprzez użycie parametru
`T` specjalizacji.

Druga specjalizacja definiuje implementację typu `A` dla przypadków,
kiedy argumentem szablonu podstawowego jest typ szablonowy, który może
być skonkretyzowany z jednym argumentem `int`.

W funkcji `main` typ `A` został użyty z różnymi specjalizacjami.
Najciekawszy jest ostatni przypadek, który jest zakomentowany, bo nie
może się kompilować: kompilator nie jest w stanie zdecydować, której
specjalizacji użyć.

```cpp
{% include_relative struct_partial.cc %}
```

# Najbardziej wyspecjalizowany szablon podstawowy

Specjalizacja (a może lepiej "wyspecjalizowanie") ma dodatkowe
znaczenie w języku C++, który pozwala przeciążać szablony podstawowe
funkcji o tej samej nazwie.  Jeżeli będzie można użyć więcej niż
jednego szablonu, to kompilator wybiera najbardziej
**wyspecjalizowany** szablon.  Nie musimy specjalizować szablonu, żeby
mówić o najbardziej wyspecjalizowanym szablonie podstawowym.  W
przykładzie niżej definiujemy dwa szablony podstawowe funkcji `foo`, a
następnie wywołujemy funkcję `foo`.

```cpp
{% include_relative special1.cc %}
```

Jak kompilator wybrał właściwy szablon dla dwóch wywołań funkcji w
przykładzie wyżej?  Pierwsze wywołanie przekazuje argument typu
całkowitego, więc wybór jest tylko jeden: szablon A.  Szablon B nie
może być użyty, bo kompilator nie jest w stanie wywnioskować argumentu
`B1` szablonu tak, żeby można byłoby zainicjalizować parametr `b1`
funkcji.

Drugie wywołanie jest ciekawsze.  Kompilator może użyć zarówno
szablonu A, jak i B.  W tej sytuacji jest użyty **bardziej
wyspecjalizowany szablon**.  W tym przykładzie szablon B jest bardziej
wyspecjalizowany.

Zanim przejdziemy dalej (do omówienia idei bardziej wyspecjalizowanego
szablonu), to podsumujmy przykład i zauważmy ważny fakt.  Podczas
opracowania drugiego wywołania, kompilator może skonkretyzować oba
szablony używając wywnioskowanych argumentów:

* przeciążenie A: `void foo(A1)` z `A1 = int *`,

* przeciążenie B: `void foo(B1 *)` z `B1 = int`.

Obie konkretyzacje tworzą funkcję szablonową `void foo(int *)`, którą
można już użyć w drugim wywołaniu.  Teraz problemem pozostaje, które
przeciążenie szablonu wybrać do wygenerowania ciała tej funkcji
szablonowej.

Podkreślmy, że kompilator w dwóch osobnych krokach:

1. tworzy zbiór kandydatów przeciążeń szablonów podstawowych,

2. wybiera najlepsze (najbardziej wyspecjalizowane) przeciążenie ze
   zbioru kandydatów.

Kompilator tworzy zbiór kandydatów przez wybranie spośród dostępnych
przeciążeń tych, które można użyć dla danego wyrażenia wywołania,
czyli tak skonkretyzować, żeby uzyskaną funkcję szablonową można było
wywołać z argumentami tego wyrażenia wywołania.  Wiemy, że
konkretyzacja jest możliwa dla wywnioskowanych argumentów, zatem dla
każdego dostępnego przeciążenia przeprowadzane jest wnioskowanie z
użyciem wyrażenia wywołania: jeżeli wnioskowanie się udało, to
przeciążenie trafia do zbioru kandydatów, w przeciwnym razie jest
ignorowane zgodnie z zasadą SFINAE.

Zwróćmy uwagę na ważny fakt: **podczas wyboru najlepszego przeciążenia
ze zbioru kandydatów (w drugim kroku), wyrażenie wywołania nie jest
już brane pod uwagę.** Wyrażenie wywołania jest brane pod uwagę tylko
w pierwszym kroku, żeby wybrać kandydatów.

## Wybór najlepszego kandydata

Ze zbioru kandydatów wybieramy najlepszy szablon, czyli **najbardziej
wyspecjalizowany**.  Wyboru dokonujemy przez porównywanie szablonów
parami, czyli z użyciem binarnej relacji, którą oznaczymy jako <.
Porównując parę szablonów I i J chcemy określić, który szablon jest
bardziej wyspecjalizowany.  Zapis I < J czytamy: **I jest bardziej
wyspecjalizowany niż J**.

Jednak relacja < nie musi zachodzić między każdą parą szablonów i
dlatego nazywana jest **częściową**.  Ponieważ relacja jest częściowa,
to może okazać się, że kompilator nie jest w stanie wybrać najbardziej
wyspecjalizowanego przeciążenia i wted zgłasza błąd
niejednoznaczności.

Relacja < jest silnym porządkiem częciowym, ponieważ jest:

* częściowa,

* przeciwzwrotna, bo szablon nie jest bardziej wyspecjalizowany od
  siebie, czyli relacja I < I nigdy nie zachodzi,

* asymetryczna, bo jeżeli I < J, to relacja odwrotna (czyli J < I) nie
  zachodzi,

* przechodnia, bo jeżeli I < J i J < K, to naturalnie oczekujemy, że I
  będzie uznany za bardziej wyspecjalizowany niż K, czyli I < K.

Dla przykładu wyżej możemy powiedzieć, że dla drugiego wywołania
szablon B jest bardziej wyspecjalizowany niż A (relacja zachodzi: B <
A).  A ponieważ zbiór kandydatów ma tylko dwa szablony, więc szablon B
uznajemy za najbardziej wyspecializowany.

### Relacja "bardziej wyspecjalizowany"

Relacja "bardziej wyspecjalizowany" sprawdza **typy argumentów**
wywołania funkcji, które mogą być użyte z przeciążeniem.

Załóżmy, że przeciążenie l<sub>i</sub> można wywołać z argumentami
typu, które należą do zbioru t<sub>i</sub>, a przeciążenie
l<sub>j</sub> z argumentami typu, które należą do zbioru
t<sub>j</sub>.  Przeciążenie l<sub>i</sub> jest bardziej
wyspecializowane niż przeciążenie l<sub>j</sub>, jeżeli t<sub>i</sub>
jest podzbiorem właściwym t<sub>j</sub>.

W przykładzie wyżej, przeciążenie pierwsze l<sub>1</sub> przyjmuje
argumenty dowolnych typów ze zbioru T<sub>1</sub>, także
wskaźnikowych.  Drugie przeciążenie l<sub>2</sub> przyjmuje argumenty
dowolnych typów wskaźnikowych ze zbioru t<sub>2</sub>.  Przeciążenie
l<sub>2</sub> jest bardziej wyspecjalizowane niż l<sub>1</sub>,
ponieważ t<sub>2</sub> jest podzbiorem właściwym t<sub>1</sub>, a to
wiemy z zasad wnioskowania:

* pierwsze przeciążenie możemy użyć dla każdego argumentu typu `T2 *`
  (czyli typu parametru drugiego przeciążenia), bo możemy
  zainicjalizować parametr `T1 p1` wyrażeniem typu `T2 *`, ponieważ
  wtedy `T1` może być wywnioskowany jako `T1 = T2 *`,

* drugiego przeciążenia nie możemy użyć dla każdego argumentu typu
  `T1`, a jedynie dla typów wskaźnikowych, czyli parametr `T2 *p2`
  możemy zainicjalizować tylko wtedy, kiedy `T1` jest typem
  `T *`, bo tylko wtedy można wywnioskować `T2 = T`.

# Podsumowanie

* Specjalizować można szablony funkcji i typy szablonowe.

* Specjalizacja może być częściowa albo całkowita.

* Specjalizacja pozwala na nadpisanie implementacji szablonu
  podstawowego dla wybranych kombinacji jego argumentów.

# Quiz

* Czy szablon funkcji może być częściowo specjalizowany?

* Czy w wyborze przeciążenia pierwszeństwo ma funkcja szablonowa czy
  przeciążenie funkcji?

* Czy specjalizacja szablonu typu dziedziczy po podstawowym szablonie
  typu?

<!-- LocalWords: lvalue lvalues rvalue -->
