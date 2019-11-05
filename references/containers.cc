#include<vector>

int main()
{
  int x, y;

  // Kontenery mogą przechowywać wskaźniki.
  std::vector<int *> v = {&x, &y};
  // Ale referencji już nie.
  // std::vector<int &> v;

  // Tablice mogą przechowywać wskaźniki.
  int *a[] = {&x, &y};
  // Ale referencji już nie.
  // int &r[] = {x, y};
}
