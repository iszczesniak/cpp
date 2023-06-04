# Wstęp

C++11 wprowadził **szablon wariadyczny** (ang. a variadic template),
który potrafi przyjąć dowolną liczbę argumentów szablonu, także
zerową.  Szablon wariadyczny poznamy po trójkropku `...` w liście
parametrów szablonu:

```cpp
{% include_relative intro.cc %}
```

# Paczka parametrów

Trójkropek jest częścią definicji **paczki parametrów** (ang. a
parameter pack), po którym następuje (bez oddzielającej spacji) nazwa
paczki.  Paczka parametrów szablonu może być szablonu albo funkcji.

## Paczka parametrów szablonu

Parametry szablonu w paczce są tego samego rodzaju: w przykładzie
wyżej są typowe, a w przykładzie niżej wartościowe.

```cpp
{% include_relative value_pack.cc %}
```

### Rozwinięcie paczki

Nazwę paczki z trójkropkiem nazywa się rozwinięciem paczki (ang. pack
expansion).  Rozwinięcie paczki parametrów szablonu jest listą
argumentów szablonu oddzielonych przecinkami:

```cpp
{% include_relative expansion.cc %}
```

W przykładach wyżej argumenty szablonu musiały być jawnie podane, bo
funkcje i konstruktor nie miały parametrów i argumentów wywołania, na
podstawie których argumenty szablonu mogły być wywnioskowane.
Argumenty dla parametrów szablonu w paczce są wnioskowane na podstawie
definicji **paczki parametrów funkcji** i argumentów wywołania
funkcji.

## Paczka parametrów funkcji

Paczka parametrów funkcji jest definiowana w liście parametrów
funkcji:

### Rozwinięcie paczki

Rozwinięcie paczki

# Sekwencyjne przetwarzanie

# Doskonałe przekazywanie
