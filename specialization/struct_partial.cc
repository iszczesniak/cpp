#include <iostream>
#include <list>
#include <vector>

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

// A partial specialization for a container of integer elements.
template <template<typename> typename T>
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
  A<std::vector<double>>().foo();
  A<std::list<int>>().goo();

  // Ambiguous instantiation: the first or the second specialization?
  A<std::vector<int>>() a;
}
