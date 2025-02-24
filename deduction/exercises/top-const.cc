void foo(const int)
{
}

template <typename T>
void too(const T)
{
}

int main()
{
  foo(1);
  too(1);
  too(true);
}
