---
title: Wnioskowanie argumentów szablonu
---

# Wprowadzenie

Argumenty szablonu są wnioskowane dla naszej wygody, żeby nie trzeba
było ich jawnie podawać i nie pomylić się przy okazji.  Kompilator
wnioskuje argumenty szablonu w następujących przypadkach:

* wywołanie nieskładowej funkcji szablonowej (najczęstsze i
  najprostsze),

* wywołanie składowej funkcji szablonowej (w tym konstruktora),

* inicjalizacja zmiennej typu `auto` (w tym parametrów funkcji i
  zwracanych wartości).

# Podstawy wnioskowania

Wnioskowanie omówimy na przykładzie nieskładowej funkcji szablonowej.
Dla wywołania **funkcji szablonowej**, kompilator musi skonkretyzować
**szablon funkcji**, czyli wygenerować kod funkcji szablonowej na
podstawie szablonu funkcji i jego argumentów.

Kompilator wnioskuje argumenty szablonu (funkcji) na podstawie:

* **typów** parametrów funkcji,

* **typów i kategorii** argumentów wywołania funkcji.

Wpływ kategorii argumentu na wnioskowanie jest dosyć skomplikowany i
opisany w oddzielnym temacie doskonałego przekazywania argumentów.

## Najprostszy przypadek

W najprostszym przypadku wywołujemy funkcję z jednym parametrem:

```cpp
template <parameter list>
void
foo(ParameterType t)
{
  // Body of a function template.
}

int
main()
{
  foo(expr);
}
```

Kompilator ma wywnioskować argumenty dla parametrów (tych z `parameter
list`) szablonu funkcji `foo` na podstawie wyrażenia `expr` i typu
`ParameterType` parametru `t` funkcji `foo`.  Żeby można mówić o
wnioskowaniu, typ `ParameterType` musi zależeć od (użyć w swojej
definicji) co najmniej jednego parametru szablonu.  Sposobów
zdefiniowania typu `ParameterType` w zależności od parametrów szablonu
jest wiele, a my omówimy najważniejsze.

## Podstawowa zasada z ograniczeniem

**Zasada: wywnioskowany argument szablonu ma pozwolić na inicjalizację
parametru funkcji.**

Inicjalizacja zawsze odbywa się na podstawie argumentu (jawnego bądź
domyślnego) funkcji.

**Ograniczenie: inicjalizacja ma się odbyć bez konwersji typu.**

Mowa tu o konwersji typu argumentu `expr` wywołania funkcji do typu
`ParameterType` parametru funkcji.  Przy wywołaniu zwykłej
(nieszablonowej) funkcji tego ograniczenia nie ma (tam konwersje są
dozwolone).

Inicjalizacja parametru `t` w powyższym najprostszym przypadku wygląda
zatem tak:

```cpp
ParameterType t = expr;
```

Kompilator musi tak wywnioskować argumenty szablonu, których parametry
są użyte w definicji typu `ParameterType`, żeby inicjalizacja była
możliwa bez konwersji typu.  Może się to okazać niemożliwe, co
uniemożliwia konkretyzację szablonu.

Na przykład, jeżeli `ParameterType` jest typem referencyjnym na obiekt
stały typu `T`, gdzie `T` jest parametrem szablonu, a argumentem
wywołania funkcji jest `1`, to inicjalizacja wygląda tak:

```cpp
const T &t = 1;
```

Wywnioskowanym argumentem będzie `T = int`, bo wtedy ta inicjalizacja
jest możliwa bez konwersji typu.  Jeżeli jednak `ParameterType` jest
typem referencyjnym na obiekt niestały typu `T`, to inicjalizacja
wygląda tak:

```cpp
T &t = 1;
```

Wywnioskowanym argumentem będzie ciągle `T = int`, bo r-wartość typu
wbudowanego (literał `1`) jest typu niestałego (tak powiada standard).
Zatem konkretyzacja nie powiedzie się, bo l-referencja niestała `t`
nie może być zainicjalizowana r-wartością.

Coś jest nie tak z tym brakiem konwersji w przykładach wyżej:
`ParameterType` jest **`const int &`**, a wyrażenie `1` jest typu
**`int`**!  Gdzie tu zgodność?  To teraz precyzyjniej: typ
`ParameterType` parametru funkcji i typ argumentu `expr` mogą się
różnić wyłącznie kwalifikatorami i deklaratorem `&` najwyższego rzędu.
Te różnice są dopuszczalne z uwagi na zasady (opisane niżej)
inicjalizowania zmiennych.

