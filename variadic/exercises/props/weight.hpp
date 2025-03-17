#ifndef WEIGHT_HPP
#define WEIGHT_HPP

#include <iostream>

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
const T &
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

#endif // WEIGHT_HPP
