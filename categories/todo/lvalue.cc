template <typename T>
struct ER;

int main()
{
  int *p;
  ER<decltype(*p)> er;
}
