---
title: Wyrażenia wywołania
---

# Wprowadzenie

W poniższym sortowaniu porównywane są liczby całkowite, dla których
jest ustalony porządek (liniowy) z użyciem operatora `<`:

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

W przykładzie niżej próbujemy posortować obiekty typu klasowego, ale
musimy zdefiniować porządek

Kompilacja jednak kończy się błędem, bo nie ma ustalonego porządku z
użyciem operatora `<`:

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Możemy zdefiniować zdefiniować operator

# Wyrażenia wywołania


<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
