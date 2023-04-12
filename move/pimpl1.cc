// Sometimes we need the ownership functionalty for the
// dynamically-allocated data, so that:
//
// * the data is destroyed when the owner is destroyed: we do not have
//   to remember to delete the data,
//
// * the ownership can be passed when, e.g., returning by value in
//   cases when the return value optimization could not be used.

// That functionality is called pointer to implementation (PIMPL), aka
// the bridge pattern.  It used to be implemented in std::auto_ptr
// that is no longer part of C++17.

// Here is a sample implementation without the move semantics, but
// with the nullptr of C++11.  We implement the functionality in the
// special copying member functions.

#include <iostream>

template <typename T>
struct auto_ptr
{
  auto_ptr(): m_ptr(nullptr)
  {}

  auto_ptr(T *ptr): m_ptr(ptr)
  {
  }

  auto_ptr(const auto_ptr &src): m_ptr(src.m_ptr)
  {
    src.m_ptr = nullptr;
  }

  auto_ptr &
  operator=(const auto_ptr &src)
  {
    m_ptr = src.m_ptr;
    m_ptr = nullptr;
  }

  ~auto_ptr()
  {
    delete m_ptr;
  }
    
  mutable T *m_ptr;
};

struct A
{
  int m_id;

  A(int id): m_id(id)
  {
    std::cout << "ctor: " << m_id << '\n';
  }

  ~A()
  {
    std::cout << "dtor: " << m_id << '\n';
  }
};

// C++14.
auto foo(bool flag)
{
  // Requires C++17.
  auto_ptr a(new A(1));
  auto_ptr b(new A(2));

  return flag ? a : b;
}

int
main()
{
  volatile bool flag = true;
  auto ptr = foo(flag);
}
