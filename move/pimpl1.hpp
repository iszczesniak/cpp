// Sometimes we need the ownership functionalty for the
// dynamically-allocated data, so that:
//
// * the data is destroyed when the owner is destroyed: we do not have
//   to remember to delete the data,
//
// * the ownership can be passed when, e.g., returning by value in
//   cases when the constructor elision (or the return value
//   optimization in the past) could not be used.

// That functionality used to be called pointer to implementation
// (PIMPL), aka the bridge pattern.  It used to be implemented in
// std::auto_ptr that no longer is part of C++17.  It used to, because
// in C++11 it was replaced by the exclusive ownership semantics and
// std::unique_ptr.

// Here is a sample implementation without the move semantics, but
// with modern C++ functionalities, so this example only poses to be
// legacy.  We implement the functionality in the special copying
// member functions.

#ifndef PIMPL1
#define PIMPL1

#include <iostream>

using namespace std;

template <typename T>
struct pimpl1
{
  // The nullptr literal is C++11.
  pimpl1(): m_ptr(nullptr)
  {}

  pimpl1(T *ptr): m_ptr(ptr)
  {
  }

  pimpl1(const pimpl1 &src): m_ptr(src.m_ptr)
  {
    src.m_ptr = nullptr;
  }

  // C++14: returning by reference with the auto type specifier.
  auto &operator=(const pimpl1 &src) const
  {
    m_ptr = src.m_ptr;
    src.m_ptr = nullptr;
    return *this;
  }

  ~pimpl1()
  {
    delete m_ptr;
  }
    
  mutable T *m_ptr;
};

#endif // PIMPL1
