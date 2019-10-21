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
  A a("a, function scope");
  A b("b, function scope");

  // Block scope.
  {
    A a("a, block scope");
    A b("b, block scope");
  }
  
  cout << "Bye!" << endl;
}
