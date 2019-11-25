#include <utility>

struct A
{
};
  
void swap(A &a, A &b)
{
  A tmp = std::move(a);
  a = std::move(b);
  b = std::move(tmp);
}

int
main()
{
  A x, y;
  swap(x, y);
}
