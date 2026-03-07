#include <string>

std::string g()
{
  return "Hello World!";
}

std::string f()
{
  return g();
}

int main()
{
  std::string s = f();
}

