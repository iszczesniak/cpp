#include <type_traits>
#include <utility>

template <typename G, typename O, typename ... Args>
requires std::is_member_function_pointer<G>
void myinvoke(G &&g, O &&o, Args &&... args)
{
  std::forward<O>(o).*std::forward<G>(g)()
    (std::forward<Args>(args)...);
}

struct A
{
  void foo()
  {
  }
};

int
main()
{
  A a;
  myinvoke(&A::foo, a);
}
