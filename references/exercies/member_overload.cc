#include <iostream>

using namespace std;

// The solution.
struct A
{
  string m_txt;

  A(const string &txt): m_txt(txt)
  {
  }

  A &operator++() &
  {
    m_txt += "l";
    return *this;
  }

  A &&operator++() &&
  {
    m_txt += "r";
    return std::move(*this);
  }
};

// An example.
ostream &operator<<(ostream &os, const A &a)
{
  os << a.m_txt << endl;
  return os;
}

int main()
{
  A l("Hello: ");
  cout << ++++l;
  cout << ++++A("World: ");
}
