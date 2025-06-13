#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

using e_type = std::shared_ptr<std::string>;

struct cmp
{
  bool operator()(const e_type &a, const e_type &b)
  {
    return *a < *b;
  }
};

int main()
{
  std::priority_queue<e_type, std::vector<e_type>, cmp> pq{cmp()};

  pq.push(std::make_shared<std::string>("Alice"));
  pq.push(std::make_shared<std::string>("Bob"));
  std::cout << *pq.top() << std::endl;
  pq.pop();
  std::cout << *pq.top() << std::endl;
  pq.pop();    
}
