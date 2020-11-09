template <typename T>
struct range_iter
{
  T m_i;

  range_iter(T i): m_i(i)
  {
  }

  range_iter &
  operator++()
  {
    ++m_i;
    return *this;
  }

  T
  operator *() const
  {
    return m_i;
  }
  
  bool
  operator!=(const range_iter &i)
  {
    return m_i != *i;
  }
};

template <typename T>
struct range
{
  T m_a;
  T m_b;

  range(T a, T b): m_a(a), m_b(b)
  {
  }

  range_iter<T> begin()
  {
    return range_iter<T>(m_a);
  }

  range_iter<T> end()
  {
    return range_iter<T>(m_b);
  }
};
