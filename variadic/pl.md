# Wstęp

C++11 wprowadził **szablon wariadyczny** (ang. a variadic template),
który potrafi przyjąć dowolną liczbę argumentów szablonu, także
zerową.  Szablon wariadyczny poznamy po trójkropku `...` w liście
parametrów szablonu:

```cpp
{% include_relative intro.cc %}
```

# Paczka parametrów

Trójkropek definiuje **paczkę parametrów szablonu** (ang. a template
parameter pack), który wpisujemy przed nazwią parametru.  Ten parametr
jest nazwą paczki.

# Sekwencyjne przetwarzanie
