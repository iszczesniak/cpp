#include <deque>
#include <iostream>
#include <vector>

using namespace std;

template <template <typename> typename C = std::vector,
          typename T = int, unsigned I = 10>
C<T>
container_factory()
{
  cout << __PRETTY_FUNCTION__ << endl;
  return C<T>(I);
}

int
main()
{
  container_factory();
  container_factory<std::deque>();
  container_factory<std::vector, double>();
  container_factory<std::deque, bool, 1>();
}
