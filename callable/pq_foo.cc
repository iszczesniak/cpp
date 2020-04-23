#include <functional>
#include <iostream>
#include <queue>

using namespace std;

bool
foo(const int &a, const int &b)
{
  return a < b;
}

int
main(void)
{
  priority_queue<int, vector<int>,
                 bool(*)(const int &, const int &)> q(foo);

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
