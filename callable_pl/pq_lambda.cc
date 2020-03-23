#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int
main(void)
{
  priority_queue<int, vector<int>,
                 function<bool(const int &, const int &)>>
    q([](const int &a, const int &b)
      {return a > b;});

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
