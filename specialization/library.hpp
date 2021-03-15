// Declaration of a primary function template.
template <typename T>
void foo(const T &t);

// This function template uses the above declaration.  Without the
// declaration, this template wouldn't compile.
template <typename T>
void goo(const T &t)
{
  foo(t);
}
