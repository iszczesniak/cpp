template <unsigned I, typename T>
T
power(T t)
{
  if constexpr (I)
    return t * power<I - 1>(t); 

  return 1;
}

int
main()
{
  
}
