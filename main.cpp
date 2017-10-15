#include <iostream>
#include <functional>
#include "DualNum.hpp"


template <typename T>
T f(T x)
{
    using namespace std;
    return exp(x);
}

template <typename T>
T D(std::function<T(T)>)

    int main()
{


    DualNum<double> a{1.0, 1.0};

    return 0;
}
