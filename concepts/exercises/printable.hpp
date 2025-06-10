#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include <iostream>
#include <ostream>

template <typename T>
concept printable = requires (T t, std::ostream out)
{
  out << t;
};

template <typename T> requires printable<T>
void print1(T &&t)
{
  std::cout << t << std::endl;
}

template <printable T>
void print2(T &&t)
{
  std::cout << t << std::endl;
}

void print3(printable auto &&t)
{
  std::cout << t << std::endl;
}

#endif // PRINTABLE_HPP
