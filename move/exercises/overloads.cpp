struct A
{
  // 1. Left operand: lvalue, right operand: lvalue or rvalue.
  A & operator = (const A &) &;
  // 2. Left operand: lvalue, right operand: rvalue.
  A & operator = (A &&) &;
  // 3. Left operand: rvalue, right operand: lvalue or rvalue.
  A & operator = (const A &) &&;
  // 4. Left operand: rvalue, right operand: rvalue.
  A & operator = (A &&) &&;

  // If we don't add a reference qualifier to a function (the trailing
  // & or &&), than the function can be called for any category of the
  // object we assign to, but this version doesn't overload with the
  // reference-qualifies versions above.

  // Functions cannot be const-qualified (the trailing const), because
  // then we would be unable to modify the object we assign to.

  // In the examples above, the right operand doesn't have to be of
  // type A, but of any type, e.g.:

  // 5. Left operand: rvalue, right operand: rvalue.
  A & operator = (int &&) &&;
};

int main()
{
  A a1;
  a1 = a1; // #1
  a1 = A(); // #2
  A() = a1; // #3
  A() = A(); // #4
  A() = 5; // #5
}
