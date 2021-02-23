#include <cassert>
#include <iostream>

int main()
{
  for(unsigned x = 1; true; ++x)
    {
      // Allocate 1 GiB.
      std::byte *p = new std::byte [1024 * 1024 * 1024];
      assert(p);
      std::cout << "Allocated " << x << "GiBs." << std::endl;
    }
}
