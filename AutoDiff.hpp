#pragma once
#include "DualNum.hpp"


template <typename T, unsigned int N>
class Diff
{
public:
    inline T operator()(auto func, T x)
    {
        return Diff<DualNum<T>, N - 1>()(func, DualNum<T>(x, T(1))).imag();
    }
};

template <typename T>
class Diff<T, 0>
{
public:
    inline T operator()(auto func, T x)
    {
        return func(x);
    }
};

/*
自動微分をする（一入力一出力関数のみ）

<使い方>
auto f = [](auto x){演算;}
Diff<typename, 微分の階数>()(f,入力値);

<注意>
c++14以降でないと動きません
*/
