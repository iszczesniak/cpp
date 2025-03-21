---
title: Semantyka przeniesienia
---

# Wprowadzenie

Semantyka przeniesienia dotyczy wyłącznie danych typów klasowych (do
tego zaliczają się także struktury i unie), więc będziemy mówić o
przenoszeniu obiektów, a nie danych.  Obiekt jest daną typu klasowego,
czyli danymi interpretowanymi zgodnie z definicją klasy.  Najczęściej
stan obiektu jest jego **wartością**.

Definicja wartości obiektu zależy od implementacji klasy.  Zwykle
wartością obiektu jest stan obiektów bazowych i składowych.  Jednak na
wartość obiektu nie muszą składać się niektóre dane, np. dane
podręczne (ang. cache data), które składają się na jego stan.

Wartość obiektu może być kopiowana podczas:

* inicjalizacji: `T t(<expr>);`

* przypisania: `t = <expr>;`

W inicjalizacji i przypisaniu rozróżniamy obiekt źródłowy (wyrażeń
`<expr>` wyżej) i docelowy (zmiennych `t` wyżej).  Obiekt docelowy
jest inicjalizowany obiektem źródłowym.  Obiekt docelowy jest po lewej
stronie operatora przypisania, a źródłowy po prawej.

Fakty o kopiowaniu obiektów:

* Kopiowanie nie zawsze jest konieczne.

* Kopiowanie jest czasochłonne, kiedy obiekty są duże.

* Kopiowanie obiektów jest implementowane przez:

  * *konstruktor kopiujący* podczas inicjalizacji,
  
  * *kopiujący operator przypisania* podczas przypisania.

Obiekty źródłowe i docelowe mogą być gdziekolwiek, czyli w dowolnym
obszarze pamięci, nie tylko na stosie czy stercie.  Na przykład,
obiekt źródłowy może być na stosie, a obiekt docelowy w obszarze
pamięci dla danych statycznych i globalnych.  Obiekt nie powinien
wiedzieć, w jakim obszarze pamięci się znajduje.

Kopiowanie może być problemem w zależności od tego czy jest potrzebne
czy nie.  Nie jest problemem, jeżeli jest potrzebne, np. kiedy musimy
wykonać kopię obiektu do zmian, bo oryginału nie możemy zmieniać.

Kopiowanie jest problemem, kiedy jest zbędne, czyli wtedy, kiedy
obiekt źródłowy po kopiowaniu nie jest potrzebny.  Zbędne kopiowanie
pogarsza wydajność: kod będzie działał poprawnie, ale mógłby być
szybszy.

# Semantyka przeniesienia

Semantyka przeniesienia pozwala na przeniesienie wartości z obiektu
źródłowego do docelowego kiedy kopiowanie nie jest potrzebne.  Została
ona wprowadzona w C++11, ale jej potrzeba była zauważona w latach
dziewięćdziesiątych.  Przenoszenie jest jak ratowanie ładunku
(wartości) z tonącego statku (obiektu, który wkrótce nie będzie
potrzebny).

Semantyka przeniesienia jest stosowana:

* podczas inicjalizacji i przypisania,

* kiedy wyrażenie obiektu źródłowego jest r-wartością,

* kiedy typ obiektu docelowego ma zaimplementowaną semantykę
  przeniesienia.

Semantyka przeniesienia jest implementowana przez:

* **konstruktor przenoszący** (dla inicjalizacji),

* **przenoszący operator przypisania** (dla przypisania).

## Jak to działa

* To nie magia.  Obiekt nie jest przenoszony bit po bicie do innego
  miejsca.  Użytkownik zna każdy szczegół i ma pełną kontrolę.

* Tylko wartość jest przenoszona.  Obiekt źródłowy i obiekt docelowy
  pozostają tam, gdzie były, bo będą one niszczone tak, jak zwykle.

* Po przeniesieniu obiekt źródłowy musi być spójny, ale stan nie musi
  być określony (np. jakiś pusty).  Obiekt musi być spójny, bo będzie
  niszczony.

## Konstruktor: kopiujący i przenoszący

Klasa może mieć kopiujący lub przenoszący konstruktor.  Może mieć oba
albo żadnego.  Konstruktor kopiujący i przenoszący są przeciążeniami
konstruktora.

