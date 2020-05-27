template <unsigned I> requires (I < 10)
void foo();

template <typename T, unsigned I> requires (I < 10)
struct mine;

template <unsigned I>
struct mine<int, I>
{
};

template <unsigned I>
struct mine<double, I>
{
};

int
main()
{
  // Link error: foo not defined.
  // foo<9>();

  mine<int, 9> mi;

  // Error: only declared, not defined.
  // mine<long, 9> ml;

  // These calls violate the template constraints.
  // foo<10>();
  // mine<int, 10> mi;
  // mine<long, 10> ml;
}
