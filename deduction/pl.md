---
title: Wnioskowanie argumentów szablonu
---

# Wprowadzenie

Argumenty szablonu mogą być:

* wnioskowane (najczęściej stosowane),

* jawnie podane (czasami potrzebne),

* domyślnie podane (czasami wygodne).

Ten przykład pokazuje wyżej wymienione przypadki:

{% highlight c++ %}
{% include_relative intro.cc %}
{% endhighlight %}

Skoncentrujemy się na wnioskowaniu, ale pierwsze krótko omówimy jawne
podawanie argumentów i domyślne argumenty.

## Jawnie podane argumenty szablonu

Kiedy korzystamy z kontenerów bilbioteki standardowej (a każdy robił
to na pewno), jawnie podajemy argumenty szablonu jako część nazwy typu
używając `<>`, czyli składni `typ kontenera<lista argumentów>`:

{% highlight c++ %}
{% include_relative explicit.cc %}
{% endhighlight %}

Tej składni możemy też użyć przy wywołaniu funkcji (a nie definiowaniu
typu, np. kontenera), co jest przydatne w dwóch przypadkach:

* chcemy innych argumentów niż te wnioskowane przez kompilator, co
  zrobiliśmy w przykładzie wyżej z funkcją `print`,

* musimy jawnie podać argumenty, bo kompilator nie jest ich w stanie
  wywnioskować.

Kompilator wnioskuje argumenty szablonu na podstawie typów wyrażeń,
które są przekazywane w wyrażeniu wywołania funkcji, albo
konstruktora.

## Domyślne argumenty szablonu

# Wnioskowanie argumentów szablonu

Kiedy wywołujemy funkcję szablonową, kompilator może wywnioskować
argumenty szablonu.
