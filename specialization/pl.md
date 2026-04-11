---
title: Specjalizacja szablonów
---

# Wprowadzenie

Możemy **specjalizować** szablon funkcji czy typu.  Szablon, który
specjalizujemy nazywamy **szablonem podstawowy** (ang. primary
template), żeby odróżnić go od specjalizacji, która też jest
szablonem.  Szablon specjalizacji nazywamy w skrócie specjalizacją.
Specjalizacja nadpisuje definicję swojego szablonu podstawowego.  Nie
można dalej specjalizować specjalizacji.

Szablon podstawowy (funkcji, typu) definiuje nazwę szablonu i jego
parametry: ich liczbę i rodzaje.  Specjalizacja musi mieć tą samą
nazwę (funkcji, typu) i dostarczyć wszystkie argumenty dla szablonu
podstawowego.

Specjalizacja może być **częściowa** (ang. partial specialization)
albo **jawna** (ang. explicit specialization).  Specjalizacja szablonu
funkcji może być tylko jawna (nie może być częściowa).  Specjalizacja
szablonu typu może być częściowa albo jawna.  W przeciwieństwie do
specjalizacji jawnej, częściowa specjalizacja pozwala na zdefiniowanie
parametrów szablonu, które są używane w argumentach szablonu
podstawowego.

# Przeciążenie szablonu podstawowego

Specjalizacja (a może lepiej "wyspecjalizowanie") ma dodatkowe
znaczenie w języku C++, który pozwala przeciążać szablony podstawowe
funkcji o tej samej nazwie, podobnie jak zwykłe funkcje.  Jeżeli
będzie można użyć więcej niż jednego szablonu podstawowego, to
kompilator wybiera najbardziej **wyspecjalizowany** szablon.  Nie
musimy specjalizować szablonu, żeby mówić o **najbardziej
wyspecjalizowanym szablonie podstawowym**.  W przykładzie niżej
definiujemy dwa szablony podstawowe funkcji `foo`, a następnie
wywołujemy funkcję `foo`.

```cpp
{% include_relative overloads_template.cc %}
```

Jak kompilator wybrał właściwy szablon dla dwóch wywołań funkcji w
przykładzie wyżej?  Pierwsze wywołanie przekazuje argument typu
całkowitego, więc wybór jest tylko jeden: szablon `A`.  Szablon `B`
nie może być użyty, bo kompilator nie jest w stanie wywnioskować
argumentu `B1` szablonu tak, żeby można byłoby zainicjalizować
parametr `b1` funkcji, co nazywa się **niepowodzeniem**, nie jest
błędem i nie kończy kompilacji.

To niepowodzenie nazywa się dokładnie **niepowodzeniem podstawienia**
(ang. substitution failure): kompilator próbuje wywnioskować
argumenty, żeby podczas konkretyzacji podstawić je za parametry.
Niepowodzenie eliminuje szablon z dalszego rozważania (wyboru
przeciążenia) i nie zgłasza błędu, co ma swój angielski akronim SFINAE
(ang. Substitution Failure Is Not An Error).

Drugie wywołanie jest ciekawsze.  Kompilator może użyć zarówno
szablonu `A`, jak i `B`, bo może skonkretyzować oba szablony używając
wywnioskowanych argumentów:

* szablon `A`: `void foo(A1)` z `A1 = int *`,

* szablon `B`: `void foo(B1 *)` z `B1 = int`.

Obie konkretyzacje tworzą funkcję szablonową `void foo(int *)`, którą
można już użyć w drugim wywołaniu.  Teraz problemem pozostaje, który
szablon wybrać do wygenerowania ciała tej funkcji szablonowej.

Podkreślmy, że kompilator w dwóch osobnych krokach:

1. tworzy zbiór kandydatów szablonów,

2. wybiera najbardziej wyspecjalizowany szablon ze zbioru kandydatów.

W pierwszym kroku, spośród dostępnych szablonów, kompilator wybiera
te, dla których można wywnioskować argumenty (pozostałe szablony są
ignorowane zgodnie z zasadą SFINAE).  Zwróćmy uwagę, że wyrażenie
wywołania jest brane pod uwagę tylko w pierwszym kroku, żeby wybrać
kandydatów, a **w drugim kroku, wyrażenie wywołania nie jest już brane
pod uwagę.**

