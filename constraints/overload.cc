#include <iostream>

template <unsigned I>
void play()
{
  std::cout << "Play.\n";
}

template <unsigned I> requires (I >= 18)
void play()
{
  std::cout << "Play >18.\n";
}

int
main()
{
  play<10>();
  play<20>();
}
