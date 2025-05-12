struct A
{
  bool operator == (const A &) const = default;
};

struct B: A
{
  using A::operator ==;
};

int main()
{
  B() == B();
}
