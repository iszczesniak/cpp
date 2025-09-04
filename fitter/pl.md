---
title: Wyspecjalizowanie szablonów
---

# Wprowadzenie

Specjalizacja (a może lepiej "wyspecjalizowanie") ma dodatkowe
znaczenie w języku C++, który pozwala przeciążać szablony podstawowe
funkcji o tej samej nazwie.  Jeżeli będzie można użyć więcej niż
jednego szablonu, to kompilator wybiera najbardziej
**wyspecjalizowany** szablon.  Nie musimy specjalizować szablonu, żeby
mówić o **najbardziej wyspecjalizowanym szablonie podstawowym**.  W
przykładzie niżej definiujemy dwa szablony podstawowe funkcji `foo`, a
następnie wywołujemy funkcję `foo`.

```cpp
{% include_relative special1.cc %}
```

Jak kompilator wybrał właściwy szablon dla dwóch wywołań funkcji w
przykładzie wyżej?  Pierwsze wywołanie przekazuje argument typu
całkowitego, więc wybór jest tylko jeden: szablon `A`.  Szablon `B`
nie może być użyty, bo kompilator nie jest w stanie wywnioskować
argumentu `B1` szablonu tak, żeby można byłoby zainicjalizować
parametr `b1` funkcji.

Drugie wywołanie jest ciekawsze.  Kompilator może użyć zarówno
szablonu `A`, jak i `B`.  W tej sytuacji jest użyty **bardziej
wyspecjalizowany szablon**.  W tym przykładzie szablon `B` jest
bardziej wyspecjalizowany.

Zanim przejdziemy dalej (do omówienia idei bardziej wyspecjalizowanego
szablonu), to podsumujmy przykład i zauważmy ważny fakt.  Podczas
opracowania drugiego wywołania, kompilator może skonkretyzować oba
szablony używając wywnioskowanych argumentów:

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
ignorowane zgodnie z zasadą SFINAE).  Zwróćmy uwagę na ważny fakt: **w
drugim kroku, wyrażenie wywołania nie jest już brane pod uwagę.**
Wyrażenie wywołania jest brane pod uwagę tylko w pierwszym kroku, żeby
wybrać kandydatów.

## Wybór najbardziej wyspecjalizowanego szablonu

Ze zbioru kandydatów wybieramy najbardziej wyspecjalizowany szablon
przez porównywanie szablonów parami, czyli z użyciem binarnej relacji,
którą umownie oznaczymy jako `⊂`.  Porównując parę szablonów `I` i `J`
chcemy określić, który szablon jest bardziej wyspecjalizowany.

Jednak relacja `⊂` nie musi zachodzić między każdą parą szablonów i
dlatego nazywana jest **częściową**.  Ponieważ relacja jest częściowa,
to może okazać się, że kompilator nie jest w stanie wybrać najbardziej
wyspecjalizowanego szablonu i wtedy zgłasza błąd niejednoznaczności.

Relacja `⊂` jest silnym porządkiem częściowym, ponieważ jest:

* częściowa,

* przeciwzwrotna, bo szablon nie może być bardziej wyspecjalizowany od
  siebie samego, czyli relacja `I ⊂ I` nigdy nie zachodzi,

* asymetryczna, bo jeżeli `I ⊂ J`, to relacja odwrotna (czyli `J ⊂ I`,
  albo inaczej `I ⊃ J`) nie zachodzi,

* przechodnia, bo jeżeli `I ⊂ J` i `J ⊂ K`, to naturalnie oczekujemy,
  że `I` będzie uznany za bardziej wyspecjalizowany niż `K`, czyli `I
  ⊂ K`.

Dla przykładu wyżej możemy powiedzieć, że dla drugiego wywołania
szablon `B` jest bardziej wyspecjalizowany niż `A` (relacja zachodzi:
`B ⊂ A`).  Ponieważ zbiór kandydatów ma tylko dwa szablony, więc
szablon `B` uznajemy za najbardziej wyspecializowany.

### Relacja "bardziej wyspecjalizowany"

