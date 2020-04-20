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
podawanie argumentów szablonów i domyślne argumenty szablonów.

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
które są przekazywane w wyrażeniu wywołania funkcji (kiedy wywołujemy
funkcję) czy konstruktora (kiedy tworzymy obiekt).  Jeżeli nie jest w
stanie wywnioskować argumentów, to musimy jawnie je podać.

Przykład niżej pokazuje implementację fabryki obiektów.  Argument
wywołania fabryki przekazujemy do konstruktora obiektu, którego typ
jest określony przez argument szablonu.  Kompilator nie jest w stanie
określić typu obiektu, więc musimy go jawnie podać.

{% highlight c++ %}
{% include_relative explicit2.cc %}
{% endhighlight %}

### Kolejność argumentów

Kolejność argumentów szablonu ma znaczenie (tak jak w przypadku
argumentów wywołania funkcji), bo argumenty są pozycyjne, czyli od
pozycji argumenty zależy to, o który argument nam chodzi.  Tak więc
jeżeli chcemy podać drugi argument, to musimy podać też pierwszy
argument.

Jeżeli w powyższym przykładzie z fabryką zmienimy kolejność
argumentów, to typ argumentu wywołania konstruktora będziemy musieli
także podać jawnie, chociaż mógłby być wywnioskowany.  A musimy jawnie
podać pierwszy argument, bo musimy podać drugi argument.

{% highlight c++ %}
{% include_relative explicit3.cc %}
{% endhighlight %}

## Domyślne argumenty szablonu

Parametr szablonu (każdego rodzaju: typowy, wartościowy i szablonowy)
może mieć zdefiniowany domyślny argument, które będzie użyty, jeżeli
kompilator nie jest w stanie wywnioskować argumentu.

Domyślny argument podajemy po nazwie parametru z użycien znaku `=`.
Oto przykład:

{% highlight c++ %}
{% include_relative explicit3.cc %}
{% endhighlight %}

### Domyślny callable



# Wnioskowanie argumentów szablonu

Kiedy wywołujemy funkcję szablonową, kompilator może wywnioskować
argumenty szablonu.
