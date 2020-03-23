---
title: Wyrażenia wywołania, callable
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
która używa właśnie operatora `<`.  Identyczny efekt uzyskamy, jeżeli
jawnie podamy trzeci argument:

{% highlight c++ %}
{% include_relative motivation3.cc %}
{% endhighlight %}

Możemy sortować w kolejności rosnącej, jeżeli użyjemy *funktora*
struktury `std::greater`.  Funktor to obiekt, który ma zdefiniowany
operator wywołania `()` (ang. call operator).  Struktura
`std::greater` używa operatora `>`, więc musimy go zdefiniować,
zamiast operatora `<`.

{% highlight c++ %}
{% include_relative motivation4.cc %}
{% endhighlight %}

Nie musimy jednak polegać na operatorze `<`.  Funkcji `std::sort`
możemy przekazać cokolwiek, na czym możemy wykonać operator wywołania
`()`

# Wyrażenia wywołania


<!-- LocalWords: destructor expr lvalue lvalues rvalue rvalues RVO -->
