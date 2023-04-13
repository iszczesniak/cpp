#ifndef PIMPL2
#define PIMPL2

template <typename T>
struct pimpl2
{
  pimpl2(): m_ptr(nullptr)
  {}

  pimpl2(T *ptr): m_ptr(ptr)
  {
  }

  pimpl2(const pimpl2 &&src): m_ptr(src.m_ptr)
  {
    src.m_ptr = nullptr;
  }

  auto &operator=(const pimpl2 &&src) const
  {
    m_ptr = src.m_ptr;
    src.m_ptr = nullptr;
    return *this;
  }

  ~pimpl2()
  {
    delete m_ptr;
  }
    
  mutable T *m_ptr;
};

#endif // PIMPL2
