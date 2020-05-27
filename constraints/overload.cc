#include <iostream>

template <unsigned I> requires (I < 18)
void play()
{
  std::cout << "<18\n";
}

template <unsigned I> requires (I >= 18)
void play()
{
  std::cout << ">18\n";
}

int
main()
{
  play<10>();
  play<20>();
}
