#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

using places_type = map<string, int>;

struct cmp
{
  places_type &m_places;

  cmp(places_type &places): m_places(places)
  {
  }

  bool
  operator()(const string &a, const string &b) const
  {
    return m_places[a] < m_places[b];
  }
};

int
main()
{
  vector v = {"Mo", "Ann", "Joe"};
  places_type places = {{"Mo", 3}, {"Ann", 1},
                        {"Joe", 2}, {"Shmo", 4}};

  sort(v.begin(), v.end(), cmp(places));

  for(auto &name: v)
    cout << name << endl;

  sort(v.begin(), v.end(),
       [&places](const string &a, const string &b)
       {return places[a] < places[b];});
}
