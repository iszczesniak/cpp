#include <chrono>
#include <forward_list>
#include <future>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

using namespace std;

struct A: public enable_shared_from_this<A>
{
  string m_text;

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
  {
    auto sp1 = make_shared<A>("A1");
    auto sp2 = sp1->shared_from_this();
    cout << "count = " << sp2.use_count() << endl;
  }

  {
    A *ap = new A("A1");
    auto sp1 = shared_ptr<A>(ap);
    auto sp2 = ap->shared_from_this();
    cout << "count = " << sp2.use_count() << endl;
  }
}
