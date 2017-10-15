#include <iostream>
#include "DualNum.hpp"

template <typename T>
T func(T x)
{
    using namespace std;
    return exp(x);
}

template <typename T>
T dfunc(T x)
{
    return func(DualNum<T>(x, T(1))).imag();
}

int main()
{
    std::cout << dfunc(1.0) << std::endl;
    return 0;
}
