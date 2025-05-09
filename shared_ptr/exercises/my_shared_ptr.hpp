#ifndef MY_SHARED_PTR
#define MY_SHARED_PTR

#include "my_unique_ptr.hpp"

#include <iostream>

template <typename T>
class my_shared_ptr
{
  struct control
  {
    unsigned count = 1;

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
  decrement()
  {
    if (m_ctrl_ptr != nullptr)
      {
        --m_ctrl_ptr->count;
        if (m_ctrl_ptr->count == 0)
          {
            delete m_data_ptr;
            delete m_ctrl_ptr;
          }
      }
  }

public:
  my_shared_ptr()
  {
  }

  my_shared_ptr(T *ptr): m_ctrl_ptr(new control), m_data_ptr(ptr)
  {
  }

  ~my_shared_ptr()
  {
    decrement();
  }

  my_shared_ptr(my_unique_ptr<T> &&a): my_shared_ptr(a.m_ptr)
  {
    a.m_ptr = nullptr;
  }

  my_shared_ptr(const my_shared_ptr &a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    if (m_ctrl_ptr)
      ++m_ctrl_ptr->count;
  }

  my_shared_ptr(my_shared_ptr &&a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
    a.m_ctrl_ptr = nullptr;
  }

  my_shared_ptr &
  operator = (const my_shared_ptr &a)
  {
    decrement();

    m_data_ptr = a.m_data_ptr;
    m_ctrl_ptr = a.m_ctrl_ptr;

    if (m_ctrl_ptr)
      ++m_ctrl_ptr->count;

    return *this;
  }

  my_shared_ptr &
  operator = (my_shared_ptr &&a)
  {
    decrement();

    m_data_ptr = a.m_data_ptr;
    m_ctrl_ptr = a.m_ctrl_ptr;
    a.m_ctrl_ptr = nullptr;

    return *this;
  }

  // The dereference operator.
  T &
  operator * () const
  {
    return *m_data_ptr;
  }

  T *
  operator -> () const
  {
    return m_data_ptr;
  }

  operator bool()
  {
    return m_ctrl_ptr != nullptr;
  }
};

#endif // MY_SHARED_PTR
