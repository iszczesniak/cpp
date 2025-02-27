#include <vector>

using namespace std;

// We want to implement a container of elements, where the elements
// have a reference to the container, i.e., an element knows who owns
// it.  We have two element types:
//
// A - disfunctional because of the circular dependency,
//
// B - working fine with the circular dependency resolved.

// Those elements want to have a reference to the object that owns
// them.  And that's a problem, because this creates a circular
// dependency.
template <typename T>
struct A
{
  T &m_t;

  A(T &t): m_t(t)
  {
  }
};

// We can break the circular dependency with the template-kind
// parameter of a template and injected class names.  This is not a
// perfect solution, because we require the owning type T to be
// templated with a single argument, so other types will not be
// accepted.
template <template <typename...> typename T>
struct B
{
  // "B" is an injected class name, i.e., we do not have to write
  // "B<T>" and that helps us break the circular dependency.
  T<B> &m_t;

  B(T<B> &t): m_t(t)
  {
  }
};

int
main()
{
  // We can't possibly define a container of elements A because of the
  // circular dependency.
  // vector<A<vector<A<vector<A<vector... a1;
  // vector<A<vector>> a2;

  // Is the initialization ill-formed or undefined-behaved?  Note that
  // we use uninitialized container "b" to initialize element B(b).
  vector<B<vector>> b = {B(b)};
  b.push_back(B(b));
  // Looks like a snake eating its own tail.
  b.emplace_back(b);
}
