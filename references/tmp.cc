#include <iostream>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A(const string &name): m_name(name)
  {
    cout << "ctor: " << m_name << endl;
  }

  ~A()
  {
    cout << "dtor: " << m_name << endl;
  }
};

int main()
{
  A a = A("a");

  {
    const A &r1 = a;
  }

  {
    const A &r2 = A("r2");

    {
      const A &R2 = r2;
    }

    cout << "Just checking." << endl;
  }

  {
    A &&r3 = A("r3");
  }
}
