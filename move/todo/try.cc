#include<utility>

struct A
{
  A() = default;
  A(const A &) = default;
  A(A &&) = delete;
};

struct B: A
{
};

int main()
{
  B x;
  B y(std::move(x));
}
