#include <iostream>

struct A
{
  A()
  {
    std::cout << "A ctor\n";
  }

  void foo()
  {
    std::cout << "A foo\n";
  }
  
  ~A()
  {
    std::cout << "A dtor\n";
  }
};

struct simple
{
  A *m_ptr;
  int *m_count;

  simple(A *ptr): m_ptr(ptr), m_count(new int(1))
  {
  }

  simple(const simple &a): m_ptr(a.m_ptr), m_count(a.m_count)
  {
    ++*m_count;
  }

  A *operator -> () const
  {
    return m_ptr;
  }
  
  ~simple()
  {
    if (!--*m_count)
      {
	delete m_count;
	delete m_ptr;
      }
  }
};

int main()
{
  simple p(new A());
  {
    simple p2 = p;
    p2->foo();
  }  
}