W drugim kroku, wybierany jest najbardziej wyspecjalizowany kandydat.
Jeżeli kandydatów nie ma, to jest zgłaszany błąd.  Jeżeli jest tylko
jeden kandydat, to kandydata nie trzeba wybierać.  Jeżeli jest ich
wielu, to kandydaci porównywani są parami, żeby znaleźć ten
najbardziej wyspecjalizowany.  Jeżeli nie można wskazać najlepszego
kandydata (dochodzi do remisu), to zgłaszany jest błąd
niejednoznaczności.

Szczegóły wyboru są omówione [tutaj](../fitter/pl).  Mówiąc krótko
(choć enigmatycznie), pierwszy szablon jest mniej wyspecjalizowany niż
drugi (albo że drugi jest bardziej wyspecjalizowany niż pierwszy),
jeżeli pierwszy szablon będzie zawsze można użyć wtedy, kiedy można
użyć drugi, ale nie na odwrót (czyli drugi szablon nie zawsze będzie
można użyć wtedy, kiedy można użyć pierwszy).

W przykładzie wyżej szablon `B` jest bardziej wyspecjalizowany niż
szablon `A`, bo szablonu `B` nie można użyć w każdym przypadku, w
którym można użyć szablonu `A`.  Na przykład, funkcja szablonu `A`
może przyjąć liczbę całowitą, a szablon `B` już nie.  Zatem szablon
`B` jest najbardziej wyspecjalizowanym kandydatem (szablonem
podstawowym) dla drugiego wywołania funkcji.

# Specjalizacja szablonu funkcji

Szablon funkcji może być specjalizowany tylko jawnie, czyli wszystkie
argumenty szablonu podstawowego są jawnie podane: szablon jawnej
specjalizacji nie ma już parametrów (jego lista parametrów jest
pusta).  Tak więc deklaracja i definicja specjalizacji szablonu
funkcji rozpoczynają się nagłówkiem szablonu z pustą listą parametrów:

```
template <>
```

Potem następuje definicja szablonu funkcji, która wygląda jak
definicja zwykłej (nieszablonowej) funkcji, bo nie używamy w niej
(czyli w liście parametrów funkcji i ciele funkcji) nazw parametrów
szablonu podstawowego, a jedynie ich argumentów (np. `int`, `1` czy
`std::list`).  Ale jest pewna różnica dotycząca nazwy funkcji: w
specjalizacji podajemy (jawnie) listę argumentów szablonu podstawowego
po nazwie funkcji, czego w definicji zwykłej funkcji nie robimy.

Oto przykład:

```cpp
{% include_relative foo1.cc %}
```

Szablon podstawowy czy specjalizację możemy także tylko zadeklarować.
Jeżeli zadeklarujemy szablon podstawowy i go później nie zdefiniujemy,
to nie będzie implementacji tego szablonu podstawowego funkcji.
Będziemy mogli specjalizować ten szablon i używać go wyłącznie dla
zdefiniowanych specjalizacji.

```cpp
{% include_relative foo2.cc %}
```

## Wnioskowanie argumentów jawnej specjalizacji

Przykład wyżej (nie niżej) pokazuje także, że nie musimy podawać
argumentów szablonu podstawowego, jeżeli kompilator jest w stanie je
wywnioskować na podstawie listy parametrów funkcji.  Na przykład,
pominęliśmy listę argumentów `<int>` szablonu podstawowego po nazwie
funkcji `foo` w deklaracji specjalizacji nr 1, bo kompilator jest w
stanie wywnioskować ten argument na podstawie definicji typu `const
int &` parametru funkcji.  Może się też okazać, jak w zakomentowanej,
błędnej specjalizacji nr 3, że argumentu nie da się wywnioskować.
Wywnioskować, ale jak?  Do wnioskowania potrzebny jest argument
wywołania funkcji, a tu go brak.

