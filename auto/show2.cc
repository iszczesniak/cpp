template <typename... T>
class ER;

template <typename... T>
void foo(T... t)
{
  ER<T...> er;
}

void goo(auto... t)
{
  ER<decltype(t)...> er;
}

int
main()
{
  // Uncomment the lines to see the types reported.
  // foo(1, .1);
  // goo(1, .1);
}
