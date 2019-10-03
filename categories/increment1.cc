int main()
{
  int x = 1;
  ++x; // The prefix version of the increment operator.
  x++; // The suffix version of the increment operator.
  // ++1; // Error: lvalue needed, no rvalue to lvalue conversion.
  // 1++; // Error: lvalue needed, no rvalue to lvalue conversion.
}
