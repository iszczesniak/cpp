#include <vector>
#include <cassert>

using namespace std;

struct matrix
{
  struct proxy
  {
    using p_type = vector<bool>::reference;

    // Here we could store a reference to a proxy, but proxies are
    // better used by value.  Proxies are usually temporary objects,
    // so we could end up with a dangling reference, i.e., to a
    // destroyed object.
    p_type m_normal, m_reverse;

    proxy(p_type normal, p_type reverse):
      m_normal(normal), m_reverse(reverse)
    {
    }
    
    // Casts to the boolean value.
    operator bool() const
    {
      return m_normal;
    }


    proxy &
    operator = (bool flag)
    {
      // We have to set the flag for the normal and the revese.
      m_normal = flag;
      m_reverse = flag;
      return *this;
    }
  };

  // Vector of vectors.
  vector<vector<bool>> m_vov;

  matrix(unsigned n): m_vov(n, vector<bool>(n))
  {
  }

  // This function has to return a proxy, so that we can assign to it
  // a boolean value.
  proxy
  operator()(unsigned i, unsigned j)
  {
    return proxy(m_vov[i][j], m_vov[j][i]);
  }
};

int
main()
{
  matrix m(4);
  assert(m(0, 0) == false);

  m(0, 1) = true;
  m(0, 2) = true;
  m(1, 3) = true;
  m(2, 3) = true;
  assert(m(3, 2) == true);
}
