#include <iostream>
#include "AutoDiff.hpp"

int main()
{
    double pi = 3.141592653589793238462643383;

    auto f = [](auto x) { return std::sin(x); };
    auto g = (d / dx)(f);

    std::cout << g(pi) << std::endl;

    return 0;
}
