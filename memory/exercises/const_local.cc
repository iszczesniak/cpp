int main()
{
  const int i = 1;
  *const_cast<int *>(&i) = 10;
}
