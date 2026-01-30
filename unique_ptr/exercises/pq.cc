#include <memory>
#include <queue>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  auto c = [](const unique_ptr<string> &a,
              const unique_ptr<string> &b)
  {
    return *a > *b;
  };
  
  std::priority_queue<unique_ptr<string>,
                      vector<unique_ptr<string>>,
                      decltype(c)> q(c);

  q.push(make_unique<string>("World"));
  q.push(make_unique<string>("Hello"));

  cout << *q.top() << endl;
  q.pop();
  cout << *q.top() << endl;
}
