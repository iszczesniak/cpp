#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

template <typename T>
struct my_unique_ptr
{
  T *m_ptr = nullptr;

  my_unique_ptr()
  {
  }

  my_unique_ptr(T *ptr): m_ptr(ptr)
  {
  }

  ~my_unique_ptr()
  {
    delete m_ptr;
  }

  my_unique_ptr(my_unique_ptr &&a): m_ptr(a.m_ptr)
  {
    a.m_ptr = nullptr;
  }

  my_unique_ptr &
  operator = (my_unique_ptr &&a)
  {
    delete m_ptr;
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr;
    return *this;
  }

  // The dereference operator.
  T &
  operator * () const
  {
    return *m_ptr;
  }

  T *
  operator -> () const
  {
    return m_ptr;
  }

  operator bool()
  {
    return m_ptr != nullptr;
  }
};

#endif // MY_UNIQUE_PTR
