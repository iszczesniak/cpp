#include <iostream>

struct frame
{
  const char *m_txt;

  frame(const char *txt): m_txt(txt)
  {
    std::cout << "Entered: " << m_txt << '\n';
  }

  ~frame()
  {
    std::cout << "Leaving: " << m_txt << '\n';
  }
};
