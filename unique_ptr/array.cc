#include <array>
#include <memory>

using namespace std;

int
main()
{
  unique_ptr<array<int, 5>> up1(new array<int, 5>);
  auto up2 = make_unique<array<int, 5>>();
}
