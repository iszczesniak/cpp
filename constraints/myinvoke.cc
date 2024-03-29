#include <iostream>
#include <utility>
#include <type_traits>

// A generic primary template overload.
template <typename G, typename ... Args>
void myinvoke(G &&g, Args &&... args)
{
  std::forward<G>(g)(std::forward<Args>(args)...);
}

// A more-specific primary template overload.
template <typename G, typename O, typename ... Args>
void
myinvoke(G &&g, O &&o, Args &&... args) requires requires
{
  (std::forward<O>(o).*std::forward<G>(g))(std::forward<Args>(args)...);
}
{
  (std::forward<O>(o).*std::forward<G>(g))(std::forward<Args>(args)...);
}

// A primary template that is as specific as the one above.
//
// template <typename G, typename O, typename ... Args> requires
// std::is_member_pointer_v<G>
// void
// myinvoke(G &&g, O &&o, Args &&... args)
// {
//   (std::forward<O>(o).*std::forward<G>(g))(std::forward<Args>(args)...);
// }

void foo()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void goo(int)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

struct A
{
  void foo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }

  void goo(int)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

int
main()
{
  A a;

  myinvoke(foo);
  myinvoke(goo, 1);
  myinvoke([]{});
  myinvoke(&A::foo, a);
  myinvoke(&A::goo, a, 1);
}
