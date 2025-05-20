template <typename F, typename... P>
concept Callable = requires (F f, P... p)
  {
    f(p...);
  };

void g();
void g(int);
void g1(int, bool);

int main()
{
  static_assert(Callable<void()>);
  static_assert(Callable<decltype(static_cast<void(*)()>(g))>);
  static_assert(Callable<decltype(static_cast<void(*)(int)>(g)), int>);
  static_assert(Callable<decltype(g1), int, bool>);
}
