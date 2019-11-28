auto // C++14
foo()
{
  std::unique_ptr <A> a(new A());

  // Jesteśmy bezpieczni na wypadek wyjątku.
  throw true; // To nie poezja programistyczna!

  return a;
}
