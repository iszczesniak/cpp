#include <chrono>
#include <forward_list>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

using namespace std;

struct A
{
  string m_text;

  shared_ptr<A> sp;
  // weak_ptr<A> wp;

  A(const string &text): m_text(text)
  {
    cout << "ctor: " << m_text << endl;
  }

  ~A()
  {
    cout << "dtor:" << m_text << endl;
  }
};

int main (void)
{
  auto sp = make_shared<A>("A1");
  sp->sp = make_shared<A>("A2");
  sp->sp->sp = sp;
  // sp->sp->wp = sp;
}
