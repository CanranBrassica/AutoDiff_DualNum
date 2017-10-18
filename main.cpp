#include <iostream>
//#include <Eigen/Dense>
#include "AutoDiff.hpp"
#include "DualNum.hpp"


int main()
{
    double a = 2;

    auto f = [](auto x) { return std::sin(x); };

    std::cout << Diff<double, 0>()(f, a) << std::endl;
    std::cout << Diff<double, 1>()(f, a) << std::endl;
    std::cout << Diff<double, 2>()(f, a) << std::endl;
    std::cout << Diff<double, 3>()(f, a) << std::endl;
    std::cout << Diff<double, 4>()(f, a) << std::endl;

    return 0;
}
