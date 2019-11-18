struct A {};

A foo(bool flag)
{
  A a1, a2;
  return flag ? a1 : a2;
}
