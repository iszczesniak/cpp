// When we implement the PIMPL (pointer to implementation) idiom with
// the move semantics, we get the exclusive ownership semantics done
// right.  Now std::unique_ptr offers this functionality.

#ifndef PIMPL2
#define PIMPL2

// Differs from pimpl1 only by two details.  Find them.
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
