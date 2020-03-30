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
będzie wywołany i nie będzie wkompilowany w miejsce wywołania.  Proszę
sprawdzić kod wynikowy przykładu niżej (z Code Explorer lub z użyciem
narzędzia `objdump`).

{% highlight c++ %}
{% include_relative run1.cc %}
{% endhighlight %}

# Callable w czasie kompilacji

Jeżeli w czasie kompilacji callable jest znane i nie zmienia się w
czasie uruchomienia, to może ono być wkompilowane (ang. inlined) w
miejscu wywołania.  Jeżeli chcemy użyć inne callable, to musimy
zmienić kod źródłowy.  Oto przykład:

{% highlight c++ %}
{% include_relative compile1.cc %}
{% endhighlight %}

# Wydajność

<!-- LocalWords: callable -->
