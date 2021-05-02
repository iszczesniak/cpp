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

Specyfikator typu `auto` pozwala na pisanie uogólnionego kodu, bo nie
musimy podawać konkretnego typu, a prosimy kompilator o
wywniowskowanie go na podstawie kodu.

# Motywacja

Pisanie typów w starym C++ było niewygodne, pracochłonne, a przy tym
łatwo można było popełnić błędy, których kompilator czasami nie był w
stanie wychwycić.  Typowym przykładem była konieczność podawania typów
iteratorów do złożonych struktur danych.  Teraz łatwo używać
iteratorów deklarując ich typ jako `auto`.  Oto przykład:

{% highlight c++ %}
{% include_relative motivation1.cc %}
{% endhighlight %}

Łatwiej jest pozwolić kompilatorowi wywnioskować typ, zamiast domyślać
się (często błędnie) czy sprawdzać w dokumentacji.  Oto przykład:

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Możemy podsumować, że jeżeli nie wiemy (i nie chcemy wiedzieć albo nie
chcemy użyć), jakiego typu funkcja zwraca wartość, to możemy użyć
specyfikatora typu `auto`.  Na przykład, funkcja `size` kontenerów
zwraca wartość typu `T::size_type`, ale łatwiej jest nam użyć `auto`.
Na przykład:

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

Czasami nie jesteśmy w stanie podać typu, bo go nie znamy, jak w
przypadku *domknięć*, czyli funktorów typów anonimowych, które są
wynikiem opracowania wyrażenia lambda.

{% highlight c++ %}
{% include_relative closure.cc %}
{% endhighlight %}

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