Relacja `I ⊂ J` porównuje argumenty wywołania funkcji, które mogą być
użyte z szablonami `I` i `J`.  **Szablon bardziej wyspecjalizowany to
ten, którego dopuszczalne argumenty funkcji są *podzbiorem właściwym*
dopuszczalnych argumentów funkcji drugiego szablonu.** Relacja
właściwego zawierania oznacza, że każdy argument funkcji dopuszczalny
dla jednego szablonu jest dopuszczalny dla drugiego szablonu, ale nie
na odwrót, co zapisujemy w poniższej definicji:

**Definicja 1**: `I ⊂ J` wtedy i tylko wtedy, gdy:

1. każdy argument funkcji dopuszczalny dla szablonu `I` jest też
   dopuszczalny dla szablonu `J`,

2. nie każdy argument funkcji dopuszczalny dla szablonu `J` jest
   dopuszczalny dla szablonu `I`.

Relację `I ⊂ J` czytamy:

* `I` jest bardziej wyspecjalizowany niż `J`,

* `I` jest mniej ogólny niż `J`.

Natomiast relację odwrotną `J ⊃ I` czytamy:

* `J` jest mniej wyspecjalizowany niż `I`,

* `J` jest bardziej ogólny niż `I`.

Ale co dokładnie oznacza "dopuszczany argument funkcji"?  Dopuszczalny
argument funkcji to ten, który może być użyty do wywołania funkcji,
czyli (w przypadku użycia szablonu funkcji) ten, na podstawie którego
można wywnioskować argumenty szablonu.  Nie chodzi tylko o typ
argumentu, ale i jego kategorię (co jest ważne w przypadku
inicjalizacji referencyjnego parametru funkcji).  W drugim kroku
wiemy, że argument funkcji opracowywanego wyrażenia jest dopuszczalny
dla każdego szablonu ze zbioru kandydatów: ten argument nie pozwoli
nam wybrać bardziej wyspecjalizowanego szablonu i dlatego nie jest
dalej brany pod uwagę (w pierwszym kroku był, ale w drugim już nie).
Potrzebujemy innego sposobu porównania.

W przykładzie wyżej, funkcja szablonu `A` przyjmuje argumenty
(funkcji) dowolnych typów, także wskaźnikowych.  Funkcja szablonu `B`
przyjmuje argumenty tylko typów wskaźnikowych.  Szablon `B` jest
bardziej wyspecjalizowany niż szablon `A` (czyli `B ⊂ A`), ponieważ
zbiór dopuszczalnych argumentów funkcji szablonu `B` jest podzbiorem
właściwym zbioru dopuszczalnych argumentów funkcji szablonu `A`.  Tak
to wynika z wnioskowania:

* szablonu `A` możemy użyć dla każdego argumentu typu `B1 *` (czyli
  typu parametru funkcji szablonu `B`), bo możemy zainicjalizować
  parametr `a1` funkcji wyrażeniem typu `B1 *`: `A1` będzie
  wywnioskowany jako `B1 *`,

* szablonu `B` nie możemy użyć dla każdego argumentu typu `A1` (czyli
  typu parametru funkcji szablonu `A`), a jedynie dla typów
  wskaźnikowych; parametr `b1` możemy zainicjalizować tylko wtedy,
  kiedy `A1` jest typem wskaźnikowym (np. `T *`), bo tylko wtedy
  wnioskowanie się uda (np. `B1 = T`).

Porównanie szablonów `I` i `J` wykorzystuje wnioskowanie.  Zacznijmy
od **najprostszego ogólnego przypadku** z jednym parametrem szablonu i
jednym parametrem funkcji:

* szablon `I` ma jeden parametr `I1` a jego funkcja `foo` ma jeden
  parametr `i1` typu `ParamI1`; typ `ParamI1` używa `I1`,

* szablon `J` ma jeden parametr `J1` a jego funkcja `foo` ma jeden
  parametr `j1` typu `ParamJ1`; typ `ParamJ1` używa `J1`.

```cpp
{% include_relative simplest.hpp %}
```

Zwróćmy uwagę na nazwy szablonów i parametrów.  Nazwy `I` i `J`
używamy w definicjach relacji `⊂`, natomiast w przykładach używamy
nazw `A`, `B`, `C`.  W przykładzie wyżej, najprostrzy ogólny przypadek
ma tak zamienione:

