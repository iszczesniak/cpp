#include "heir.hpp"
#include "name.hpp"
#include "weight.hpp"

#include <iostream>

int
main()
{
  using type = hair<name<string>, weight<int>>;

  type joe{"Jonathan", 12};
  get_name(joe) += " I";
  get_weight(joe) += 50;
}
