#include <set>
#include <vector>

using namespace std;

template <template <typename> typename C, typename T>
void
foo(const C<T> &c)
{
}

int
main()
{
    foo(set<int>{1, 2, 3});
    foo(vector<int>{1, 2, 3});
}
