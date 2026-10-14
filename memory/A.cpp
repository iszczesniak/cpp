#include "A.hpp"
#include <iostream>

using namespace std;

A::A(const string &name): m_name(name)
{
  cout << "ctor: " << m_name << endl;
}

A::A(const A &a): m_name(a.m_name + " copied")
{
  cout << "copy-ctor: " << m_name << endl;
}

A::A(A &&a): m_name(a.m_name + " moved")
{
  cout << "move-ctor: " << m_name << endl;
}

void A::hello() const
{
  cout << "Hello from " << m_name << endl;
}

A::~A()
{
  cout << "dtor: " << m_name << endl;
}
