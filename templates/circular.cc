#include <vector>

// Here we have a structure that has a vector of elements of type T.
// No biggie.
template <typename T>
struct A
{
  std::vector<T> m_t;
};

// But those elements want to have a reference to the object that owns
// them.  And that's a problem, because this creates a circular
// dependency.
template <typename T>
struct B
{
  T &m_t;

  B(T &t): m_t(&t)
  {
  }
};

// We can break the circular dependency with the template-kind
// parameter of a template.
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
