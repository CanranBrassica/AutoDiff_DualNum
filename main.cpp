#include <iostream>
#include "AutoDiff.hpp"

int main()
{
    double pi = 3.14159265358979323846;

    auto f = [](auto x) { return std::cos(std::sin(x)); };
    std::cout << Diff<double, 0>()(f, pi) << std::endl;
    std::cout << Diff<double, 1>()(f, pi) << std::endl;
    std::cout << Diff<double, 2>()(f, pi) << std::endl;
    std::cout << Diff<double, 3>()(f, pi) << std::endl;

    return 0;
}
