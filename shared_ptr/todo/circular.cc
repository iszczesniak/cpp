#include <memory>

using namespace std;

struct B;

struct A
{
  shared_ptr<B> b;
};

struct B
{
  shared_ptr<A> a;
};

int main()
{
  auto sp_a = make_shared<A>();
  auto sp_b = make_shared<B>();
  sp_a->b = sp_b;
  sp_b->a = sp_a;
}
