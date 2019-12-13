#include <cassert>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct A
{
  string m_name;

  A()
  {
    cout << "default ctor\n";
  }

  A(string &&name): m_name(move(name))
  {
    cout << "ctor: " << m_name << endl;
  }

  ~A()
  {
    cout << "dtor: " << m_name << endl;
  }

  // Smart pointers never copy or move their managed data, so we can
  // delete these special member functions, and the code should
  // compile.
  A(const A &) = delete;
  A(A &&) = delete;
  A &operator=(const A &) = delete;
  A &operator=(A &&) = delete;
};

int
main()
{
  // That's an empty pointer.
  std::unique_ptr<A> p1;

  // That's how we test whether a pointer manages some data.
  assert(!p1);
  assert(p1 == nullptr);

  // This pointer manages an object.
  std::unique_ptr<A> p2(new A("A1"));
  assert(p2);
  assert(p2 != nullptr);

  // We can assign an new object to manage, but not this way.
  // p1 = new A("A1'");

  // That's the correct way.  The previously managed object is
  // destroyed.
  p2.reset(new A("A2"));

  // Or better yet:
  p2 = make_unique<A>("A3");

  // We cannot copy-initialize, because the ownership is exclusive.
  // std::unique_ptr<A> p3(p2);

  // We cannot copy-assign, because the ownership is exclusive.
  // p2 = p1;

  // We can move-initialize to move the ownership.
  auto p3 = move(p2);

  // We can move-assign to move the ownership.
  p2 = move(p3);

  // That's how we can get access to the managed data.
  cout << p2->m_name << endl;
  cout << (*p2).m_name() << endl;
  cout << p1.get()->m_name() << endl;

  // The "release" function releases p1 from managing the data.  The
  // managed data is not destroyed.  Luckily, p1 doesn't manage
  // anything, so we don't get a memory leak.
  p1.release();
}
