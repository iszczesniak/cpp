#include <functional>
#include <iostream>
#include <queue>

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
  // priority_queue<int, vector<int>, CMP> q;

  // That's a function declaration!  Q takes a pointer of the type
  // "CMP (*)()", and returns a priority_queue object.
  priority_queue<int, vector<int>,
                 function<bool(const int &, const int &)>> Q(CMP());

  priority_queue<int, vector<int>,
                 function<bool(const int &, const int &)>> q(CMP{});

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
