#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

struct timer
{
  std::chrono::time_point<std::chrono::system_clock> t0;
  std::string m_message;

  timer(const std::string &message): m_message(message),
				     t0(std::chrono::system_clock::now())
  {
    std::cout << "Starting: " << m_message << '\n';
  }

  ~timer()
  {
    auto t1 = std::chrono::system_clock::now();
    double dt = static_cast<std::chrono::duration<double>>(t1 - t0).count();
    std::cout << "Finished: " << m_message << " in " << dt << " s\n";
  }
};

#endif
