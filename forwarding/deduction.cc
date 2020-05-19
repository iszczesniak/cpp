template <typename T>
class ER;

int
main()
{
  int x = 1;
  auto &&r1 = 1;
  auto &&r2 = x;

  ER<decltype(r1)> error1;
  ER<decltype(r2)> error2;
}
