template <int N = 1>
struct test
{
};

template <template<int> typename T>
void
foo(T<> t)
{
}

int main()
{
  //  foo(test<int>{});
}
