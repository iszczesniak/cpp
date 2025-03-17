#include <iostream>

// name --------------------------------------------------------------

template <typename T>
struct name
{
  T m_name;
};

template <typename T>
T &
get_name(name<T> &a)
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
  T m_weight;
};

template <typename T>
T &
get_weight(weight<T> &a)
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

template <typename... P>
struct A: P...
{
  A(P &&... p): P(std::forward<P>(p))...
    {
    }
};

template <typename P1, typename... Ps>
std::ostream &
operator << (std::ostream &out, const A<P1, Ps...> &a)
{
  out << static_cast<const P1 &>(a);
  (... , (out << ", " << static_cast<const Ps &>(a)));
  return out;
}

// The main function -------------------------------------------------

int
main()
{
  using type = A<name<const char *>, weight<int>>;

  type a(name<const char *>("Hello"), weight<int>(1));
  type b = a;
  get_weight(a) = 2;
  get_name(a) = "World";

  std::cout << a << std::endl;
  std::cout << b << std::endl;
}