Standard mówi ([temp.deduct.decl]), że wnioskowanie odbywa się tak,
jak w przypadku funkcyjnego typu parametu funkcji.  W przykładzie
niżej, funkcja `primary` ma parametr typu `void (const T &t)`
podstawowego szablonu funkcji `foo` z przykładu wyżej, a funkcje
`spec1`, `spec2` i `spec3` są typu specjalizacji nr 1, 2 i 3 funkcji
`foo`.

Jeżeli w przykładzie wyżej odkomentujemy specjalizację nr 3 albo
przykładzie niżej odkomentujemy trzecie wywołanie funkcji `primary`,
to otrzymujemy ten sam błąd kompilacji:

`could not match 'const T &' against 'bool'`

```cpp
{% include_relative deduction.cc %}
```


## Szablon podstawowy funkcji a zwykła funkcja

Czy możemy się obyć bez szablonów?  Czy przeciążenia zwykłych funkcji
nie wystarczą?  W przykładzie niżej funkcja `foo` jest przeciążona,
żeby można użyć różnych implementacji w zależności od argumentu
funkcji.  Problem w tym, że dla każdego wymaganego typu musimy
implementować przeciążenie, albo korzystać z konwersji niejawnej, jak
w przykładzie niżej: dla argumentu `'1'` typu `char` jest wywołane
przeciążenia dla typu `int`.

```cpp
{% include_relative overloads_function.cc %}
```

W powyższym przykładzie zamieńmy przeciążenie zwykłej funkcji dla
`const int &` na szablon podstawowy, żeby jedną implementacją załatwić
wywołania `foo(1)` i foo('1').  Zatem w przykładzie niżej mamy szablon
podstawowy dla dowolnego typu i zwykłą funkcję dla typu `std::string`.
Czy dla wywołania funkcji `foo` z argumentem `std::string()` będzie
użyty podstawowy szablon funkcji czy zwykła funkcja?  **Zwykła funkcja
zawsze ma pierwszeństwo.**

```cpp
{% include_relative mix1.cc %}
```

Dla podstawowego szablonu funkcji możemy dodać specjalizację dla
`std::string`, ale kompilator i tak używa zwykłej funkcji.  Podczas
wyboru przeciążenia, kompilator nie rozważa specjalizacji, a jedynie
przeciążenia zwykłych funkcji i przeciążenia podstawowych szablonów
funkcji.

```cpp
{% include_relative mix2.cc %}
```

## Kiedy potrzebujemy specjalizacji

Wydaje się, że specjalizacja podstawowego szablonu funkcji jest
zbędna, bo przeciążenie zwykłej funkcji oferuje podobną (a nawet
lepszą, bo mającą pierszeństwo) funkcjonalność: zarówno specjalizacja
(która jest tylko jawna) jak i przeciążenie są (zdefiniowane,
przeznaczone) dla określonego typu argumentu funkcji.  Jest jednak
funkcjonalność specjalizacji, której nie osiągniemy przez
przeciążenie.

Specjalizacja szablonów pozwala użytkownikowi na dostarczenie
implementacji dla kodu (na przykład funkcji sortującej), który został
już dołączony w pliku nagłówkowym, np. biblioteki standardowej.
Biblioteka deklaruje podstawowy szablon funkcji, której wymaga, a
definicję specjalizacji czy nawet szablonu podstawowego pozostawia
użytkownikowi.  Tak może wyglądać plik nagłówkowy `library.hpp`:

```cpp
{% include_relative library.hpp %}
```

Tak może wyglądać użycie biblioteki:

```cpp
{% include_relative library.cc %}
```

C++ jest kompilatorem jednego przebiegu (ang. one-pass compiler), więc
jeżeli zwykłą funkcję `foo` zadeklarujemy po dołączeniu naszej
biblioteki, to funkcja biblioteczna `goo` nie zna jej i nie może jej
wywołać.  Natomiast funkcja `goo` zna i może użyć podstawowego
szablonu funkcji `foo`, bo został wcześniej zadeklarowany.

Moblibyśmy przenieść definicję zwykłej funkcji `foo` przed dyrektywę
`#include`, żeby funkcja `goo` mogła ją wywołać, ale lepiej nie
wprowadzać takiego nieporządku.

