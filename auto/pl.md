---
title: Typ auto
---

# Typ `auto`

Specyfikator typy `auto` oznacza, że kompilator ma wywnioskować typ na
podstawie typu wyrażenia inicjalizującego.  Specyfikator można użyć w
deklaracji typu:

* zmiennej,

* parametru wyrażenia lambda,

* wartości zwracanej przez funkcję.

Wnioskowanie typu `auto` odbywa się tak, jak wnioskowanie argumentów
szablonu.  Jeżeli typem jest `auto &&`, to kompilator wywnioskuje, czy
referencja powinna być typu l-wartość czy r-wartość w zależności od
kategorii wartości wyrażenia inicjalizującego referencję.

Żeby zobaczyć wywnioskowany typ w czasie kompilacji, w kodzie
wprowadzono błąd, o którym kompilator informuje jednocześnie wypisując
interesujący nas typ.

{% highlight c++ %}
{% include_relative auto.cc %}
{% endhighlight %}
