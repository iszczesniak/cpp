struct A {};
  
A foo()
{
  static A a;
  return a;
}