## Ciekawostki

Przykłady niżej ilustrują ciekawostki związane z szablonami funkcji.

### Częściowa specjalizacja szablonu funkcji?

Nie możemy częściowo specjalizować szablonu funkcji.  W przykładzie
niżej, zakomentowana specjalizacja definiowałaby parametry szablonu i
jawne argument szablonu podstawowego, ale to nie jest dozwolone.

```cpp
{% include_relative explicit.cc %}
```

### Przerwanie rekurencji

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu.  W
specjalizacji musimy podać argument `0` parametru `N`, bo kompilator
nie jest w stanie go wywnioskować.  Nie podaliśmy jednak argumentu
`int` dla parametru `T`, bo kompilator może go sobie wywnioskować.
Zauważmy, że tak to się robiło kiedyś (ten przykład to jedynie
kuriozum), bo od C++11 mamy do tego instrukcję warunkową czasu
kompilacji.

```cpp
{% include_relative print.cc %}
```

# Specjalizacja szablonów typów

Możemy zadeklarować lub zdefiniować szablon typu, czyli struktury,
klasy czy unii.  Ten szablon podstawowy możemy specjalizować jawnie
lub częściowo.  Szablon podstawowy i jej specjalizacje mają jedynie
wspólną nazwę typu, a ich interfejsy (składowe publiczne),
implementacje i wielkości w pamięci mogą się całkowicie różnić.

Przykładem specjalizacji typu w bibliotece standardowej jest
`std::vector<bool>`, czyli specjalizacja `std::vector` dla typu
`bool`.  Ta specjalizacja ma interfejs podobny do interfejsu szablonu
podstawowego, ale jej implementacja jest zupełnie inna.

## Przykład jawnej specjalizacji

Niżej definiujemy szablon podstawowy typu `A` z jedną funkcją składową
`foo`.  Dla jawnej specjalizacji dla argumentu `double`, typ `A`
dziedziczy po `std::pair`, ma funkcję `goo`, ale nie ma już funkcji
`foo`.

```cpp
{% include_relative struct_explicit.cc %}
```

## Częściowa specjalizacja i przykład

Szablon częściowej specjalizacji definiuje od nowa swoje parametry,
które nie muszą mieć nic wspólnego z parametrami szablonu
podstawowego.  Ważne jedynie, żeby jawnie podać (po nazwie typu)
argumenty szablonu podstawowego, które muszą zależeć od (używać)
parametrów specjalizacji.

W przykładzie niżej deklarujemy szablon podstawowy typu `A` z typowym
parametrem `T`, a następnie definiujemy dwie specjalizacje, obie z
parametrem `T`.  Parametry `T` trzech szablonów nie mają ze sobą nic
wspólnego, ponieważ mają lokalny zakres.

Pierwsza specjalizacja definiuje implementację typu `A` dla przypadku,
gdzie argumentem szablonu podstawowego jest `std::vector`.  Pozwalamy
na dowolny typ elementów wektora poprzez użycie parametru `T`
specjalizacji.

Druga specjalizacja definiuje implementację typu `A` dla przypadku,
gdzie argumentem szablonu podstawowego jest szablon typu, który może
być skonkretyzowany z jednym argumentem `int`.

W funkcji `main` typ `A` został użyty z dwoma specjalizacjami.
Najciekawsze jest ostatnie użycie, które jest zakomentowane, bo nie
może się kompilować: kompilator nie jest w stanie zdecydować, której
specjalizacji użyć.

```cpp
{% include_relative struct_partial.cc %}
```

# Podsumowanie

* Specjalizować można szablon funkcji i szablon typu.

* Specjalizacja może być częściowa albo jawna.

* Specjalizacja pozwala na nadpisanie implementacji szablonu
  podstawowego.

# Quiz

* Czy szablon funkcji może być częściowo specjalizowany?

* Czy w wyborze przeciążenia pierwszeństwo ma funkcja szablonowa czy
  zwykła funkcja?

* Czy specjalizacja szablonu typu dziedziczy po podstawowym szablonie
  typu?

<!-- LocalWords: lvalue lvalues rvalue -->
