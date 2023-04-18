#include <iostream>
#include <memory>
#include <utility>

using namespace std;

struct A
{
};

struct B
{
};

struct C: A, B
{
};

template <typename Callable, typename FirstArg>
struct F
{
  Callable &&m_c;
  FirstArg &&m_a;

  F(Callable &&c, FirstArg &&a): m_c(forward<Callable>(c)),
				 m_a(forward<FirstArg>(a))
  {
  }

  template <typename SecondArg>
  auto
  operator()(SecondArg &&b)
  {
    return forward<Callable>(m_c)(forward<FirstArg>(m_a),
				  forward<SecondArg>(b));
  }
};

int
main()
{
  cout << "Test #1:\n";
  {
    F f(make_unique<C, A, B>, A{});
    auto up = f(B{});
  }

  cout << "Test #2:\n";
  {
    F f([](auto &&a, auto &&b)
    {return make_unique<C>(forward<decltype(a)>(a),
			   forward<decltype(b)>(b));}, A{});
    auto up = f(B{});
  }
}
