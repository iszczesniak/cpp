---
title: Specyfikator typu `auto`
---

# Wprowadzenie

Specyfikator typu `auto` oznacza, że kompilator ma wywnioskować typ na
podstawie typu wyrażenia inicjalizującego.  W miejsce specyfikatora
`auto` kompilator wstawia wywniowskowany typ.  Specyfikator można użyć
w deklaracji typu:

* zmiennej,

* parametru wyrażenia lambda,

* wartości zwracanej przez funkcję.

# Motywacja

* closure

* wymuszona inicjalizacja

* auto i = v.size();

# Wnioskowanie typu zmiennej

Wnioskowanie typu `auto` odbywa się tak, jak wnioskowanie typowych
argumentów szablonu.

Jeżeli typem jest `auto &&`, to kompilator wywnioskuje, czy referencja
powinna być typu l-wartość czy r-wartość w zależności od kategorii
wartości wyrażenia inicjalizującego referencję.

{% highlight c++ %}
{% include_relative auto.cc %}
{% endhighlight %}

Żeby zobaczyć wywnioskowany typ w czasie kompilacji, w kodzie
wprowadzono błąd, o którym kompilator informuje jednocześnie wypisując
interesujący nas typ.

# Wnioskowanie typu parametru wyrażenia lambda

# Wnioskowanie typu wartości zwracanej przez funkcję

# `auto` jako typ zmiennej deklarowanej w pętli for: przykład z
  dostępem do elementów std::map

# `decltype`

