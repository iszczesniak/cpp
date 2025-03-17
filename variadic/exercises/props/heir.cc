#include "heir.hpp"
#include "name.hpp"
#include "weight.hpp"

#include <iostream>
#include <string>

using namespace std;

int
main()
{
  using type = heir<name<string>, weight<int>>;

  type joe{name<string>("Jonathan"), weight<int>(12)};
  get_name(joe) += " I";
  get_weight(joe) += 50;
}
