#include <utility>

struct A {};

struct my_unique_ptr
{
  A *m_ptr;

  my_unique_ptr(A *ptr): m_ptr(ptr)
  {
  }

  my_unique_ptr(my_unique_ptr &&src): m_ptr(src.m_ptr)
  {
    src.m_ptr = nullptr;
  }

  my_unique_ptr &operator=(my_unique_ptr &&src)
  {    
    if (this != &src)
      {
        delete m_ptr;
        m_ptr = src.m_ptr;
        src.m_ptr = nullptr;
      }

    return *this;
  }

  A &operator*()
  {
    return *m_ptr;
  }
};

int main()
{
  my_unique_ptr p(new A());
  auto p2 = std::move(p);
  p2 = std::move(p2);
}
