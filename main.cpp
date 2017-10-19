#include <iostream>
//#include <Eigen/Dense>
#include "AutoDiff.hpp"
//#include "DualNum.hpp"


int main()
{
    double a = 3.141592653589793238462643383;

    auto f = [](auto x) { return std::sin(x); };

    std::cout << Diff<double,0>()(f, a) << std::endl;
    std::cout << Diff<double,1>()(f, a) << std::endl;
    std::cout << Diff<double,2>()(f, a) << std::endl;
    std::cout << Diff<double,3>()(f, a) << std::endl;
    std::cout << Diff<double,4>()(f, a) << std::endl;
    std::cout << Diff<double,5>()(f, a) << std::endl;

    return 0;
}
