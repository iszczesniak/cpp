---
title: std::shared_ptr
---

# Wprowadzenie

Kiedy dynamicznie tworzymy dane (albo jakikolwiek inne zasoby) i
używamy ich w innych wątkach albo częściach kodu, to pojawia się
problem kiedy zniszczyć dane.  Jeżeli:

* nie zniszczymy danych, to mamy wyciek pamięci,

* zniszczymy dane zbyt wcześnie, to mamy zjawisko hazardu: nieaktualny
  wskaźnik i niezdefiniowane zachowanie, bo inne wątki czy części
  programu ciągle używają danych,

* zniszczymy dane zbyt późno, to mamy spadek wydajności, ponieważ
  pozwalamy niepotrzebnym danym tkwić w pamięci.

Dlatego powinniśmy niszczyć dane we właściwym momencie, czyli wtedy,
kiedy nie są już potrzebne.  Niestety, ten właściwy moment jest trudny
do określenia, ponieważ może on zależeć od:

* danych (ich wartości),

* przebiegu w czasie innych wątków (tego co i kiedy robią).

Rozwiązaniem problemu jest *semantyka współdzielonej własności*:

* współdzielonej, ponieważ dane są zarządzane przez grupę,

* własności, ponieważ dane są niszczone, kiedy grupa staje się pusta.

Referencja w Javie i C# ma semantykę współdzielonej własności.

# `std::shared_ptr`

* `#include <memory>`

* Inteligentny wskaźnik o semantyce wspołdzielonej własności.

* Jest to typ szablonowy: argumentem szablonu jest typ zarządzanych
  danych.

* Przeciwstawność `std::unique_ptr`.

* Obiekt tego typu może być kopiowany i przenoszony.

* Obiekt, który przyjmuje dane do zarządzania, tworzy grupę obiektów
  zarządzających.  Na początku grupa ma tylko jeden obiekt
  zarządzający.

* Kiedy kopiujemy obiekt zarządzający, tworzymy kolejny obiekt
  zarządzający, który należy do tej samej grupy obiektów
  zarządzających.

* Zarządzane dane są niszczone, kiedy ostatni z obiektów
  zarządzających jest niszczony.

* Dane nie wiedzą, że są zarządzane, a ich typ nie musi być
  przygotowany w specjalny sposób, np. nie musi być wyprowadzony z
  jakiegoś typu bazowego.

* Tak wydajny czasowo i pamięciowo, jak ta sama funkcjonalność
  poprawnie zaimplementowana z użyciem surowych wskaźników.

* Obiekt tej klasy zabiera dwa razy więcej pamięci w porównaniu do
  surowego wskaźnika.

# Szczegóły

## Użycie

Przykład niżej pokazuje podstawowe użycie.

{% highlight c++ %}
{% include_relative basic.cc %}
{% endhighlight %}

## Jak to działa.

* Grupa obiektów zarządzających posiada jedną **strukturę
  sterującą**.  Struktura jest alokowana dynamicznie przez obiekt,
  który przyjął dane do zarządzania.

* Obiekt zarządzający posiada wskaźnik do struktury sterującej swojej
  grupy.

* Licznik odwołań (ang. a reference count), czyli rozmiar grupy, jest
  polem w strukturze sterującej.

* Licznik odwołań jest inkrementowany, kiedy obiekt zarządzający jest
  kopiowany.

* Licznik odwołań jest dekrementowany, kiedy obiekt zarządzający jest
  niszczony.

* Dane zarządzane są niszczone, kiedy licznik odwołań osiąga 0.

## Z `unique_ptr` do `shared_ptr`

Możemy przenieść własność z obiektu typu `unique_ptr` do obiektu typu
`shared_ptr` w ten sposób:

{% highlight c++ %}
{% include_relative u2s.cc %}
{% endhighlight %}

Ale lepiej jest tak:

{% highlight c++ %}
{% include_relative u2s_better.cc %}
{% endhighlight %}

Możemy przenieść własność z r-wartości typu `unique_ptr` do obiektu
typu `shared_ptr`, ponieważ typ `shared_ptr` ma konstruktor, który
przyjmuje przez r-referencję obiekt typu `unique_ptr`.  W przykładzie
niżej, tworzymy obiekt typu `shared_ptr` za podstawie obiektu
tymczasowego typu `unique_ptr` zwracanego przez funkcję:

{% highlight c++ %}
{% include_relative u2s_example.cc %}
{% endhighlight %}

## Wydajność

Obiekt typu `shared_ptr` zabiera dwa razy więcej pamięci jak surowy
wskaźnik, ponieważ zawiera dwa pola składowe:

* wskaźnik do zarządzanych danych,

* wskaźnik do struktury sterującej.

Dochodzi do tego jeszcze pamięć dla struktury sterującej, ale to nic
wielkiego, bo jest ona współdzielona przez obiekty zarządzające.

Wskaźnik do zarządzanych danych mógłby być przechowywany w strukturze
sterującej, ale wtedy dostęp do zarządzanych danych byłby wolniejszy,
bo wymagałby dodatkowego odwołania pośredniego (przez wskaźnik).

## `std::make_shared`

Kiedy tworzymy dane zarządzane i obiekt zarządzający, możemy podać typ
zarządzanych danych dwa razy (i być może się pomylić):

{% highlight c++ %}
{% include_relative make_shared.cc %}
{% endhighlight %}

Ale możemy użyć szablonu funkcji `make_shared` i podać typ tylko raz,
co jest mniej podatne na błędy:

{% highlight c++ %}
{% include_relative make_shared2.cc %}
{% endhighlight %}

Szablon funkcji `make_shared` przyjmuje typ zarządzanych danych jako
argument szablonu.

Podobnie do funkcji `make_unique`, funkcja `make_shared` tworzy dane
zarządzane i obiekt zarządzający, a następnie zwraca obiekt
zarządzający.  Nie będzie narzutu wydajnościowego, ponieważ funkcja
najprawdopodobniej będzie wkompilowana, będzie zastosowana
optymalizacja wartości powrotu, a konstruktor przenoszący zostanie
pominięty.

Co ciekawe, `make_shared` alokuje *w jednym kawałku* (czyli z jedną
alokacją pamięci) pamięć dla zarządzanych danych i struktury
sterującej, a następnie *tworzy w miejscu* (ang. to create in place,
czyli pod wskazanym adresem, bez alokacji pamięci) dane zarządzane i
strukturę sterującą, co jest szybsze niż dwie osobne alokacje pamięci.

# Podsumowanie

* Obiekt klasy `shared_ptr<A>` pozwala na współdzielenie danych typu
  `A`, które były zaalokowane dynamicznie.

* Cel: zniszczyć zarządzane dane wtedy, kiedy nie są już potrzebne.

* Obiekt zarządzający typu `shared_ptr` jest dwa razy większy niż
  surowy wskaźnik.

* Możemy łatwo przekazać własność z `unique_ptr` to `shared_ptr`, ale
  nie odwrotnie.

# Quiz

* Jaka jest różnica między `unique_ptr` i `shared_ptr`?

* W jaki sposób należy przygotować typ danych, żeby `shared_ptr` mógł
  nim zarządzac?

* Dlaczego `shared_ptr` potrzebuje struktury sterującej?
