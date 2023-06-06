#include <iostream>
#include <string>

// name --------------------------------------------------------------

template <typename T>
struct name
{
  using name_type = T;
  name_type m_name;

  name(const name_type &name): m_name(name)
  {
  }

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
const auto &
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

  weight(const weight_type &weight): m_weight(weight)
  {
  }

  constexpr auto operator <=> (const weight &) const = default;
};

// The non-const getter.
template <typename T>
constexpr auto &
get_weight(weight<T> &a)
{
  return a.m_weight;
}

// The const getter.
template <typename T>
constexpr const auto &
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

  std::ostream &
    operator << (std::ostream &out) const
  {
    (out << ... << static_cast<P>(*this));
    return out;
  }
};

// The main function -------------------------------------------------

int
main()
{
  A<name<std::string>, weight<int>>
    a(name<std::string>("Hello"), weight<int>(1));
  get_weight(a) = 2;
  get_name(a) = "World";
  //  std::cout << a;
  std::cout << (a < a);
}
