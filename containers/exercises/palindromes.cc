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
  set<string> m_words;

  palindromes(const string &first): m_base(first)
  {
    // Create the base word.
    std::sort(m_base.begin(), m_base.end());
    // Insert the first word.
    m_words.insert(first);
  }

  void
  insert(string &&word)
  {
    m_words.insert(move(word));
  }

  bool exists(const string &word) const
  {
    return m_words.find(word) != m_words.end();
  }
};

bool operator < (const palindromes &a, const palindromes &b)
{
  return a.m_base < b.m_base;
}

int
main()
{
  timer("Took", false);

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
              nh.value().insert(move(word));
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
        for(const auto &word: e.m_words)
          cout << word << ' ';
        cout << '\n';
      }
}
