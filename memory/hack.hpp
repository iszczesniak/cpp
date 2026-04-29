#include <iostream>
#include <string>

struct A
{
  std::string m_name;

  A(const std::string &name): m_name(name)
  {
    std::cout << "ctor: " << m_name << std::endl;
  }

  A(const A &a): m_name(a.m_name + " copied")
  {
    std::cout << "copy-ctor: " << m_name << std::endl;
  }

  A(A &&a): m_name(a.m_name + " moved")
  {
    std::cout << "move-ctor: " << m_name << std::endl;
  }

  ~A()
  {
    std::cout << "dtor: " << m_name << std::endl;
  }
};
