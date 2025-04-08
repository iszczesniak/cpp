#include<utility>

struct A
{
  A() = default;
  A(const A &) = default;
  A(A &&) = delete;
};

struct B: A
{
  B() = default;
  B(const B &) = default;
  B(B &&) = default;
};

int main()
{
  B x;
  B y(std::move(x));
}
