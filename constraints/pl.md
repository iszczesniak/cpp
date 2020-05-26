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

Ale w przypadku programu korzystającego z bibliotek, do których kodu
nie chcemy nawet zaglądać, to jest problem.  Oczywiście możemy zajrzeć
i może się domyślimy w czym problem (często po długim czasie i ze
sporym wysiłkiem), ale nasza wydajność pracy spada.  **Chcemy lepszej
diagnostyki błędów.**

Lepsza diagnostyka polega na sprawdzeniu warunków stawianych
argumentom szablonu, co możemy zrobić na dwa sposoby:

* stary sposób (C++11): `static_assert`,

* nowy sposób (C++17): ograniczenia.

# `static_assert`

Statyczna asercja `static_assert` sprawdza w czasie kompilacji, czy
argument asercji jest prawdą.

{% highlight c++ %}
{% include_relative intro2.cc %}
{% endhighlight %}

Błąd niespełnionej statycznej asercji jest lepszu od błędu kompilacji,
ale to ciągle błąd kompilacji ciała funkcji, który może pochodzić ze
specjalizacji podstawowego szablonu.  Lepiej jest otrzymać błąd
pochodzący z deklaracji podstawowego szablonu, że argument szablonu
nie spełnia wymagań.

# Ograniczenia

