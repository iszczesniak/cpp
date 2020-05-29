#include <iostream>

enum sex:bool {male, female};

template <unsigned I, sex S> requires (I < 18)
void play()
{
  std::cout << "<18\n";
}

template <unsigned I, sex S> requires (I < 18) && (S == sex::male)
void play()
{
  std::cout << "toys for boys\n";
}

template <unsigned I, sex S> requires (I >= 18)
void play()
{
  std::cout << ">18\n";
}

int
main()
{
  play<10, sex::male>();
  play<10, sex::female>();
  play<20, sex::male>();
  play<20, sex::female>();
}