## Najwyższego rzędu

Kwalifikatory i deklaratory typu mogą być najwyższego rzędu.

### Deklaratory

Deklaratory `*` typu wskaźnikowego i `&` typu referencyjnego mogą
znaleźć się w różnych miejscach w definiowanym typie.  **Deklaratorem
najwyższego rzędu** jest ten pierwszy od prawej strony.  Na przykład,
w typie `int * const &` deklaratorem najwyższego rzędu jest `&`.

### Kwalifikatory

**Kwalifikatory typu (`const` i `volatile`) najwyższego rzędu** mogą
występować w każdym typie za wyjątkiem typu referencyjnego.

#### Typ zwykły

Definiowany typ zwykły (niewskaźnikowy i niereferencyjny) może mieć
kwalifikatory typu najwyższego rzędu podane przed albo po nazwie
używanego typu, np. `const int` albo `int const` (i są to te same
typy).  Kwalifikatory te mają znaczenie wyłącznie na etapie kompilacji
(nie uruchomienia): kompilator nie może pozwolić modyfikować danej
typu `const`, a dostępu do danej typu `volatile` nie może
optymalizować.

**Swoboda.** Zmienną możemy inicjalizować wyrażeniem inicjalizującym,
nawet jeżeli ich typy (zwykłe) różnią się jedynie kwalifikatorami
najwyższego rzędu, bo chodzi tylko o kopiowanie wartości.  Przykład:

```cpp
{% include_relative cv_regular1.cc %}
```

Ta swoboda dotycz także inicjalizacji parametru funkcji z użyciem
argumentu funkcji, z czego wynika ograniczenie.

**Ograniczenie.** Nie można przeciążać funkcji pod względem
kwalifikatorów typu zwykłego (parametru funkcji), ponieważ
inicjalizacja parametru typu zwykłego (gdzie swoboda nie stawia
warunków dotyczących kwalifikatorów) nie jest w stanie wpłynąć na
wybór przeciążenia.

Te kwalifikatory (które są szczegółem implementacji ciała funkcji) i
tak nie mają znaczenia dla strony wywołującej funkcję i dlatego są
usuwane przez kompilator z sygnatury funkcji (nie są one częścią
interfejsu funkcji), żeby umożliwić konsolidację.  Proszę sprawdzić
(komendą `nm`) sygnatury funkcji w tablicy symboli programu poniżej.

```cpp
{% include_relative cv_regular2.cc %}
```

#### Typ wskaźnikowy

Kwalifikatory typu wskaźnikowego znajdują się na prawo od deklaratora
`*` najwyższego rzędu, czyli na końcu definicji typu (albo na początku
patrząc od prawej strony).  Odnoszą się one do zmiennej wskaźnikowej,
a nie do wskazywanych danych.

Tak jak w przypadku zmiennej zwykłego typu, zmienną wskaźnikową możemy
inicjalizować na podstawie wartości wskaźnika, nawet jeżeli ich typy
(wskaźnikowe) różnią się kwalifikatorami najwyższego rzędu, bo wartość
wskaźnika jest jedynie kopiowana i dlatego też nie możemy przeciążać
funkcji dla typów wskaźnikowych (parametrów funkcji) różniących się
kwalifikatorami najwyższego rzędu.  Przykład:

```cpp
{% include_relative cv_ptr1.cc %}
```

W typie wskaźnikowym, tuż po lewej stronie deklaratora `*` najwyższego
rzędu, możemy też podać kwalifikatory **najwyższego rzędu** dla typu
wskazywanych danych.  Kwalifikatory te możemy nazwać **niższego
rzędu**, jeżeli mówimy o typie wskaźnikowym.

**Warunek dla typu wskaźnikowego.** Kwalifikatory *niższego rzędu*
typu wskaźnikowego muszą zawierać kwalifikatory *najwyższego rzędu*
typu wskazywanych danych.

Oto przykład:

```cpp
{% include_relative cv_ptr2.cc %}
```

Ten warunek pozwala przeciążać funkcje dla typów wskaźnikowych
(parametru funkcji), które różnią się kwalifikatorami dla typu
wskazywanych danych.  Chodzi o możliwość przeciążenia pod względem
typu danych, do których odnosi się wskaźnik.  Oto przykład:

