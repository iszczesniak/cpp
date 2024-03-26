#include <type_traits>

// Here we accept a callable by pointer as a template argument.  Here
// we define the type of accepted functions.  We perfectly return the
// value regardless that interface.
template <int &(*F)()>
decltype(auto)
foo1()
{
  return F();
}

// Here we accept a callable by reference as a function argument.
template <typename F>
decltype(auto)
foo2(F &f)
{
  return f();
}

int &loo()
{
  static int i = 1;
  return i;
}

int roo()
{
  return 1;
}

auto c = []() -> int & {static int i = 1; return i;};

struct
{
  int &
  operator()() const
  {
    static int i = 1;
    return i;
  }
} f;

int
main()
{
  foo1<loo>();
  static_assert(std::is_same_v<decltype(foo1<loo>()), int &>);
  // To make the following compile, we would have to change the type
  // of functions accepted by foo1.
  // foo1<roo>();
  // static_assert(std::is_same_v<decltype(foo1<roo>()), int>);

  // A closue is implicitly converted to a function pointer.
  foo1<c>();
  static_assert(std::is_same_v<decltype(foo1<c>()), int &>);

  // A functor is not implicitly converted to a function pointer.
  // foo1<f>();
  
  foo2(loo);
  static_assert(std::is_same_v<decltype(foo2(loo)), int &>);
  foo2(roo);
  static_assert(std::is_same_v<decltype(foo2(roo)), int>);

  foo2(c);
  static_assert(std::is_same_v<decltype(foo2(c)), int &>);

  foo2(f);
  static_assert(std::is_same_v<decltype(foo2(f)), int &>);
  
  // To make the following line compile, function foo2 should take its
  // argument by a forwarding reference.
  // foo2([]{return 1;});
}
