#include "A.hpp"

#pragma clang diagnostic ignored "-Wunused-value"

int main()
{
  static_cast<const A &>(A("World"));
}
