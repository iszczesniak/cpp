#include <iostream>

using namespace std;

template <typename T>
void f(T)
{
  cout << "f(T)\n";
}

template <typename T>
void f(T *)
{
  cout << "f(T *)\n";
}

// This one is wrong!
//
// template <>
// void f<int *>(int *)
// {
//   cout << "f<int *>(T *)\n";
// }

// This one is fine!  But f<int>(int *) can be shrunk to f<>(int *),
// because T can be deducted to be T = int.
//
// template <>
// void f<int>(int *)
// {
//   cout << "f<int *>(T *)\n";
// }

// This one if fine too, but "f<>" can be shrunk to "f", because we
// already know it's a specialization.
//
// template <>
// void f<>(int *)
// {
//   cout << "f<int *>(T *)\n";
// }

template <>
void f(int *)
{
  cout << "f<int *>(T *)\n";
}

int
main()
{
  int *i;
  f(i);
}
