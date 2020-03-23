#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int
main(void)
{
  // HERE'S THE DIFFERENCE!
  priority_queue<int, vector<int>, greater<int>> q;

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
