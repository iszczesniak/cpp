---
title: Wyrażenia wywołania
---

# Wprowadzenie

W poniższym sortowaniu porównywane są liczby całkowite, dla których
jest ustalony porządek (liniowy) z użyciem operatora `<`:

{% highlight c++ %}
{% include_relative motivation.cc %}
{% endhighlight %}

W przykładzie niżej sortujemy obiekty typu klasowego.  Żeby kompilacja
powiodła się, musimy zdefiniować porządek z użyciem operatora `<`.
Operator zdefiniowaliśmy jako *stałą* funkcję składową, która drugi
argument operatora `<` przyjmuje jako argument wywołania funkcji
(pierwszym argumentem jest obiekt `*this`).

{% highlight c++ %}
{% include_relative motivation2.cc %}
{% endhighlight %}

Funkcja `std::sort` domyślnie używa operatora `<`, bo domyślną
wartością trzeciego argumentu wywołania tej funkcji jest domyślna
(ang. default-constructed) wartość obiektu struktury `std::less<A>`,
która używa właśnie operatora `<`.  Ten

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

Możemy sortować w kolejności rosnącej, jeżeli użyjemy 

Nie musimy jednak polegać na operatorze `<`.  Jeżeli chcemy sortować e

# Wyrażenia wywołania


<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
