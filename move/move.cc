#include <cassert>
#include <iostream>
#include <deque>

using namespace std;

struct A
{
  string m_text;

  A(const string &text): m_text(text)
  {
    cout << "ctor: " << m_text << endl;
  }

  A(const A &a): m_text(a.m_text)
  {
    cout << "copy ctor: " << m_text << endl;
  }

  A(A &&a): m_text(move(a.m_text))
  {
    a.m_text.clear();
    cout << "move ctor: " << m_text << endl;
  }
  
  ~A()
  {
    cout << "dtor: " << m_text << endl;
  }

  A &operator = (const A &a)
  {
    m_text = a.m_text;
    cout << "copy-assignment: " << m_text << endl;    
  }

  A &operator = (A &&a)
  {
    m_text = move(a.m_text);
    cout << "move-assignment: " << m_text << endl;    
  }
};

A
foo()
{
  A a("TEST");
  return a;
}

int
main(void)
{
  A a1("A1"), a2("A2");
  a2 = move(a1);

  return 0;
}
