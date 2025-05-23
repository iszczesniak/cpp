void foo(const int &); // #1
void foo(int &&); // #2

int main()
{
  // Calls #2, because initializing an rvalue reference with an rvalue
  // is better than initializing an lvalue reference
  // [over.ics.rank#3.2.3].
  foo(1);
}
