#include <cassert>
#include <iostream>
#include <memory>
#include <deque>

struct A
{
  std::string m_text;

  A(const std::string &text): m_text(text)
  {
    std::cout << "Constructor: " << m_text << std::endl;
  }

  A(const A &&a)
  {
    std::cout << "Moving: " << m_text << std::endl;
  }

  ~A()
  {
    std::cout << "Destructor: " << m_text << std::endl;
  }

  void
  print()
  {
    std::cout << "Print: " << m_text << std::endl;
  }
};

std::unique_ptr <A>
foo()
{
  std::unique_ptr <A> a(new A("test"));

  // Jesteśmy bezpieczni na wypadek wyjątku.
  throw true;
  
  return a;
}

int
main(void)
{
  std::unique_ptr<A> p1(new A("A1"));

  auto up = std::make_unique<A>("A1");

  // Tu idą różne testy, jak w lab3.txt.
  
  return 0;
}
