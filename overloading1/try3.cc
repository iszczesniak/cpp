void foo(long double)
{
}

int main()
{
  // Conversion sequence:
  // - first promotion: float -> double,
  // - then conversion: double -> long double.
  foo(.0f);
}
