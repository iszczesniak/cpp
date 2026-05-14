#include <functional>
#include <iostream>

struct A
{
  void foo() &
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  void foo() &&
  {
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }
};

template <typename T>
void call(T)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

int
main()
{
  A a;
  a.foo();
  A().foo();

  // std::invoke(&A::foo, a);
  // std::invoke(&A::foo, A());

  // call(&A::foo);
  call<void(A::*)() &>(&A::foo);
  call<void(A::*)() &&>(&A::foo);

  void(A::*pl)() & = &A::foo;
  (a.*pl)();
  void(A::*pr)() && = &A::foo;
  (A().*pr)();

  std::invoke<void(A::*)() &>(&A::foo, a);
  std::invoke<void(A::*)() &&>(&A::foo, A());

  std::invoke(static_cast<void(A::*)() &>(&A::foo), a);
  std::invoke(static_cast<void(A::*)() &&>(&A::foo), A());
}
