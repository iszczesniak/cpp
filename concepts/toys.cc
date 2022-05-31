#include <iostream>

using namespace std;

enum sex:bool {male, female};

template<unsigned I>
concept adult = I >= 18;

template<unsigned I>
concept kid = !adult<I>;

template<sex S>
concept is_male = S == sex::male;

template <sex S, unsigned I> requires adult<I>
void
play()
{
  cout << "Toys for adults.\n";
}

template <sex S, unsigned I> requires kid<I>
void
play()
{
  cout << "Toys for kids.\n";
}

template <sex S, unsigned I> requires kid<I> && is_male<S>
void
play()
{
  cout << "Toys for boys.\n";
}

int
main()
{
  play<sex::male, 10>();
  play<sex::female, 10>();
  play<sex::male, 20>();
  play<sex::female, 20>();
}
