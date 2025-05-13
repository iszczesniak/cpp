#ifndef MY_WEAK_PTR
#define MY_WEAK_PTR

#include "my_unique_ptr.hpp"

#include <cassert>
#include <iostream>

template <typename T>
class my_weak_ptr;

template <typename T>
class my_shared_ptr
{
  friend my_weak_ptr<T>;

  struct control
  {
    unsigned ref_count = 1;
    unsigned weak_count = 0;

    control()
    {
      std::cout << "control-ctor\n";
    }

    ~control()
    {
      std::cout << "control-dtor\n";
    }
  };

  control *m_ctrl_ptr = nullptr;
  T *m_data_ptr;

  void
  clean()
  {
    if (m_ctrl_ptr != nullptr && --m_ctrl_ptr->ref_count == 0)
      {
        delete m_data_ptr;

        if (m_ctrl_ptr->weak_count == 0)
          delete m_ctrl_ptr;
      }
  }

public:
  my_shared_ptr()
  {
  }

  // This might not be exception-safe, because "new" can throw.
  my_shared_ptr(T *ptr): m_ctrl_ptr(new control), m_data_ptr(ptr)
  {
  }

  // Here I can only declare this constructor.  The implementation has
  // to come after the definition of my_weak_ptr.
  my_shared_ptr(const my_weak_ptr<T> &);

  ~my_shared_ptr()
  {
    clean();
  }

  my_shared_ptr(my_unique_ptr<T> &&a): my_shared_ptr(a.m_ptr)
  {
    a.m_ptr = nullptr;
  }

  my_shared_ptr(const my_shared_ptr &a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    if (m_ctrl_ptr)
      ++m_ctrl_ptr->ref_count;
  }

  my_shared_ptr(my_shared_ptr &&a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    a.m_ctrl_ptr = nullptr;
  }

  my_shared_ptr &
  operator = (const my_shared_ptr &a)
  {
    clean();
        
    m_data_ptr = a.m_data_ptr;
    m_ctrl_ptr = a.m_ctrl_ptr;
    if (m_ctrl_ptr)
      ++m_ctrl_ptr->ref_count;

    return *this;
  }

  my_shared_ptr &
  operator = (my_shared_ptr &&a)
  {
    clean();
        
    m_data_ptr = a.m_data_ptr;
    m_ctrl_ptr = a.m_ctrl_ptr;
    a.m_ctrl_ptr = nullptr;

    return *this;
  }
};

template <typename T>
class my_weak_ptr
{
  friend my_shared_ptr<T>;

  typename my_shared_ptr<T>::control *m_ctrl_ptr = nullptr;
  T *m_data_ptr;

  void
  clean()
  {
    if (m_ctrl_ptr != nullptr &&
        --m_ctrl_ptr->weak_count == 0 &&
        m_ctrl_ptr->ref_count == 0)
      delete m_ctrl_ptr;        
  }

public:
  my_weak_ptr()
  {
  }

  ~my_weak_ptr()
  {
    clean();        
  }
    
  my_weak_ptr(const my_shared_ptr<T> &a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    ++m_ctrl_ptr->weak_count;
  }

  my_weak_ptr(const my_weak_ptr &a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    ++m_ctrl_ptr->weak_count;
  }

  my_weak_ptr(my_weak_ptr &&a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    a.m_ctrl_ptr = nullptr;
  }

  my_weak_ptr &
  operator = (const my_weak_ptr &a)
  {
    clean();

    m_ctrl_ptr = a.m_ctrl_ptr;
    m_data_ptr = a.m_data_ptr;
    if (m_ctrl_ptr)
      ++m_ctrl_ptr->weak_count;

    return *this;
  }

  my_weak_ptr &
  operator = (my_weak_ptr &&a)
  {
    clean();

    m_ctrl_ptr = a.m_ctrl_ptr;
    m_data_ptr = a.m_data_ptr;
    a.m_ctrl_ptr = nullptr;

    return *this;
  }
};

template <typename T>
my_shared_ptr<T>::my_shared_ptr(const my_weak_ptr<T> &a):
  m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
{
  assert(m_ctrl_ptr);
  assert(m_ctrl_ptr->ref_count != 0);
  ++m_ctrl_ptr->ref_count;
}

#endif // MY_WEAK_PTR