* nazwy szablonów: `I` &rarr; `A`, `J` &rarr; `B`,

* nazwy parametrów szablonów: `I1` &rarr; `A1`, `J1` &rarr; `B1`,

* nazwy parametrów funkcji: `i1` &rarr; `a1`, `j1` &rarr; `b1`,

* definicje typów parametrów funkcji: `ParamI1` &rarr; `A1`, `ParamJ1`
  &rarr; `B1 *`.

Definicję 1 (relacji `I ⊂ J`) możemy wyrazić wnioskowaniem argumentów
szablonu, co zapiszemy jako poniższą definicję.

**Definicja 2**: `I ⊂ J` wtedy i tylko wtedy, gdy:

1. możemy wywnioskować argument szablonu `J` na podstawie szablonu
   `I`, czyli możemy wywnioskować argument dla parametru `J1` na
   podstawie inicjalizacji parametru `j1`: `ParamTypeJ1 j1 = ExprI1`,
   gdzie `ExprI1` jest typu `ParamTypeI1`,

2. nie możemy wywnioskować argumentu szablonu `I` na podstawie
   szablonu `J`, czyli nie możemy wywnioskować argumentu dla parametru
   `I1` na podstawie inicjalizacji parametru `i1`: `ParamTypeI1 i1 =
   ExprJ1`, gdzie `ExprJ1` jest typu `ParamTypeJ1`.

Spróbujmy użyć Definicji 2 do zrozumienia poniższego przykładu.  Ten
przykład jest przerobionym poprzednim przykładem, gdzie usunęliśmy
pierwsze i drugie wywołanie, a następnie dodaliśmy szablon `C` i jego
użycie.

```cpp
{% include_relative special2.cc %}
```

Wywołujemy funkcję `foo` i przekazujemy jej argument: nazwę funkcji
`goo`.  Kompilator próbuje użyć szablonów (`A`, `B`, `C`) i dla
każdego z nich nazwa `goo` rozpada się na wskaźnik do funkcji `goo`,
ponieważ żaden z szablonów nie przyjmuje argumentu przez referencję.
Zatem typem przekazywanego argumentu jest `void (*)()`.  Dla każdego
szablonu wnioskowanie się powodzi.

Wiemy z poprzedniego przykładu, że `B ⊂ A`, więc pozostaje sprawdzić,
w jakiej relacji jest `C` z `B` i `A`.  Sprawdźmy, który szablon jest
bardziej wyspecjalizowany: `C` czy `B`.  Powiemy, że `C` jest bardziej
wyspecjalizowany od `B` (`C ⊂ B`), jeżeli:

1. możemy wywnioskować argument szablonu `B` na podstawie szablonu
   `C`, czyli możemy wywnioskować argument dla parametru `B1` na
   podstawie inicjalizacji parametru `b1`: `B1 *b1 = ExprC1`, gdzie
   `ExprC1` jest typu `C1 (*)()`,

2. nie możemy wywnioskować argumentu szablonu `C` na podstawie
   szablonu `B`, czyli nie możemy wywnioskować argumentu dla parametru
   `C1` na podstawie inicjalizacji parametru `c1`: `C1 (*c1)() =
   ExprB1`, gdzie `ExprB1` jest typu `B1 *`.

Zatem `C ⊂ B`, ponieważ:

Ad 1. `ExprC1` jest typem wskaźnika na funkję typu `C1()`, więc `B1`
   jest wywnioskowany jako `C1()`: udało się,

Ad 2. `ExprB1` jest typem wskaźnika na cokolwiek, więc nie możemy
   wywnioskować `C1` dla dowolnego B1 (powiodłoby się wyłącznie dla
   pewnych typów funkcji).

Jako ćwiczenie proszę sprawdzić, czy zachodzi relacja `B ⊂ C`.

Relacja `⊂` jest przechodnia (ponieważ jest porządkiem), więc z `C ⊂
B` i `B ⊂ A` wynika `C ⊂ A`.  Zatem `C` jest najbardziej
wyspecjalizowany i on jest użyty.

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
