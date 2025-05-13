#include <cassert>
#include <iostream>

using namespace std;

struct A
{
  A()
  {
    cout << "ctor\n";
  }

  ~A()
  {
    cout << "dtor\n";
  }
};

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
};

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
      cout << "control-ctor\n";
    }

    ~control()
    {
      cout << "control-dtor\n";
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

  my_shared_ptr(my_unique_ptr<A> &&a): my_shared_ptr(a.m_ptr)
  {
    a.m_ptr = nullptr;
  }

  my_shared_ptr(const my_shared_ptr &a):
    m_ctrl_ptr(a.m_ctrl_ptr), m_data_ptr(a.m_data_ptr)
  {
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
    
  my_weak_ptr(const my_shared_ptr<A> &a):
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

int
main()
{
  my_unique_ptr<A> up(new A);
  // my_unique_ptr<A> up2 = up;
  my_unique_ptr<A> up2 = move(up);

  my_unique_ptr<A> up3;
  // up3 = up2;
  up3 = std::move(up2);

  my_shared_ptr<A> sp = move(up3);

  {
    my_shared_ptr<A> sp2 = sp;
    my_shared_ptr<A> sp3;
    sp3 = sp2;

    my_shared_ptr<A> sp4 = move(sp);
    sp3 = move(sp2);

    my_weak_ptr<A> wp = sp3;
    my_weak_ptr<A> wp2 = wp;
    my_weak_ptr<A> wp3(move(wp));
    my_weak_ptr<A> wp4;
    wp4 = wp2;

    my_shared_ptr<A> sp5 = wp4;
  }

  std::cout << "Bye!\n";
}
