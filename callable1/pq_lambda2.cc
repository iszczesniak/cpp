#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int
main(void)
{
  bool order;

  cout << "Enter 0 or 1: ";
  cin >> order;
  
  auto c = [order](const int &a, const int &b)
           {return order ? a < b : a > b;};

  priority_queue<int, vector<int>, decltype(c)> q(c);

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
