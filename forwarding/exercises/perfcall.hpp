#ifndef PERFCALL
#define PERFCALL

#include <utility>

decltype(auto)
f(auto &&g)
{
  return std::forward<decltype(g)>(g)();
}

#endif // PERFCALL_HPP
