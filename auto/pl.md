---
title: Typ auto
---

# Typ `auto`

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
