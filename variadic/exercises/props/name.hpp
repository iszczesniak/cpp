#ifndef NAME_HPP
#define NAME_HPP

#include <iostream>

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
const T &
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

#endif // NAME_HPP
