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

template <typename T>
T ddfunc(T x)
{
    return dfunc(DualNum<T>(x, T(1))).imag();
}

int main()
{
    double a = 3.1415926535;
    std::cout << func(a) << std::endl;
    std::cout << dfunc(a) << std::endl;
    std::cout << ddfunc(a) << std::endl;

    return 0;
}
