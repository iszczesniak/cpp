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

  void goo()
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
// instantiation of the primary template for T = char, so now we
// cannot even declare the primary template for T = char, let alone
// specialize it.

// template <>
// struct A<char>;

// But we can still specialize the other function:

template<>
void A<char>::goo()
{
  cout << "specialization: " << __PRETTY_FUNCTION__ << endl;
}

// Specialization of the primary template for T = char along with the
// definition of the member function.

// template <>
// struct A<char>
// {
//   void foo()
//   {
//     cout << "definition: " << __PRETTY_FUNCTION__ << endl;
//   }
// };

// The implementation below is the same as the one right above.  Below
// we moved the definition of the foo function outside the class.

// template <>
// struct A<char>
// {
//   void foo();
// };

// void A<char>::foo()
// {
//   cout << "definition: " << __PRETTY_FUNCTION__ << endl;
// }

int main()
{
  A<int>().foo();
  A<char>().foo();

  A<int>().goo();
  A<char>().goo();
}