```cpp
{% include_relative cv_ptr3.cc %}
```

#### Typ referencyjny

Referencja albo nazywa pewną daną (np. element tablicy) albo jest
aliasem innej zmiennej.  Typ referencyjny nie ma kwalifikatorów
najwyższego rzędu, bo referencja ma wiernie odwzorować typ danej,
której jest aliasem: wyrażenie referencyjne jest zamieniane na
wyrażenie z tą daną, do której referencja się odnosi.  Co więcej,
referencję można tylko zainicjalizować, a potem już nie można jej
zmienić, żeby była aliasem innej danej, a kwalifikator `const`
najwyższego rzędu nie robiłby różnicy.  Tak więc, na przykład, typ
`int & const` jest niedopuszczalny.

Dlatego nie da się przeciążać funkcji dla typów referencyjnych
(parametru funkcji), które miałyby się różnić tylko kwalifikatorami
najwyższego rzędu.  Nawet deklaracja jednej funkcji jest niemożliwa,
jeżeli typ referencyjny jej parametru miałby mieć kwalifikator.

Podobnie jak w typie wskaźnikowym, tak i w typie referencyjnym, tuż po
lewej stronie deklaratora `&` najwyższego rzędu, możemy też podać
kwalifikatory **najwyższego rzędu** dla typu wskazywanych danych.
Kwalifikatory te możemy nazwać **niższego rzędu**, jeżeli mówimy o
typie referencyjnym.

**Warunek dla typu referencyjnego.** Kwalifikatory *niższego rzędu*
typu referencyjnego muszą zawierać kwalifikatory *najwyższego rzędu*
typu wskazywanych danych.

Oto przykład:

```cpp
{% include_relative cv_ref1.cc %}
```

Ten warunek pozwala przeciążać funkcje dla typów referencyjnych
(parametru funkcji), które różnią się kwalifikatorami dla typu
wskazywanych danych.  Chodzi o możliwość przeciążenia pod względem
typu danych, do których odnosi się referencja.  Oto przykład:

```cpp
{% include_relative cv_ref2.cc %}
```

## Typ wyrażenia

Każde wyrażenie w C++ jest typu niereferencyjnego, a więc i typ
argumentu funkcji jest niereferencyjny, nawet jeżeli wyrażeniem jest
nazwa referencji.  W standardzie napisano ([expr.type]), że kompilator
usuwa deklarator `&` najwyższego rzędu z typu wyrażenia przed jego
dalszym opracowaniem.

# Rodzaje argumentów

Dla każdego **rodzaju** parametru szablonu, kompilator może wnioskować
argument.  Najczęściej chcemy, żeby kompilator wnioskował typowe (w
tym szablonowe) argumenty, ale czasem też argumenty wartościowe.

## Typowy argument

Typowy argument szablonu jest wnioskowany dla typowego parametru
szablonu.  To wnioskowanie jest najbardziej złożone (w porównaniu do
rodzaju wartościowego czy szablonowego), bo rozróżnia:

* typ parametru funkcji, w szczególności:

  - **zwykły** (niewskaźnikowy i niereferencyjny) dla przekazywania
    przez wartość,

  - **wskaźnikowy** dla przekazywania przez wskaźnik (które jest
    po prostu przekazywaniem przez wartość),

  - **referencyjny** dla przekazywania przez referencję.

* typ argumentu wywołania funkcji, w szczególności:

  - **funkcyjny**,

  - **tablicowy**.

* kategorię argumentu (opisane w innym temacie).

W zależności od omawianych szczególnych (najważniejszych) typów
parametru funkcji (zwykłych, wskaźnikowych, referencyjnych) stosowane
są nieco różne zasady, które jednak wynikają z podstawowej zasady z
ograniczeniem.  Dla tych szczególnych typów, wnioskowany typ może
różnić się od typu argumentu wywołania funkcji wyłącznie
kwalifikatorami lub deklaratorami najwyższego rzędu.  Wnioskowanym
typem nigdy nie będzie typ referencyjny, bo argument funkcji nigdy nie
jest typu referencyjnego.

## Zwykły typ parametru funkcji

**Wywnioskowany argument szablonu jest typem argumentu funkcji z
pominięciem kwalifikatorów najwyższego rzędu.**

