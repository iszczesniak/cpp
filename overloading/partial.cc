#include <iostream>

// Template #1
template <typename T>
void foo(T t1, T t2)
{
  std::cout << "Template with one parameter.\n";
}

// Template #2
template <typename T1, typename T2>
void foo(T1 t1, T2 t2)
{
  std::cout << "Template with two parameters.\n";
}

int main()
{
  // Template #1 is transformed into this function type:
  //
  // void foo(F, F)

  // To get F, [temp.func.order] says "synthesize a unique type"
  // without further explanation.  I guess that:
  //
  // * "to synthesize" implies taking into account the function call,
  //
  // * "unique" means that F is no longer a template parameter.
  //
  // For the following function call, I guess the first template is
  // intransformed into this function type:
  //
  // void foo(int, int) // Function type #1
  //
  // The above type is the function type transformed from the argument
  // template.
  //
  // Template #2 is called the parameter template, because for that
  // template we try to deduce the arguments based on the function
  // type #1:
  //
  // For template #2, T1 = int, T2 = int.  Success.

  foo(1, 1);
}
