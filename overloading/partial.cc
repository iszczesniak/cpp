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
  // Step 1: template #1 is transformed into this function type:
  //
  // void (U, U) // function type #1

  // We got U, because [temp.func.order] says "for each (...)
  // parameter (...) synthesize a unique type".  Template 1 has one
  // parameter T only for which we make up ("synthesize") type U.
  //
  // The above type is the function type transformed from the argument
  // template.
  //
  // Template #2 is called the parameter template, because for that
  // template we try to deduce the arguments based on the template #1.
  // Template #1 is called the argument template, because it's given,
  // and doesn't change.  Specifically, the deduction takes into
  // account as the argument the function type #1.
  //
  // Deduced arguments for template #2: T1 = U1, T2 = U2.  Success.

  // Step 2: template #2 is transformed into this function type:
  //
  // void (U1, U2)
  //
  // We got unique types U1, and U2, because [temp.func.order] says
  // "for each (...) parameter (...) synthesize a unique type".
  // Template 2 has two parameters T1 and T2 for which we make up
  // types U1 and U2.
  //
  // We cannot deduce arguments for template #1, because T cannot be
  // both U1, and U2.  Failure.

  // Conclusion
  // ----------
  //
  // Template #1 is used, because it is more specialized than template
  // #2: calls to #1 are a subset of calls to #2, i.e., whenever
  // template #1 can be used, template #2 can be used.  We can say
  // that template #1 implies template #2: if template #1 can be used,
  // then template #2 could be used too, but not the other way around.
  
  foo(1, 1);
}
