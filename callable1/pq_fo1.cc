#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct CMP
{
  bool
  operator()(const int &a, const int &b)
  {
    return a > b;
  }
};

int
main(void)
{
  // An object of CMP will be default-constructed by q.
  priority_queue<int, vector<int>, CMP> q;

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
