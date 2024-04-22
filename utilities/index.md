# Structured bindings

# Quasi-containers

## `std::pair`

* `#include <utility>`

* Para `p` obiektów typów A i B: \code{std::pair<A, B> p;}

* `p.first` - pierwszy element, `p.second` - drugi element

* Globalna funkcja szablonowa `std::make_pair` pozwala na tworzenie
  pary bez podania typów, kompilator wywnioskuje typy sam:
  `std::make_pair(1, "test");`

* Funkcja `std::tie`  pozwala na wygodne przypisanie wartości z
  pary do osobnych  zmiennych: `std::tie(f, s) = p;`

* Przeniesienie pary polega na przeniesieniu każdego z obiektów
  składowych.

* Ma zdefiniowane globalne operatory: \code{!= < == > <= >=}

# `std::tuple`

# `std::array` vs C-array

# `std::optional`

# `std::any`

# std::expected

# std::exchange

# Returning tuple with:

  auto foo()
  {
    return {1, 0.2, false};
  }

# Structured bindings

  