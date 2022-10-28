struct A
{
  int m_t[3];

  int
  operator[](unsigned i)
  {
    return m_t[i];
  }
};

int main()
{
  A a1;
  // The built-in assignment operator for integers expects an lvalue
  // on the left-hand size.  However, the overloaded operator[]
  // function returns a non-reference type, and so its call expression
  // is an rvalue.  That's why the following equivalent lines of code
  // do not compile.
  // a1[0] = 1;
  // a1.operator[](0) = 1;
}
