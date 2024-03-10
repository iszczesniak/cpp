#include <iostream>
#include <list>
#include <vector>
#include <tuple>

// Definition of a primary template.
template <typename T>
struct A;

// A partial specialization for a vector of elements of any type.
template <typename T>
struct A<std::vector<T>>
{
  void
  foo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }  
};

// A partial specialization for any template type of the integer
// argument.
template <template<typename...> typename T>
struct A<T<int>>
{
  void
  goo()
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }  
};

int
main()
{
  A<std::vector<bool>>().foo();
  A<std::vector<double>>().foo();
  A<std::list<int>>().goo();
  A<std::tuple<int>>().goo();

  // Ambiguous instantiation: the first or the second specialization?
  // A<std::vector<int>>() a;
}
