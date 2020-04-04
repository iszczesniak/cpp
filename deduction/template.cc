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
    foo(set{1, 2, 3});
    foo(vector{1, 2, 3});
}
