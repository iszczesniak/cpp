#include <set>
#include <vector>

int
main()
{
  std::vector<int> vi = {1};
  std::set<int> s = {1};

  // We can initialize a non-const reference to a vector element,
  // because the dereference operator returns a non-const lvalue
  // reference to a vector element.
  int &a = *vi.begin();

  // We cannot initialize a non-const reference to a set element.
  // int &b = *s.begin();

  // The reference has to be const, because the dereference operator
  // returns a const lvalue reference to a set element.
  const int &c = *s.begin();

  // It's best to let the compiler figure out the right type.  As part
  // of the type deduction, e becomes a const reference.
  auto &d = *vi.begin();
  auto &e = *s.begin();

  std::vector<bool> vb = {true};
  // We cannot initialize an lvalue reference, because the
  // initializing expression is an rvalue: the dereference operator
  // returns a temporary proxy object that can convert to a bool.
  // auto &f = *vb.begin();

  // We have to use an rvalue reference.
  bool &&f = *vb.begin();

  // So it's best to use the forwarding reference:
  auto &&g = *vi.begin();
  auto &&h = *s.begin();
  auto &&i = *vb.begin();
}
