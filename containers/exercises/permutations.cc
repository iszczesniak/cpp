#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct iter
{
  const vector<string> &m_words;
  vector<unsigned> m_perm;
  bool last;

  iter(const vector<string> &words):
    m_words(words), m_perm(words.size()), last(false)
  {
    for(unsigned i = 0; i < m_perm.size(); ++i)
      m_perm[i] = i;
  }

  iter(const vector<string> &words, bool):
    m_words(words), last(true)
  {
  }

  string
  operator*()
  {
    string ret;
    for(auto &i: m_perm)
      ret += m_words[i] + " ";
    return ret;
  }

  iter &
  operator++()
  {
    if (!std::next_permutation(m_perm.begin(), m_perm.end()))
      last = true;

    return *this;
  }

  bool
  operator==(const iter &i) const
  {
    if (last == true && i.last == true)
      return true;

    return m_perm == i.m_perm;
  }
};

struct range
{
  const vector<string> &m_words;

  range(const vector<string> &words): m_words(words)
  {
  }

  iter
  begin() const
  {
    return iter(m_words);
  }

  iter
  end() const
  {
    return iter(m_words, true);
  }
};

int
main()
{
  vector<string> words = {"Ala", "ma", "kota"};

  for(auto &&sentence: range(words))
    cout << sentence << endl;
}
