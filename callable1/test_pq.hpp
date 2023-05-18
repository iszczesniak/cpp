#ifndef TEST_PQ_HPP
#define TEST_PQ_HPP

#include "student.hpp"
#include "timer.hpp"

#include <algorithm>
#include <random>
#include <queue>

template <typename Q>
void
doit(Q &&q)
{
  timer t("together");

  const auto N = 10000000;
  
  {
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> distr;

    timer t("pushing");
    std::string name = "abcdefghijklmnop";

    for(auto i = N; --i;)
      {
	int index = distr(gen);
	int year = index % 5 + 1;

	q.push(student{index, year, name});

	std::next_permutation(name.begin(), name.end());
      }
  }

  {
    timer t("popping");
    while(!q.empty())
      q.pop();
  }
}

#endif // TEST_PQ_HPP
