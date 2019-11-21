#include <utility>

struct A
{
  A() = default;

  // Konstruktor kopiujący.
  A(const A &) = delete;

  // Kopiujący operator przypisania.
  A &
  operator =(const A &) = delete;
};

int
main()
{
  A a;
  // A b(a);
  A b(std::move(a));
}
