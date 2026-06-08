template <typename T>
void primary(void (const T &));

void spec1(bool);

void spec2(int &);

int main()
{
  // primary(spec1);
  // primary(spec2);
}
