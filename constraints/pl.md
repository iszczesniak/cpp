---
title: Ograniczenia
---

# Wprowadzenie

Szablony nie wprowadzają ograniczeń na typowe argumenty szablonu:
argumentem może być dowolny typ.  Jeżeli argumentem jest niedozwolony
typ, dopiero na etapie konkretyzacji szablonu otrzymamy błąd, że
**ciało funkcji** nie kompiluje się, ze wskazaniem w której linii jest
błąd.

W przypadku prostego kodu łatwo zorientujemy się o co chodzi, jak na
przykład tu:

{% highlight c++ %}
{% include_relative intro1.cc %}
{% endhighlight %}

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

{% highlight c++ %}
{% include_relative intro2.cc %}
{% endhighlight %}

Do sprawdzenia niektórych warunków możemy użyć standardowej biblioteki
**cech typów** (ang. type traits).  Cecha typu jest szablonem
(struktury lub zmiennej), który dostarcza nam informacji (typów,
stałych wartości) w czasie kompilacji na temat dowolnego () typu,
który jest argumentem szablonu.

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

{% highlight c++ %}
{% include_relative intro3.cc %}
{% endhighlight %}

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

## Wyrażenie ograniczenia



# Przeciążenie szablonów funkcji

Szablony funkcji można przeciążać pod względem ograniczeń, bo przecież
ograniczenia są częścią interfejsu.  Szablony, których ograniczenia
nie są spełnione, są pomijane, bez zgłaszania błędu.

Dla danego wywołania funkcji, tylko dla jednego przeciążenia powinny
zostać poprawnie wywnioskowane argumenty spełniające ograniczenia.
Błąd jest zgłaszany, jeżeli takich przeciążeń nie ma, lub jest ich
więcej niż jedno.

{% highlight c++ %}
{% include_relative overload.cc %}
{% endhighlight %}

Tego nie zrobimy z `static_assert`.

# Cechy typu
