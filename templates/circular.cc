#include <vector>

using namespace std;

// Those elements want to have a reference to the object that owns
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
// parameter of a template and injected class names.  This is not a
// perfect solution, because we require the owning type T to be
// templated with a single argument.
template <template <typename> typename T>
struct C
{
  // "C" is an injected class name, i.e., we do not have to write
  // "C<T>".
  T<C> &m_t;

  C(T<C> &t): m_t(t)
  {
  }
};

int
main()
{
  // We can't possibliy define a type using B.
  // vector<B<vector<B<...>>>> a;

  // Is the initialization ill-formed?  Note we use uninitialized "a".
  vector<C<vector>> a = {C(a)};
  a.emplace_back(a);
  a.push_back(C(a));
}
