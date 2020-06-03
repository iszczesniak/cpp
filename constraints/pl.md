---
title: Ograniczenia
---

# Wprowadzenie

Szablony nie wprowadzają ograniczeń na argumenty szablonu.  Jeżeli
argument jest niedozwolony, to dopiero na etapie konkretyzacji
szablonu otrzymamy błąd, że **ciało funkcji** nie kompiluje się, ze
wskazaniem w której linii jest błąd.

W przypadku prostego kodu łatwo zorientujemy się o co chodzi, jak na
przykład tu:

```cpp
{% include_relative intro1.cc %}
```

Ale to jest problem w przypadku programu korzystającego z bibliotek,
do których kodu nie chcemy nawet zaglądać.  Oczywiście możemy zajrzeć
i może się domyślimy w czym problem (często po długim czasie i ze
sporym wysiłkiem), ale kto chce to robić.  **Chcemy lepszej
diagnostyki błędów.**

Lepsza diagnostyka polega na sprawdzeniu warunków stawianych
argumentom szablonu, co możemy zrobić na dwa sposoby:

* stary sposób (C++11): `static_assert`,

* nowy sposób (C++20): ograniczenia.

## Stary sposób: `static_assert`

Statyczna asercja `static_assert` sprawdza w czasie kompilacji, czy
argument asercji jest prawdą.

Przykład:

```cpp
{% include_relative intro2.cc %}
```

Do sprawdzenia niektórych warunków możemy użyć standardowej biblioteki
**cech typów** (ang. type traits).  Cecha typu jest szablonem
(struktury lub zmiennej), który dostarcza nam informacji (typów,
stałych wartości) w czasie kompilacji na temat dowolnego typu, który
jest argumentem szablonu.

W przykładzie wyżej użyliśmy cechy typu `std::is_integral_v<T>`, który
jest prawdą, jeżeli typ `T` jest całkowity.  Ta cecha typu jest
szablonem *stałej zmiennej* (chociaż brzmi to dziwnie), która istnieje
tylko w czasie kompilacji (nie w czasie uruchomienia).

Błąd niespełnionej statycznej asercji jest jakąś lepszą diagnostyką,
ale to ciągle błąd kompilacji ciała funkcji, który kończy kompilację.
Lepiej jest mieć możliwość definicji warunków jako część definicji
interfejsu, poza ciałem funkcji.

## Nowy sposób: ograniczenia

Ograniczenie (ang. constraint) podajemy jako **część definicji
interfejsu**, czyli w części deklaracyjnej szablonu, a nie w ciele
szablonu.  Cześć deklaracyjna szablonu to wszystko oprócz ciała
szablonu.  Ograniczenia to funkcjonalność C++20.

Przykład:

```cpp
{% include_relative intro3.cc %}
```

# Ograniczenie

**Ograniczenie to predykat czasu kompilacji, który definiuje warunki
dotyczące argumentów szablonu.** Predykat czasu kompilacji to
wyrażenie typu logicznego, którego wartość jest znana w czasie
kompilacji.  Ograniczenie jest warunkiem, który musi być spełniony
(czyli wartością ma być prawda) przez argumenty szablonu, żeby można
było użyć szablonu.

Ograniczenie podajemy po słowie kluczowym `requires` po liście
parametrów szablonu funkcji czy struktury danych.  Słowo kluczowe
`requires` wraz z następującym ograniczeniem nazywamy **klauzulą
ograniczenia** (ang. a requires-clause).

Predykat może być alternatywą czy koniunkcją, których operandami mogą
być kolejne predykaty.  Jeżeli predykat jest wyrażeniem, które wymaga
opracowania (na przykład wykonania porównania), to należy wyrażenie
ująć w nawiasy.

Na przykład:

```cpp
{% include_relative complex.cc %}
```

## Wyrażenie ograniczenia

Są warunki do sprawdzenia, których nie sprawdzimy używając cech typów,
a przynajmniej nie tych standardowych.  Na przykład, jak sprawdzić,
czy typ danych, który jest argumentem szablonu, ma zdefiniowany
operator inkrementacji?  Najlepiej sprawdzić, czy fragment kodu z
inkrementacją kompilowałby się.  I do tego właśnie służy wyrażenie
ograniczenia.

Wyrażenie ograniczenia (ang. a requires-expression) jest predykatem
czasu kompilacji.  Zaczyna się od słowa kluczowego `requires`, po
którym następuje opcjonalna lista parametrów (taka jak w funkcji), po
czym następuje ciało zawierające definicje warunków zakończone
średnikami.  Wyrażenie jest prawdziwe, jeżeli spełnione są wszystkie
warunki.  Taka jest więc składnia:

