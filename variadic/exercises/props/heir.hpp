#ifndef HEIR_HPP
#define HEIR_HPP

#include <iostream>
#include <utility>

// Type A can use properties. ----------------------------------------

template <typename... P>
struct heir: P...
{
  heir(const P &&... p): P(p)...
    {
    }
};

template <typename P1, typename... Ps>
std::ostream &
operator << (std::ostream &out, const heir<P1, Ps...> &a)
{
  out << static_cast<const P1 &>(a);
  (... , (out << ", " << static_cast<const Ps &>(a)));
  return out;
}

#endif // HEIR_HPP
