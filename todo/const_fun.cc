int main()
{
  // A non-const function cannot be declated const, because it has no
  // object to work :

  // void goo() const;

  // But if so, then why does the following compile:
  using fun_type = void() const;

  // And the following doesn't:
  fun_type *p = hello;
}

