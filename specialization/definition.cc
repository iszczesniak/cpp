#include <iostream>

using namespace std;

// The primary template.
template <class T>
struct A
{
  void foo()
  {
    cout << __PRETTY_FUNCTION__ << endl;
  }
};

// Specialization of the member function of the primary template.
// Everything in A stays the same except our specialization.

template<>
void A<char>::foo()
{
  cout << "specialization: " << __PRETTY_FUNCTION__ << endl;
}

// The above specialization of a member function trigers the
// instantiation of the primary template for T = char, so we cannot
// now specialize the primary template for T = char.

// If we want to specialize the primary template as given below, we
// should comment out the specialization above.

// Specialization of the primary template for T = char.
// template <>
// struct A<char>
// {
//   void foo();
// };

// This is the definition of a member function, not a template
// specialization, so we cannot use 'template <>'.
// void A<char>::foo()
// {
//   cout << "definition: " << __PRETTY_FUNCTION__ << endl;
// }

int main()
{
  A<int>().foo();
  A<char>().foo();
}
