template <typename T>
T
abs(T &t)
{
  return t >= 0 ? t : -t;
}

int
main()
{
  volatile const int i = 1;
  volatile auto c = abs(i);
}
