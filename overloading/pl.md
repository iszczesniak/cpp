---
title: Przeciążenia
---

# Wyprowadzenie

Funkcje (zwykłe, nieszablonowe) mogą być przeciążane.  Także szablony
funkcji mogą być przeciążone.  Kiedy wywołujemy funkcję, kompilator
musi wybrać funkcję spośród zbioru przeciążeń.

Już dla prostych funkcji możemy mieć problem określić które
przeciążenie zostanie wywołane.  Na przykład:

```cpp
{% include_relative spec-vs-over.cc %}
```

Wybór przeciążenia (ang. overload resolution) ma kilka składowych:

* wybór spośród zwykłych funkcji: tutaj dozwolone są konwersje typów
  między typem argumentu wywołania, a typem parametru funcji,

* wybór spośród szablonów funkcji: tutaj typy szablonu muszą być
  doskonale wywnioskowane,

* wybór specjalizacji dla już wybranego szablonu podstawowego.

W wyborze przeciążenie, funkcje mają pierwszeństwo, potem są wybierane
szablony funkcji.

Specjalizacje szablonów nie mają wpływu na wybór szblonu podstawowego.

## Klas nie można przeciążać.

Możemy zdefiniować tylko jeden szablon klasy.  Jest to szablon
podstawowy, który możemy częściowo albo całkowicie specjalizować.  Nie
możemy definiować kolejnych szablonów podstawowych dla klasy o tej
samej nazwie, bo byłoby to przeciążanie klasy, na co C++ nie pozwala.

# Przeciążenia a specjalizacja

Różnica między specjalizacją szablonu, a przeciążeniem szablonu.

Jak wybrany jest szablon podstawowy, to potem wybierana jest najlepiej
pasująca specjalizacja szablonu.
