#include <iostream>
#include "DualNum.hpp"

template <typename T>
T func(T x)
{
    using namespace std;
    return sin(x);
}

template <typename T>
T dfunc(T x)
{
    return func(DualNum<T>(x, T(1))).imag();
}

int main()
{
    double pi = 3.1415926535;
    std::cout << dfunc(pi / 2) << std::endl;
    return 0;
}
