template <typename T>
void
foo(T (&&t)[4])
{
}

template <unsigned I>
void
foo(int (&&t)[I])
{
}

int
main()
{
  foo({1, 2, 3, 4, 5});
}
