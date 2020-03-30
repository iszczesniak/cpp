---
title: Callable - kontynuacja
---

# Wprowadzenie

Wiemy już, że callable jest czymś, co możemy wywołać, czyli użyć w
wyrażeniu wywołania.  Od typu callable zależy z jakimi argumentami
możemy callable wywołać i czy callable zwróci wynik.

Callable może być określone (o który callable dokładnie chodzi) w
czasie **uruchomienia**, albo **kompilacji**.

# Callable w czasie uruchomienia

Jeżeli callable jest ustalane w czasie uruchomienia, to kod callable
będzie wywołany i nie będzie wkompilowany (ang. inlined) w miejsce
wywołania, no bo nie wiadomo co wkompilować.  Proszę sprawdzić kod
wynikowy przykładu niżej (z Code Explorer lub z użyciem narzędzia
`objdump`).

{% highlight c++ %}
{% include_relative run.cc %}
{% endhighlight %}

# Callable w czasie kompilacji

Jeżeli w czasie kompilacji callable jest znane i nie zmienia się w
czasie uruchomienia, to może ono być wkompilowane w miejscu wywołania.
Jeżeli chcemy użyć inne callable, to musimy zmienić kod źródłowy.  Oto
przykład:

{% highlight c++ %}
{% include_relative compile1.cc %}
{% endhighlight %}

Przykład niżej pokazuje wkompilowanie domknięcia, co pokazuje, że
używanie domknięcia nie wprowadza narzutu wydajnościowego (czyli nie
spowalnia).

{% highlight c++ %}
{% include_relative compile2.cc %}
{% endhighlight %}

# Przekazywanie callable

# Wydajność

<!-- LocalWords: callable -->