Chodzi o to, że inicjalizacja parametrów funkcji (przy przekazywaniu
argumentów wywołania przez wartość) kopiuje wartość argumentu
wywołania do parametru funkcji.  Wnioskowanie nie musi zadbać o
kwalifikatory typu, bo w ciele funkcji działamy na kopii.  W definicji
parametru możemy podać kwalifikatory, żeby poprosić kompilator o
pilnowanie się z tym parametrem.

Przykład:

```cpp
{% include_relative arg_type_val1.cc %}
```

Ten typ paramatru szablonu może także przyjąc argument typu
wskaźnikowego:

```cpp
{% include_relative arg_type_val2.cc %}
```

## Wskaźnikowy typ parametru funkcji

**Wywnioskowany argument szablonu jest typem argumentu funkcji z
pominięciem deklaratora `*` i kwalifikatorów *najwyższego* rzędu.
Kwalifikatory najwyższego rzędu dla *typu wskazywanych danych* też są
pomijane, jeżeli znajdują się w definicji typu parametru funkcji.**

Wyjaśnienie:

* Deklarator `*` najwyższego rzędu jest pomijany, bo on już jest w
  definicji typu parametru funkcji.

* Kwalifikatory najwyższego rzędu są pomijane, bo nie mają one
  znaczenia dla funkcji, która działa na kopii wartości argumentu
  przekazanego do niej (tak jak w przypadku zwykłego typu parametru
  funkcji).

* Jeżeli w definicji typu parametru funkcji podamy kwalifikatory
  najwyższego rzędu dla **typu wskazywanych danych**, to te
  kwalifikatory będą pominięte we wywnioskowanym typie.  Jeżeli nie
  zostały podane, to kwalifikatory (typu wskazywanych danych)
  zdefiniowane przez typ argumentu funkcji będą propagowane do
  wywnioskowanego typu, co pozwala na inicjalizację parametru funkcji.

```cpp
{% include_relative arg_type_ptr.cc %}
```

## Referencyjny typ parametru funkcji

**Wywnioskowany argument szablonu jest typem argumentu funkcji z
pominięciem tych kwalifikatorów najwyższego rzędu, które zostały
podane w definicji typu danych, do których referencyjny parametr
funkcji się odnosi.**

Chodzi o to, żeby referencyjny parametr funkcji rzeczywiście mógł być
zainicjalizowany: jeżeli typ argumentu wywołania jest stały (bądź
ulotny), to referencja musi odnosić się do danej typu stałego (bądź
ulotnego).  Pamiętajmy, że typ argumentu nigdy nie jest referencyjny.

Przykład:

```cpp
{% include_relative arg_type_ref.cc %}
```

### Przekazywanie funkcji

Funkcję możemy przekazać przez:

* referencję,

* wskaźnik,

* ale nie wartość.

Funkcję możemy przekazać przez *referencję* używając referencyjnego
typu parametru funkcji, a dokładnie typu `F &`, gdzie `F` jest typowym
parametrem szablonu.  Wywnioskowanym argumentem szablonu będzie typ
referencji na przekazywaną funkcję.  Przykład:

```cpp
{% include_relative foo_ref.cc %}
```

Funkcję możemy przekazać przez *wskaźnik* używając wskaźnikowego typu
parametru funkcji szablonowej, a dokładnie typu `F *`, gdzie `F` jest
typowym parametrem szablonu.  Wywnioskowanym argumentem szablonu
będzie typ przekazywanej funkcji.  Przykład:

```cpp
{% include_relative foo_ptr.cc %}
```

Zamianę nazwy funkcji na wskaźnik do niej nazywamy **rozpadem funkcji
na wskaźnik** (ang. decay), który pochodzi z języka C.  Z rozpadu
skorzystaliśmy wyżej podając nazwę funkcji jako argument wywołania
funkcji szablonowej.

Funkcję możemy także przekazać przez *wskaźnik* używając zwykłego
(niereferencyjnego i niewskaźnikowego) typu parametru funkcji, a
dokładnie typu `F`, gdzie `F` jest typowym parametrem szablonu.  Wtedy
wywnioskowanym argumentem szablonu będzie typ wskaźnikowy na funkcję.
Przykład:

```cpp
{% include_relative foo_val.cc %}
```

### Przekazywanie tablic języka C

Tablicę języka C możemy przekazać do funkcji szablonowej przez:

* referencję,

* wskaźnik,

* ale nie wartość.

