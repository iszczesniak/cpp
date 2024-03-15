#include <vector>
#include <cassert>

using namespace std;

struct matrix
{
  struct proxy
  {
    using p_type = vector<bool>::reference;
    p_type m_normal, m_reverse;

    proxy(p_type normal, p_type reverse):
      m_normal(normal), m_reverse(reverse)
    {
    }
    
    operator bool() const
    {
      return m_normal;
    }

    proxy &
    operator = (bool flag)
    {
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
  
  proxy
  operator()(unsigned i, unsigned j) const
  {
    return proxy(m_vov[i][j], m_vov[j][i]);
  }
};

int
main()
{
  matrix m(6);
  assert(m(0, 0) == false);
  
  m(0, 1) = true;
  assert(m(1, 0) == true);
  m(0, 4) = true;
  m(1, 2) = true;
  m(1, 4) = true;
  m(2, 3) = true;
  m(2, 5) = true;
  m(3, 5) = true;
}
