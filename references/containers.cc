#include <vector>

int main()
{
  int x, y;

  // Containers can store pointers.
  std::vector<int *> v = {&x, &y};
  // But not references.
  // std::vector<int &> v;

  // Array can store pointers.
  int *a[] = {&x, &y};
  // But not references.
  // int &r[] = {x, y};
}
