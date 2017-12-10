#include <iostream>
#include "AutoDiff.hpp"

int main()
{
    double pi = 3.141592653589793238462643383;

    auto f = [](auto x) { return std::sin(x); };

    auto g = (d / dx)(f);

    std::cout << g(pi) << std::endl;
    std::cout << (d / dx)(f)(pi) << std::endl;

    /*
    std::cout << Diff<double, 0>()(f, a) << std::endl;
    std::cout << Diff<double, 1>()(f, a) << std::endl;
    std::cout << Diff<double, 2>()(f, a) << std::endl;
    std::cout << Diff<double, 3>()(f, a) << std::endl;
    std::cout << Diff<double, 4>()(f, a) << std::endl;
    std::cout << Diff<double, 5>()(f, a) << std::endl;
    */

    return 0;
}


/*
auto f = [](double x){return hoge;}:

auto g = d/dx(f);
       = d./(dx)(f)
       =[](T x){return Diff<T, 1>()(f,x);}
dxはfの第一引数を微分する意味    int dx = 1; とか?
オブジェクトdの/メソッドにdxを渡すと、関数を引数にとりそれを微分する関数が返る

g(1);

auto g = d/dx


*/
