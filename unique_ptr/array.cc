#include <array>
#include <memory>

using namespace std;

int
main()
{
  unique_ptr<array<int, 5>> up(new array<int, 5>);
  auto up = make_unique<array<int, 5>>();
}
