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

  A(const string &text): m_text(text)
  {
    cout << "ctor: " << m_text << endl;
  }

  ~A()
  {
    cout << "dtor:" << m_text << endl;
  }

  void print() const
  {
    cout << "print: " << m_text << endl;
  }
};

void
foo(shared_ptr<A> sp)
{
  std::this_thread::sleep_for(chrono::seconds(1));
  sp->print();
}

int main (void)
{
  forward_list<future<void>> fl;

  {
    auto sp = make_shared<A>("A1");

    for(int i = 0; i < 10; ++i)
      fl.push_front(async(launch::async, foo, sp));
  }

  cout << "TEST" << endl;

  this_thread::sleep_for(chrono::seconds(2));

  cout << "TEST2" << endl;
}
