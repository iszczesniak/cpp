#include <iostream>
#include <set>
#include <string>

// name --------------------------------------------------------------

template <typename T>
struct name
{
  using name_type = T;
  name_type m_name;

  constexpr auto operator <=> (const name &) const = default;
};

// The non-const getter.
template <typename T>
auto &
get_name(name<T> &a)
{
  return a.m_name;
}

// The const getter.
template <typename T>
auto &
get_name(const name<T> &a)
{
  return a.m_name;
}

template <typename T>
std::ostream &
operator << (std::ostream &os, const name<T> &w)
{
  os << "name = " << w.m_name;

  return os;
}

// weight ------------------------------------------------------------

template <typename T>
struct weight
{
  using weight_type = T;
  weight_type m_weight;

  constexpr auto operator <=> (const weight &) const = default;
};

// The non-const getter.
template <typename T>
auto &
get_weight(weight<T> &a)
{
  return a.m_weight;
}

// The const getter.
template <typename T>
auto &
get_weight(const weight<T> &a)
{
  return a.m_weight;
}

template <typename T>
std::ostream &
operator << (std::ostream &os, const weight<T> &w)
{
  os << "weight = " << w.m_weight;

  return os;
}

// Type A can use properties. ----------------------------------------

template <typename ...P>
struct A: P...
{
  A(P && ...p): P(std::forward<P>(p))...
    {
    }

  constexpr auto operator <=> (const A &) const = default;
};

template <typename ...P>
std::ostream &
operator << (std::ostream &out, const A<P...> &a)
{
  ((out << static_cast<P>(a) << std::endl), ...);
  return out;
}

// The main function -------------------------------------------------

int
main()
{
  A<name<std::string>, weight<int>>
    a(name<std::string>("Hello"), weight<int>(1));

  auto b = a;
  get_weight(a) = 2;
  get_name(a) = "World";
  std::set s = {a, b};

  for(auto &e: s)
    std::cout << e << std::endl;
}
