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
będzie wywołany i nie będzie wkompilowany w miejsce wywołania.

{% highlight c++ %}
{% include_relative run1.cc %}
{% endhighlight %}

# Callable w czasie kompilacji

Jeżeli w czasie kompilacji callable jest znane i nie zmienia się w
czasie uruchomienia, to może ono być wkompilowane (ang. inlined) w
miejscu wywołania.



Zmieniamy kod źródłowy.  W czasie uruchomienia callable już nie możemy
zmieniać.  Najprawdopodobniej kod callable został wkompilowany w
miejsce wywołania callable.

Nawet jeżeli callable jest wskaźnikiem, to 

# Wydajność

<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
