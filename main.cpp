#include <iostream>
#include "DualNum.hpp"
#include <cmath>

template <typename T>
T func(T x)
{
    return T(2) * x * X;
}

int main()
{
    DualNum<> a{2.0, 1.0};

    std::cout << func(a).img() << std::endl;

    return 0;
}
