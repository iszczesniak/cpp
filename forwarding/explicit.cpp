#include <iostream>
#include <utility>

struct A
{
    template <typename Self, typename Src>
    auto && operator=(this Self &&self, A &&src)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return forward<Self>(self);
    }
};

int main()
{
    A a;
    a = A();
}
