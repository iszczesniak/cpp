#include <concepts>
#include <iostream>

using namespace std;

enum sex:bool {male, female};

template <sex S, unsigned I> requires (I >= 18)
void
play()
{
  cout << "Toys for adults.\n";
}

template <sex S, unsigned I> requires (I < 18)
void
play()
{
  cout << "Toys for kids.\n";
}

template <sex S, unsigned I> requires (S == sex::male) && (I < 18)
void
play()
{
  cout << "Toys for boys.\n";
}

int
main()
{
  // play<sex::male, 10>();
  play<sex::female, 10>();
  play<sex::male, 20>();
  play<sex::female, 20>();
}
