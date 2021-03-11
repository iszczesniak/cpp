---
title: Specjalizacja szablonów
---

To samo zadanie rozwiązane z użyciem szablonów i ich
**specjalizacji**:

{% highlight c++ %}
{% include_relative generic2.cc %}
{% endhighlight %}

Przykład niżej ilustruje rekurencyjny szablon funkcji, gdzie
rekurencja jest przerwana przez specjalizację szablonu dla `N = 0`.
Nie ma *częściowej specjalizacji* szablonu funkcji, jest tylko *pełna
specjalizacja*, więc musimy jawnie podać także argument szablonu dla
parametru `T`, czyli `int`.

{% highlight c++ %}
{% include_relative print4.cc %}
{% endhighlight %}

# Podsumowanie

# Quiz

<!-- LocalWords: lvalue lvalues rvalue -->
