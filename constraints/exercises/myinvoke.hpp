#ifndef MYINVOKE_HPP
#define MYINVOKE_HPP

#include <utility>
#include <type_traits>

// A generic primary template overload.
template <typename G, typename... Args>
void myinvoke(G &&g, Args &&... args)
{
  std::forward<G>(g)(std::forward<Args>(args)...);
}

// A more specialized primary template overload.
// template <typename G, typename O, typename... Args>
// void
// myinvoke(G &&g, O &&o, Args &&... args) requires requires
// {
//   (std::forward<O>(o).*std::forward<G>(g))(std::forward<Args>(args)...);
// }
// {
//   (std::forward<O>(o).*std::forward<G>(g))(std::forward<Args>(args)...);
// }

// We can implement the above overloard simpler with a standard trait.
template <typename G, typename O, typename ... Args> requires
std::is_member_function_pointer_v<G>
void
myinvoke(G &&g, O &&o, Args &&... args)
{
  (std::forward<O>(o).*std::forward<G>(g))(std::forward<Args>(args)...);
}

#endif // MYINVOKE_HPP
