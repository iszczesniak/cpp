#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int
main(void)
{
  auto f = [](const int &a, const int &b){return a > b;};

  priority_queue<int, vector<int>, decltype(f)> q(f);

  q.push(2);
  q.push(1);
  q.push(3);

  while(!q.empty())
    {
      cout << q.top() << endl;
      q.pop();
    }
  
  return 0;
}
