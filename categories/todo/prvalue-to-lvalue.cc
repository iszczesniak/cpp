#include "A.hpp"

int main()
{
  static_cast<const A &>(A("World"));
}
