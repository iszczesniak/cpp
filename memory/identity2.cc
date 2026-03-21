#include <string>

int main()
{
  // Default-constucted.
  std::string x;

  // Equivalent to the above.
  std::string y = {};

  std::string z = std::string("Hello!");
  // Expression string("Hello!") doesn't have identity.
  // &string("Hello!"); // Error!
}
