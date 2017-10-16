#include <iostream>
#include "DualNum.hpp"

template <typename T>
T func(T x)
{
    return std::sin(x);
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
    double pi = 3.1415926535;
    std::cout << func(pi) << std::endl;
    std::cout << dfunc(pi) << std::endl;
    std::cout << ddfunc(pi) << std::endl;
    return 0;
}
