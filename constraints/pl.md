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
ale to ciągle błąd kompilacji ciała funkcji, który zawsze kończy się
zakończeniem kompilacji.  Lepiej jest mieć możliwość definicji
warunków jako część definicji interfejsu, poza ciałem funkcji.

## Nowy sposób: Ograniczenia

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
operator inkrementacji?

Najlepiej sprawdzić, czy fragment kodu z inkrementacją kompilowałby
się.  I do tego właśnie służy wyrażenie ograniczenia.

Wyrażenie ograniczenia (ang. a requires-expression) jest predykatem
czasu kompilacji.  Zaczyna się od słowa kluczowego `requires`, po
którym następuje opcjonalna lista parametrów (taka jak w funkcji), po
czym następuje ciało wyrażenia zawierające definicje warunków
oddzielonych średnikami.  Wyrażenie jest prawdziwe, jeżeli spełnione
są wszystkie warunki.

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

Możemy także sprawdzić dostępność typów, na przykład, typu iteratora
jako typ składowy klasy:

```cpp
{% include_relative requires3.cc %}
```

Możemy sprawdzić typ wyrażenia, jak w drugim wyrażeniu ograniczenia w
poniższym przykładzie.  Sprawdzamy typ wyrażenia `c.begin()`, które
umieszczamy w `{}`.  Potem następuje `->`, a potem warunek.  Warunkiem
jest `std::same_as`, który jest dwuargumentowy **konceptem**, gdzie
pierwszym argumentem jest sprawdzay typ.

```cpp
{% include_relative requires4.cc %}
```

# Przeciążenie szablonów funkcji

Szablony funkcji można przeciążać pod względem ograniczeń, bo przecież
ograniczenia są częścią interfejsu.  Szablony, których ograniczenia
nie są spełnione, są pomijane, bez zgłaszania błędu.

Dla danego wywołania funkcji, tylko dla jednego przeciążenia powinny
zostać poprawnie wywnioskowane argumenty spełniające ograniczenia.
Błąd jest zgłaszany, jeżeli takich przeciążeń nie ma, lub jest ich
więcej niż jedno.

```cpp
{% include_relative overload.cc %}
```

Przeciążeń szablonów pod względem spełniania warunków nie
zaimplementujemy ze statyczną asercją, bo ona zawsze kończy kompilację
błędem, kiedy warunki nie są spełnione.

# Podsumowanie

* Organiczenia to mechanizm czasu kompilacji.  Nie wprowadzają żadnego
  narzutu w czasie uruchomienia.

* Ograniczenia pozwalają na definicję warunków szablonu.

* Ograniczenia pozwalają na przeciążanie szablonów.
