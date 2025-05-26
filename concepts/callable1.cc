template <typename F, typename... P>
concept Callable = requires (F f, P... p)
{
  f(p...);
};

void f(int, bool);

void g();
void g(int);

int main()
{
  // Here we pass a function type 'void()', and make sure we can call
  // it with no argument.
  static_assert(Callable<void()>);

  // Can we call f with an int and a bool?
  static_assert(Callable<decltype(f), int, bool>);

  // We cannot just say 'decltype(g)', because the compiler wouldn't
  // know which overload we mean, and thefore we need to static_cast.
  static_assert(Callable<decltype(static_cast<void(*)()>(g))>);
  static_assert(Callable<decltype(static_cast<void(*)(int)>(g)), int>);

  // The declaration below overshadows the 'void g()' overload, so now
  // (that there's just one g in scope) we can say 'decltype(g)'.
  void g(int);
  static_assert(Callable<decltype(g), int>);
}
