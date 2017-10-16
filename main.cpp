#include <iostream>
#include "DualNum.hpp"

template <typename T>
T func(T x)
{
    return x * x * x * x;
}

/*
二乗すると0になる数ε(実数ではない)を用いて、二重数a+bε(a,bは実数)を定義すると
f(a+bε)=f(a)+bf'(a)ε
となる。（テイラー展開を考えればわかる）
つまり、f'(a)=Im(f(a+ε))  (Im(a+bε)=b)
*/

template <typename T, unsigned int N>
class DiffFunc
{
public:
    inline T operator()(T x)
    {
        DiffFunc<DualNum<T>, N - 1> diff_func;
        return diff_func(DualNum<T>(x, T(1))).imag();
    }
};

template <typename T>
class DiffFunc<T, 0>
{
public:
    inline T operator()(T x)
    {
        return func(x);
    }
};


int main()
{
    double pi = 3.1415926535;
    std::cout << DiffFunc<double, 0>()(pi) << std::endl;
    std::cout << DiffFunc<double, 1>()(pi) << std::endl;
    std::cout << DiffFunc<double, 2>()(pi) << std::endl;
    std::cout << DiffFunc<double, 3>()(pi) << std::endl;
    std::cout << DiffFunc<double, 5>()(pi) << std::endl;
    return 0;
}