```cpp
requires (parameter-list) {expression body}
```

Przykład:

```cpp
{% include_relative requires1.cc %}
```

W przykładzie wyżej `requires requires` to nie błąd.  Pierwsze
`requires` wprowadza klauzulę ograniczenia, a drugie `requires`
wprowadza wyrażenie ograniczenia.  Wyrażenie ograniczenia jest
predykatem klauzuli ograniczenia.  Słowo kluczowe `requires` ma po
prostu dwa różne, chociaż pokrewne, zastosowania.

Lista parametrów w wyrażeniu ograniczenia jest opcjonalna i możemy ją
pominąć, na przykład wtedy, kiedy w ciele wyrażenia ograniczenia
użyjemy parametrów funkcji.  Żeby jednak użyć parametrów funkcji, to
klauzulę ograniczenia musimy podać po liście parametrów funkcji, jak w
tym przykładzie:

```cpp
{% include_relative requires2.cc %}
```

Możemy także sprawdzić dostępność typu składowego klasy, na przykład
typu iteratora:

```cpp
{% include_relative requires3.cc %}
```

Możemy sprawdzić typ wyrażenia jak w drugim wyrażeniu ograniczenia w
poniższym przykładzie.  Sprawdzamy typ wyrażenia `c.begin()`, które
umieszczamy w `{}`.  Potem następuje `->`, a potem warunek.  Warunkiem
jest szablonowy predykat, za którego pierwszy argument jest
podstawiany typ testowanego wyrażenia.  Czyli w przykładzie niżej
sprawdzamy `same_as<typ testowanego wyrażenia, typename C::iterator>`,
gdzie `std::same_as`, który jest dwuargumentowy **konceptem** (koncept
to szablon predykatu).

Próbowałem użyć cechy typu `is_same_v` jako warunku, zamiast konceptu
`same_as`, ale nie kompiluje się.  Nie wiem dlaczego.

```cpp
{% include_relative requires4.cc %}
```

### Przykład ograniczenia: wymagana klasa bazowa

Jeżeli funkcja ma przyjąć jako argument wywołania obiekt typu, który
dziedziczy po klasie bazowej `A`, to możemy ten obiekt przyjąć przez
referencję na obiekt klasy `A`, tak jak robi to funkcja `foo1` w
przykładzie niżej.  **W ten sposób funkcja działa zawsze na obiekcie
typu `A`, czyli tracimy typ argumentu.**

Możemy też napisać szablon funkcji (`foo2` w przykładzie niżej), która
przyjmie obiekt dowolnego typu i będzie używała składowych klasy `A`,
bez deklarowania tego wymogu, co może się skończyć błędem kompilacji.

Kolejną możliwością jest napisanie szablonu funkcji (`foo3` w
przykładzie niżej) i zdefiniowanie ograniczenia: przyjmujemy dowolny
typ `T` wyprowadzony z `A`.  **W ten sposób funkcja działa na obiekcie
typu `T`, czyli nie tracimy typu argumentu.**

```cpp
{% include_relative static.cc %}
```

# Przeciążenie szablonów funkcji

Szablony funkcji można przeciążać pod względem ograniczeń, ponieważ są
one częścią interfejsu.  Szablony bez spełnionych warunków są
pomijane, bez zgłaszania błędu.

Dla danego wywołania funkcji, co najmniej dla jednego przeciążenia
powinny zostać poprawnie wywnioskowane argumenty spełniające
ograniczenia.  Jeżeli takich przeciążeń nie ma, zgłaszany jest błąd.

Jeżeli takich przeciążeń jest więcej, to wybierane jest to bardziej
wyspecjalizowane, którego warunki nie są spełniane przez pozostałe
przeciążenia.  Jeżeli kompilator nie jest w stanie wybrać jednego
przeciążenia, zgłaszany jest błąd niejednoznaczności (ang. ambiguity
error).

```cpp
{% include_relative overload1.cc %}
```

Tutaj jest kolejny przykład, który nie kompiluje się w całości,
chociaż nie rozumiem dlaczego.  Problem jest z wyborem przeciążenia
dla zakomentowanego wywołania funkcji.  Albo to bug w kompilatorze,
albo moja niewiedza.

```cpp
{% include_relative overload2.cc %}
```

Przeciążeń szablonów pod względem spełniania warunków nie
zaimplementujemy ze statyczną asercją, bo ona zawsze kończy kompilację
błędem dla niespełnionego warunku.

# Podsumowanie

* Ograniczenia to mechanizm czasu kompilacji.  Nie wprowadzają żadnego
  narzutu w czasie uruchomienia.

* Ograniczenia pozwalają na definicję warunków szablonu.

* Ograniczenia pozwalają na przeciążanie szablonów.
