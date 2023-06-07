// Exercise
//
// Read words from the input, and print in aphabetical order:
//
// * the words that have no palindromes,
//
// * the words that have 1 palindrome,
//
// * the words that have 2 palindromes,
//
// * and so forth.

#include "factory.hpp"
#include "timer.hpp"

#include <algorithm>
#include <map>
#include <iostream>
#include <set>
#include <string>

using namespace std;

struct palindromes
{
  string m_base;

  struct cmp
  {
    bool operator () (const shared_ptr<string> &sp1,
                      const shared_ptr<string> &sp2) const
    {
      return *sp1 < *sp2;
    }
  };

  set<shared_ptr<string>, cmp>  m_words;

  palindromes(const string &first): m_base(first)
  {
    // Create the base word.
    std::sort(m_base.begin(), m_base.end());
    // Insert the first word.
    m_words.insert(factory<string>(first));
  }

  void
  insert(const string &word)
  {
    m_words.insert(factory<string>(word));
  }

  bool exists(const string &word) const
  {
    return m_words.find(factory<string>(word)) != m_words.end();
  }
};

bool operator < (const palindromes &a, const palindromes &b)
{
  return a.m_base < b.m_base;
}

int
main()
{
  timer("Took");
  
  map<int, set<palindromes>> m;

  // Iterate over the input words.
  for(string word; cin >> word;)
    {
      bool found = false;

      // First check whether there is an existing palindrome.
      // Iterate over the pairs in the map.
      for(auto &p: m)
        {
          auto j = p.second.find(word);
          if (j != p.second.end() && !j->exists(word))
            {
              auto nh = p.second.extract(j);
              nh.value().insert(word);
              m[p.first + 1].insert(move(nh));
              found = true;
              break;
            }
        }

      if (!found)
        m[0].insert(word);
    }

  for(const auto &p: m)
    for(const auto &e: p.second)
      {
        for(const auto &sp: e.m_words)
          cout << *sp << ' ';
        cout << '\n';
      }
}
