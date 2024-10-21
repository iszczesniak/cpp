---
title: Wnioskowanie argumentów szablonu
---

# Wprowadzenie

Argumenty szablonu są wnioskowane dla naszej wygody, żeby nie trzeba
było ich jawnie podawać i nie pomylić się przy okazji.  Kompilator
wnioskuje argumenty szablonu kiedy kompiluje wywołanie funkcji
szablonowej -- to jest najczęstsze zastosowanie.  Ale te same zasady
wnioskowania są też wykorzystywane kiedy *inicjalizujemy*:

* zmienną typu `auto` na podstawie wyrażenia inicjalizującego
  (np. `auto i = m.find(key);`), gdzie `auto` pełni rolę typowego
  parametru szablonu, którego argument kompilator wnioskuje,

* wynik typu `auto` zwracany przez funkcję na podstawie wyrażenia
  instrukcji `return`, gdzie `auto` pełni rolę typowego parametru
  szablonu, którego argument kompilator wnioskuje,

* obiekt klasy szablonowej na podstawie argumentów wywołania
  konstruktora (np. `pair p{1, .1};`), gdzie kompilator wnioskuje
  wymagane argumenty szablonu klasy.

Kiedy kompilator kompiluje wywołanie jakiejś **funkcji szablonowej**,
to musi skonkretyzować **szablon funkcji**, czyli wygenerować kod
funkcji szablonowej na podstawie szablonu funkcji i jego argumentów.
Jeżeli argumenty szablonu nie są jawnie podane, to kompilator musi je
wywnioskować, a jeżeli nie jest w stanie tego zrobić, to korzysta z
domyślnych argumentów, jeżeli są.

Kompilator wnioskuje argumenty szablonu (funkcji) na podstawie:

* **typów** parametrów funkcji,

* **typów i kategorii** argumentów wywołania funkcji.

Typ wyrażenia (czyli także argumentu funkcji) nigdy nie jest
referencyjny, nawet jeżeli wyrażeniem jest nazwa
referencji. [expr.type]

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

## Inicjalizacja parametrów funkcji szablonowej: bez konwersji

Ponieważ parametr funkcji jest inicjalizowany na podstawie argumentu
wywołania funkcji, to wywnioskowane argumenty szablonu mają pozwolić
na tę inicjalizację.  Wnioskowanie wprowadza ważne ograniczenie:
**inicjalizacja ma się odbyć bez konwersji typu** (z typu argumentu
wywołania funkcji do typu parametru funkcji).  Tego warunku nie ma
przy wywołaniu zwykłej (nieszablonowej) funkcji, gdzie konwersje są
dozwolone.

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
jest możliwa bez konwersji typu.

Jeżeli jednak dla przykładu wyżej `ParameterType` jest typem
referencyjnym na obiekt niestały typu `T`, to inicjalizacja wygląda
tak:

```cpp
T &t = 1;
```

Wywnioskowanym argumentem będzie ciągle `T = int`, bo r-wartość typu
wbudowanego jest typu niestałego.  Zatem konkretyzacja nie powiedzie
się, bo l-referencja niestała `t` nie może być zainicjalizowana
r-wartością.

# Rodzaje argumentów

Dla każdego **rodzaju** parametru szablonu, kompilator może wnioskować
argument.  Najczęściej chcemy, żeby kompilator wnioskował typowe
argumenty, ale czasem też argumenty wartościowe czy szablonowe.

Wnioskowanie typowych argumentów szablonu jest najbardziej złożone (w
porównaniu do wartościowych i szablonowych argumentów szablonu), bo:

* uwzględnia różne typy parametrów funkcji: zwykłe, referencyjne i
  wskaźnikowe,

* uwzględnia różne typy argumentów wywołania funkcji: wbudowane
  (np. `int`), funkcyjne i tablicowe.

## Typowy argument

Typowy argument szablonu jest wnioskowany dla typowego parametru
szablonu.  Zasady wnioskowania dla szablonowych argumentów szablonu są
takie same, jak dla typowych argumentów.  W zależności od typu
parametru funkcji, kompilator stosuje różne zasady wnioskowania
typowego argumentu szablonu.  Typ parametru funkcji może być:

* referencyjny lub wskaźnikowy,

* zwykły (niereferencyjny i niewskaźnikowy).

### Referencyjny lub wskaźnikowy typ parametru funkcji

*Zasada: wnioskowany argument szablonu jest typem argumentu wywołania
 z pominięciem kwalifikatorów typu (`const` czy `volatile`) jeżeli te
 kwalifikatory zostały podane w definicji typu parametru funkcji.
 Pamiętajmy, że typ argumentu funkcji nigdy nie jest referencyjny.*

Chodzi o to, żeby referencyjny (albo wskaźnikowy) typ parametru
funkcji rzeczywiście mógł być zainicjalizowany: jeżeli typ argumentu
wywołania jest stały (bądź ulotny), to referencja (albo wskaźnik) musi
być stała (bądź ulotna).

Oto przykład dla typów referencyjnych, gdzie funkcja `foo1` została
skonkretyzowana trzy razy, funkcje `foo2` i `foo3` po dwa razy, a
`foo4` raz:

```cpp
{% include_relative arg_type_ref.cc %}
```

Oto przykład dla typów wskaźnikowych:

```cpp
{% include_relative arg_type_ptr.cc %}
```

### Zwykły typ parametru funkcji

*Zasada: wnioskowany argument szablonu jest typem argumentu wywołania
 z pominięciem kwalifikatorów `const` i `volatile`.  Wnioskowanym
 typem nigdy nie będzie typ referencyjny (bo wyrażenie nigdy nie jest
 typu referencyjnego), ale może być wskaźnikowy.  Dla typu
 wskaźnikowego są pomijane kwalifikatory najwyższego rzędu
 (ang. top-level qualifiers).  Typy referencyjne nie mają
 kwalifikatorów najwyższego rzędu.*

Chodzi o to, że inicjalizacja parametrów funkcji (przy przekazywaniu
argumentów wywołania przez wartość) kopiuje wartość argumentu
wywołania do parametru funkcji.  Wtedy nie trzeba już zadbać o
kwalifikatory typu, bo w ciele funkcji działamy na kopii.

Przykład:

```cpp
{% include_relative arg_type_val.cc %}
```

W powyższym przykładzie, na podstawie skonkretyzowanych funkcji wydaje
się, że kwalifikatory typu (`const` i `volatile`) podane w definicji
typu parametru funkcji nie miały znaczenia.  Kwalifikatory typu dla
parametrów zwykłych typów (niereferencyjnych i niewskaźnikowych) mają
jedynie znaczenie na etapie kompilacji (nie konsolidacji): kompilator
nie może pozwolić na modyfikację parametru (`const`) i optymalizację
odwołań (`volatile`) do parametru w ciele funkcji.  Typy tych funkcji
nie mają zachowanych kwalifikatorów typu, bo nie mają one znaczenia
dla kodu wywołującego te funkcje:

```cpp
{% include_relative qualifiers_dropped.cc %}
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

* Wnioskowany może być typ wskaźnikowy, referencyjny, stały, a nawet
  tablicowy.

# Quiz

* Na podstawie czego wnioskowane są argumenty szablonu?

* Czy wnioskowanie uwzględnia typ wartości zwracanej przez funkcję?

* Co to jest rozpad tablicy?
