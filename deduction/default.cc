#include <iostream>
#include <>

using namespace std;

template <template<typename> typename C = ,
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
  
}
