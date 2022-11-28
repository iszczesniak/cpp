#include <vector>

// Here we have a structure that has a vector of elements of type T.
// No biggie.
template <typename T>
struct A
{
  std::vector<T> m_t;
};

// But those elements want to have a reference to the object that owns
// them.  And that's a problem.
template <typename T>
struct B
{
  T &m_t;

  B(T &t): m_t(&t)
  {
  }
};

// But those elements want to have a reference to the object that owns
// them.  And that's a problem.
template <template <typename> typename T>
struct C
{
  T<C> &m_t;

  C(T<C> &t): m_t(&t)
  {
  }
};

int
main()
{
  // A<B<A<B<...>>>> a;
  A<C<A>> a;
}
