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
sporym wysiłkiem), ale nasza wydajność pracy spada.  **Chcemy lepszej
diagnostyki błędów.**

Lepsza diagnostyka polega na sprawdzeniu warunków stawianych
argumentom szablonu, co możemy zrobić na dwa sposoby:

* stary sposób (C++11): `static_assert`,

* nowy sposób (C++17): ograniczenia.

## Stary sposób: `static_assert`

Statyczna asercja `static_assert` sprawdza w czasie kompilacji, czy
argument asercji jest prawdą.

Przykład:

{% highlight c++ %}
{% include_relative intro2.cc %}
{% endhighlight %}

Do sprawdzenia warunków możemy użyć standardowej biblioteki **cech
typów** (ang. type traits).  Cecha typu jest szablonem (struktury lub
zmiennej), który dostarcza nam informacji (typów, stałych wartości) w
czasie kompilacji na temat typu, który jest argumentem szablonu.

W przykładzie wyżej użyliśmy cechy typu `std::is_integral_v<T>`, który
jest prawdą, jeżeli typ `T` jest całkowity.  Ta cecha typu jest
szablonem stałej zmiennej (chociaż brzmi to dziwnie), która istnieje
tylko w czasie kompilacji (nie w czasie uruchomienia).

Błąd niespełnionej statycznej asercji jest lepszy od błędu kompilacji,
ale to ciągle błąd kompilacji ciała funkcji.  Lepiej jest mieć
możliwość definicji warunków jako część definicji interfejsu, poza
ciałem funkcji.

## Nowy sposób: Ograniczenia

Ograniczenia (ang. constraints) to warunki do spełnienia przez
argumenty szablonu, żeby można było użyć szablonu.  Warunki te
podajemy jako **część definicji interfejsu**, czyli w części
deklaracyjnej szablonu, a nie w ciele szablonu.  Cześć deklaracyjna
szablonu to wszystko oprócz ciała szablonu.  Ograniczenia to
funkcjonalność C++20.

Przykład:

{% highlight c++ %}
{% include_relative declaration.cc %}
{% endhighlight %}

# Ograniczenia

# Derived from:
