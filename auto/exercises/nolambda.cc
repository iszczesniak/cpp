#include <iostream>

struct
{
  void operator()(const auto &t)
  {
    std::cout << t << std::endl;
  }
} f;

int main()
{
  f(std::string("Hello"));
  f("World");
  f('!');

  auto c = [](const auto &t){std::cout << t << std::endl;};
  
  c(std::string("Hello"));
  c("World");
  c('!');
}
