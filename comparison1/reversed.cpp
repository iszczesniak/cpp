struct A
{
  bool operator == (const A &) const & = default;
};

struct B: A
{
  // bool operator == (const B &b) const
  // {
  //   return static_cast<const A &>(*this) == static_cast<const A &>(b);
  // }
};

bool operator == (const A&, const B &);

int main()
{
  B b;
  b == b;
}
