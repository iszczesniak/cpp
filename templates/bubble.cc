#include <iostream>

using namespace std;

template <typename I, typename F>
void bubble(I i1, I i2, F f)
{

}

int
main()
{
  int t[] = {1, 5, 3, 2};
  bubble(begin(t), end(t), less<int>{});
}
