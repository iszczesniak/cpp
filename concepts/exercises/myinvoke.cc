#include <iostream>
#include <utility>
#include <type_traits>

template <typename F>
concept member_pointer = std::is_member_pointer_v<F>;

// A generic primary template overload.
template <typename G, typename ... Args>
void myinvoke(G &&g, Args &&... args)
{
  std::forward<G>(g)(std::forward<Args>(args)...);
}

// A more specialized primary template.
template <member_pointer G, typename O, typename ... Args>
void
myinvoke(G g, O &&o, Args &&... args)
{
  (std::forward<O>(o).*g)(std::forward<Args>(args)...);
}

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