Konstruktor przenoszący klasy `T` ma jeden parametr typu `T &&`.

### Prosty przykład

W przykładzie niżej klasa ma zdefiniowane trzy konstruktory:

```cpp
{% include_relative constructors.cc %}
```

### Implementacja przeciążeń konstruktora

Konstruktor przenoszący powinien inicjalizować obiekty bazowe i
składowe z użyciem konstruktorów przenoszących.  Dlatego w liście
inicjalizacyjnej obiektów bazowych i składowych konstruktora
przenoszącego powinny być przekazywane r-wartości jako wyrażenia
inicjalizacyjne, żeby wpłynąć na wybór przeciążeń konstruktorów
obiektów bazowych i składowych.  Do tego celu używamy funkcji
`std::move`, jak pokazano w przykładzie niżej, w którym dla porównania
zaimplementowano także konstruktor kopiujący.

```cpp
{% include_relative ctor_impl.cc %}
```
  
## Operator przypisania: kopiujący i przenoszący

Klasa może mieć kopiujący lub przenoszący operator przypisania.  Może
mieć oba albo żadnego.  Operator kopiujący i przenoszący są
przeciążeniami operatora przypisania.

Przenoszący operator przypisania klasy `T` ma jeden parametr typu `T
&&`.

### Prosty przykład:

W przykładzie niżej klasa ma zdefiniowane dwa przeciążenia operatora
przypisania:

```cpp
{% include_relative operators.cc %}
```

### Typ wyniku przenoszącego operatora przypisania

Jeżeli `x` i `y` są typu `A`, to wyrażenie `x = y = A()` powinno
przenieść wartość z obiektu tymczasowego `A()` do `y`, a następnie
powinno skopiować wartość z `y` do `x`.  To wyrażenie jest
opracowywane od prawej do lewej strony, ponieważ operator przypisania
ma prawe wiązanie.

Dlatego przenoszący operator przypisania powinien zwracać
l-referencję, a nie r-referencję.  Jeżeli operator zwracałby
r-referencję, to wtedy to wyrażenie przenosiłoby wartość z obiektu
tymczasowego `A()` do `y` (tak jak oczekujemy), ale potem
*przenosiłoby* wartość z `y` do `x`, a przecież oczekiwalibyśmy
kopiowania.  Implementacja poniżej.

```cpp
{% include_relative assign_cat1.cc %}
```

Jednak z powyższą implementacją, wyrażenie `x = A() = A()` jest
niepoprawnie opracowywane.  Wyrażenie `A() = A()` co prawda przeniesie
wartość z prawego obiektu do lewego, ale to wyrażenie jest l-wartością
(ponieważ przenoszący operator przypisania zwraca l-referencję), która
będzie wyrażeniem źródłowym operatora przypisania do zmiennej `x`, ale
operatora przypisania kopiującego, a nie oczekiwanego przenoszącego.

Co ciekawe, ponieważ przenoszący operator przypisania zwraca
l-referencję, to jego wynikiem możemy zainicjalizować niestałą
l-referencję: `A &l = A() = A();`.  Taka inicjalizacja kompiluje się,
choć nie powinna, skoro `A &l = A();` się nie kompiluje.  To jest
uchybienie.

Żeby zaradzić powyższemu niepoprawnemu opracowaniu i temu uchybieniu,
należy przeciążyć przenoszący operator przypisania osobno dla
l-wartości i r-wartości.  Poprawna implementacja poniżej.

```cpp
{% include_relative assign_cat2.cc %}
```

### Implementacja przeciążeń operatora przypisania

Przenoszący operator przypisania powinien przypisywać obiektom bazowym
i składowym z użyciem przenoszących operatorów przypisania.  Dlatego
wyrażeniami źródłowymi operatorów przypisania dla obiektów bazowych i
składowym powinny być r-wartości, żeby wpłynąć na wybór przeciążeń
operatorów przypisania.  Do tego celu używamy funkcji `std::move`, jak
pokazano w przykładzie niżej, w którym dla porównania zaimplementowano
także kopiujący operator przypisania.

```cpp
{% include_relative assign_impl.cc %}
```

## Wybór przeciążenia