Tablicę możemy przekazać przez *referencję* używając referencyjnego
typu parametru funkcji szablonowej, a dokładnie typu `A &`, gdzie `A`
jest typowym parametrem szablonu.  Wywnioskowanym argumentem będzie
typ tablicy.  Przykład:

```cpp
{% include_relative car_ref.cc %}
```

Tablicę możemy przekazać przez *wskaźnik* używając wskaźnikowego typu
parametru funkcji szablonowej, a dokładnie typu `A *`, gdzie `A` jest
typowym parametrem szablonu.  Wywnioskowanym argumentem będzie typ
tablicy.  Przykład:

```cpp
{% include_relative car_ptr.cc %}
```

Jeżeli typem parametru funkcji szablonowej jest zwykły typ
(niereferencyjny i niewskaźnikowy), a argumentem wywołania funkcji
będzie nazwa tablicy, to do funkcji zostanie przekazany wskaźnik na
pierwszy element tablicy (a nie wskaźnik na tablicę), bo:

* tablica rozpadnie się (ang. decay) na wskaźnik na pierwszy element
  tablicy,

* wywnioskowanym argumentem będzie typ wskaźnikowy na element tablicy.

Oto przykład z rozpadem:

```cpp
{% include_relative car_val.cc %}
```

## Wartościowy argument

Wartościowy argument szablonu jest wnioskowany tylko na podstawie typu
argumentu wywołania funkcji, z którego można ten argument
wywnioskować.  Częścią typu argumentu wywołania funkcji musi być pewna
wartość, którą potrzebujemy, i która staje się wywnioskowanym
wartościowym argumentem.

Jedynymi typami argumentu wywołania funkcji, na podstawie których
możemy wywnioskować wartościowy argument szablonu, to:

* typ tablicy języka C,

* dowolny typ szablonowy.

### Typ tablicy języka C

Oto przykład:

```cpp
{% include_relative carray.cc %}
```

### Dowolny typ szablonowy

Typy wartościowych parametrów obu szablonów muszą się zgadzać.  Te oba
szablony to:

* szablon funkcji: wartościowy parametr tego szablonu ma wywnioskowany
  argument,

* szablon typu: tego szablonowego typu jest argument wywołania
  funkcji.

Na przykład, wartościowy parametr `I` musi mieć typ `std::size_t`, bo
takiego typu jest wartościowy parametr typu szablonowego `std::array`:

```cpp
{% include_relative array.cc %}
```

# Wiele parametrów funkcji szablonowej

W przykładach wyżej używaliśmy tylko jednego parametru funkcji
szablonowej, więc parametry szablonu mogły być użyte w co najwyżej
jednej definicji typu parametru funkcji szablonowej.  Parametrów
funkcji szablonowej może być jednak dowolna liczba, a parametr
szablonu może być użyty w dowolnej liczbie definicji typów parametrów
funkcji szablonowej.  Jak wtedy wnioskowane są argumenty szablonu?

Wtedy wnioskowanie argumentów szablonu odbywa się niezależnie dla
każdej pary parametru funkcji i argumentu wywołania.  Dla każdej pary
wnioskowane są argumenty dla parametrów szablonu, które zostały użyte
w definicji typu tego parametru funkcji.  Jeżeli jakiś argument został
wywnioskowany więcej niż raz (czyli dla różnych par), to musi on być
taki sam, w przeciwnym razie wnioskowanie nie udaje się.

Podczas wnioskowania nie jest dopuszczalna konwersja typów.  W
przykładzie niżej wnioskowane są różne argumenty, bo nie jest
dopuszczalna konwersja różnych typów argumentów wywołania funkcji.
Zatem w poniższym przykładzie wnioskowanie nie udaje się:

```cpp
{% include_relative fail.cc %}
```

# Podsumowanie

* Argument szablonu może być wywnioskowany albo podany (jawnie albo
  domyślnie).

* Wnioskowanie argumentów szablonu zależy od typu parametru funkcji i
  typu argumentu wywołania funkcji.

* Żeby zrozumieć wnioskowanie, należy znać szczegóły dotyczące
  inicjalizacji zmiennych, wskaźników i referencji.

# Quiz

* Na podstawie czego wnioskowane są argumenty szablonu?

* Czy wnioskowanie uwzględnia typ wartości zwracanej przez funkcję?

* Co to jest rozpad tablicy?
