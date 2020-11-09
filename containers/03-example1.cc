#include <iostream>
#include <vector>

int main()
{
  std::vector<int> a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);  
  for(std::vector<int>::iterator i = a.begin();
      i != a.end(); ++i)
    std::cout << *i << std::endl;
}
