#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int
main(void)
{
  // HERE'S THE DIFFERENCE!
  priority_queue<int, vector<int>, greater<int>> q;

  // I was hoping the third template argument would be deduced from
  // the constructor argument, but, alas, no.
  // priority_queue<int> q(std::greater<int>{});
  
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
