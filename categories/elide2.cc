#include <string>

std::string g()
{
  return "Hello World!";
}

std::string f(string p)
{
  return p;
}

int main()
{
  std::string s = f(g());
}
