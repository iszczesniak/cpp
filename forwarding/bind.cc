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
    cout << __PRETTY_FUNCTION__ << endl;
  }

  template <typename SecondArg>
  auto
  operator()(SecondArg &&b)
  {
    cout << __PRETTY_FUNCTION__ << endl;
    return forward<Callable>(m_c)(forward<FirstArg>(m_a),
				  forward<SecondArg>(b));
  }
};

// A deduction guide.
template <typename Callable, typename FirstArg>
F(Callable &&, FirstArg &&) -> F<Callable, FirstArg>;

auto
loo(A &a, B &b)
{
  return make_unique<C>(a, b);
}

int
main()
{
  cout << "Test #1:\n";
  {
    A a;
    F f(make_unique<C, A, B>, move(a));
    auto up = f(B{});
  }

  cout << "Test #2:\n";
  {
    A a;
    F f([](auto &&a, auto &&b)
    {return make_unique<C>(forward<decltype(a)>(a),
			   forward<decltype(b)>(b));}, move(a));
    auto up1 = f(B{});
    B b;
    auto up2 = f(b);
  }

  cout << "Test #3:\n";
  {
    A a;
    F f(make_unique<C, A &, B>, a);
    auto up1 = f(B{});
  }

  cout << "Test #4:\n";
  {
    A a;
    B b;
    F f(loo, a);
    auto up = f(b);
  }
}
