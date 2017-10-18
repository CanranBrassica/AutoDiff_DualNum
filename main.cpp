#include <iostream>
//#include <Eigen/Dense>
//#include "AutoDiff.hpp"
#include "DualNum.hpp"


int main()
{
    /*
    double a = 2;

    auto f = [](auto x) { return std::pow(x, 10); };

    std::cout << Diff<double, 0>()(f, a) << std::endl;
    std::cout << Diff<double, 1>()(f, a) << std::endl;
    std::cout << Diff<double, 2>()(f, a) << std::endl;
    std::cout << Diff<double, 3>()(f, a) << std::endl;
    */
    //    std::cout << Diff<double, 4>()(f, a) << std::endl;


    std::cout << DualNum<double>(1) << std::endl;
    std::cout << DualNum<DualNum<double>>(1) << std::endl;
    //std::cout << DualNum<DualNum<DualNum<double>>>(1) << std::endl;
    std::cout << DualNum<DualNum<DualNum<double>>>(DualNum<DualNum<double>>(1), DualNum<DualNum<double>>(0)) << std::endl;
    //std::cout << DualNum<DualNum<DualNum<DualNum<double>>>>(0) << std::endl;
    std::cout << DualNum<DualNum<DualNum<DualNum<double>>>>(DualNum<DualNum<DualNum<double>>>(1), DualNum<DualNum<DualNum<double>>>(0)) << std::endl;

    return 0;
}
