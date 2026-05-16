#include <iostream>
#include <string>
#include <queue>
#include <tuple>

struct airplane
{
  int m_priority;
  std::string m_registration;
};

bool operator<(const airplane &a1, const airplane &a2)
{
  return std::tie(a1.m_priority, a1.m_registration) >
    std::tie(a2.m_priority, a2.m_registration);
}

int main()
{
  std::priority_queue<airplane> pq;

  pq.push({0, "XYZ"});
  pq.push({1, "ABC"});
  pq.push({0, "QRS"});

  while(!pq.empty())
    {
      std::cout << pq.top().m_priority << ", "
                << pq.top().m_registration << '\n';

      pq.pop();
    }
}