Wybór przeciążenia (kopiującego albo przenoszącego) konstruktora czy
operatora przypisania zależy od kategorii wartości wyrażenia
źródłowego i dostępności przeciążeń.  Stosowane są tu zasady wyboru
przeciążenia funkcji w zależności od referencyjnego typu parametru
przeciążenia.

## Składowe specjalne

Składowymi specjalnymi są:

* konstruktor domyślny (z pustą listą parametrów),

* konstruktor kopiujący i kopiujący operator przypisania,

* konstruktor przenoszący i przenoszący operator przypisania,

* destruktor.

Składowa specjalna może być niezadeklarowana (ang. undeclared) albo
zadeklarowana (ang. declared).  Funkcja może być zadeklarowana:

* **jawnie przez programistę** (ang. explicitly) jako:

  * *dostarczona przez użytkownika* (ang. user-defined): programista
     dostarcza implementację,

  * *domyślnie zaimplementowana* (ang. defaulted): programista żądą
     domyślnej implementacji,

  * *usunięta* (ang. deleted): programista deklaruje składową jako
     usuniętą.

* **niejawnie przez kompilator** (ang. implicitly) jako:

  * *domyślnie zaimplementowana* (ang. defaulted): kompilator dołącza
     domyślą implementację bez żądania programisty,

  * *usunięta* (ang. deleted): kompilator deklaruje składową jako
     usuniątą bez żądania programisty.

Jeżeli składowa jest zadeklarowana jako usunięta (nieważne, czy jawnie
czy niejawnie), to jest brana pod uwagę w wyborze przeciążenia, ale
kiedy jest wybrana, to kompilacja kończy się błędem.

### Jawnie domyślna składowa

Programista może jawnie zażądać domyślnej implementacji składowej
specjalnej z użyciem `= default`:

```cpp
{% include_relative default.cc %}
```

### Domyślna implementacja

Wszystkie obiekty bazowe i składowe w domyślnej implementacji:

* konstruktora domyślnego są inicjalizowane domyślnie,

* konstruktora kopiującego są inicjalizowane przez kopiowanie,

* kopiującego operatora przypisania są przypisywane przez kopiowanie,

* konstruktora przenoszącego są inicjalizowane przez przenoszenie,

* przenoszącego operatora przypisania są przypisywane przez
  przenoszenie,

* destruktora są niszczone.

### Jawnie usunięta składowa

Programista może jawnie usunąć składową z użyciem `= delete`:

```cpp
{% include_relative delete.cc %}
```

### Zasady dla składowych specjalnych

Wszystkie składowe specjalne są niejawnie domyślnie zaimplementowane
(jeżeli są potrzebne), chyba że będzie zastosowana:

* *stara zasada*: konstruktor domyślny (ten z pustą listą parametrów)
  będzie **niezadeklarowany**, jeżeli którykolwiek inny konstruktor
  będzie jawnie **zadeklarowany**,

* *zasada kompatybilności wstecz*: składowe przenoszące będą
  **niezadeklarowane** (więc nie będą brały udziału w wyborze
  przeciążenia), jeżeli składowa kopiująca lub destruktor jest
  **jawnie zadeklarowany**: stary kod będzie nadal działał po staremu,
  bo nie będzie miał niejawnie dostarczonej domyślnej implementacji
  semantyki przeniesienia (czyli składowych przenoszących),

* *zasada nowego kodu*: składowe kopiujące będą **niejawnie usunięte**
  (więc będą brały udział w wyborze przeciążenia), jeżeli składowa
  przenosząca jest **jawnie zadeklarowana**: programista będzie musiał
  zadeklarować składowe kopiujące, jeżeli są potrzebne.

Te zasady mają na celu bezproblemową integrację semantyki
przeniesienia zarówno w starym, jak i nowym kodzie.  Typ, który nie
zarządza swoimi zasobami w jakiś nietypowy sposób (chodzi o składowe
specjalne), będzie miał zaimplementowane domyślnie semantyki
kopiowania i przeniesienia.

## Typ tylko do przenoszenia

Obiekty typu tylko do przenoszenia mogą być tylko przenoszone i nie
mogą być kopiowane.  Oto przykład typu tylko do przenoszenia:

```cpp
{% include_relative move_only.cc %}
```

# Konsekwencje semantyki przeniesienia

## Inicjalizacja parametrów funkcji

Parametr funkcji jest inicjalizowany z użyciem argumentu wywołania.
Dla parametru klasowego typu niereferencyjnego, wybór przeciążenia
konstruktora będzie zależał od kategorii argumentu i dostępności
przeciążeń.

Jeżeli będzie przekazywany obiekt tymczasowy do funkcji, to
konstruktor przenoszący nie będzie wywołany, a pominięty.

## Niejawne przeniesienie zwracanej wartości

Jeżeli unikanie konstruktorów (albo optymalizacja wartości powrotu)
nie może być zastosowana, a zwracany obiekt będzie niszczony po
powrocie z funkcji, to wartość zwracanego obiektu może być niejawnie
przeniesiona: instrukcja `return t;` będzie niejawnie zamieniana na
`return std::move(t);`.  Tylko wyrażenia będące nazwą zmiennej są tak
konwertowane (z l-wartości na r-wartość), inne wyrażenia nie.

Nie powinniśmy zawsze jawnie konwertować kategorii wartości wyrażenia
(np. z użyciem funkcji `std::move`) instrukcji powrotu, bo wtedy
uniemożliwimy unikanie konstruktorów (albo optymalizację wartości
powrotu).

Poniżej omówione są dwa przypadki, w których optymalizacja wartości
powrotu jest niemożliwa, ale w których zwracana wartość jest niejawnie
przenoszona.

#### Przypadek 1

Kiedy zwracamy parametr funkcji, nie można zastosować optymalizacji
wartości powrotu (bo parametr nie może być stworzony w miejscu dla
zwracanej wartości), ale będzie zastosowane niejawne przeniesienie
wartości, bo:

* parametr będzie niszczony po wyjściu z funkcji,

* wyrażenie instrukcji powrotu to tylko nazwa parametru.

Oto przykład:

```cpp
{% include_relative implicit1.cc %}
```

#### Przypadek 2

Kiedy zwracamy obiekt bazowy lokalnego obiektu, nie można zostosować
optymalizacji wartości powrotu, bo miejsce dla wracanej wartości jest
przewidziane dla typu bazowego.  Wartość obiektu bazowego może być
jednak przeniesiona, bo:

* obiekt lokalny będzie zniszczony po wyjściu z funkcji,

* wyrażenie instrukcji powrotu to tylko nazwa parametru, która nie
  tylko będzie niejawnie konwertowana do r-wartości, ale też niejawnie
  rzutowana do typu bazowego.

Będzie przenoszona tylko wartość obiektu bazowego, a nie całego
obiektu, co nazywamy cięciem obiektu (ang. object slicing), bo
wycinamy wartość obiektu bazowego, żeby ją przenieść.

```cpp
{% include_relative implicit2.cc %}
```

Jeżeli obiekt lokalny byłby statyczny (czyli nie byłby niszczony po
wyjściu z funkcji), to wartość nie mogłaby zostać niejawnie
przeniesiona, a jedynie skopiowana.

## Funkcja `std::swap`

Zakończmy tym, od czego semantyka przeniesienia się zaczęła, funkcją
`std::swap`.  W latach dziewięćdziesiątych zauważono, że ta funkcja
będzie działała szybciej bez kopiowania.  Ale jak, skoro wówczas było
tylko kopiowanie?  Takie jest źródło semantyki przeniesienia.

Funkcja `std::swap` przyjmuje przez referencję dwa argumenty i
zamienia ich wartości.  Ta funkcja jest częścią biblioteki
standardowej, ale przykładowa implementacja niżej ilustruje problem
wydajnej zamiany wartości:

```cpp
{% include_relative swap.cc %}
```

# Podsumowanie

Semantyka przeniesienia:

* została wprowadzona w C++11,

* jest używana, kiedy kopiowanie jest zbędne,

* poprawia wydajność czasową programu,

* dotyczy tylko r-wartości,

* jest używana, nawet jeżeli programista tego nie żąda.

# Quiz

* Dlaczego semantyka przeniesienia jest ważna?

* Jak działa semantyka przeniesienia?

* Czym jest typ tylko do przenoszenia?

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
