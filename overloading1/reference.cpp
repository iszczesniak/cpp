void foo(const int &);
void foo(int &&);

int main()
{
  foo(1);
}
