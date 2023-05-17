#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

struct timer
{
  std::chrono::time_point<std::chrono::system_clock> t0;
  std::string m_message;

  // Tells whether we should print at the start.
  bool m_flag;
  
  timer(const std::string &message, bool flag = false):
    m_message(message), m_flag(flag)
  {
    if (m_flag)
      std::cout << "Starting: " << m_message << '\n';

    t0 = std::chrono::system_clock::now();
  }

  ~timer()
  {
    auto t1 = std::chrono::system_clock::now();
    double dt = static_cast<std::chrono::duration<double>>(t1 - t0).count();

    if (m_flag)
      std::cout << "Finished: ";

    std::cout << m_message << " in " << dt << " s\n";
  }
};

#endif
