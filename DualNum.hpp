// dual number
#pragma once
#include <ostream>
#include <cmath>

/*
 二重数(dual number)を定義する
 二重数とは、二乗すると0になる数εを用いて
 a+bεと表される数
*/

template <typename T>
class DualNum
{
private:
    T real_;
    T imag_;

public:
    template <typename U>
    inline DualNum<T>(U real, U imag = U(0))
        : real_(T(real)), imag_(T(imag)){};

    // getter
    inline T real() const { return real_; }
    inline T imag() const { return imag_; }

    /*----------------------------------------------------------------------
                            算術演算子
    ----------------------------------------------------------------------*/
    // 単項演算子
    inline DualNum<T> operator-() const { return DualNum<T>(-real_, -imag_); }
    inline DualNum<T> operator+() const { return *this; }

    // 代入演算子
    // dual number
    inline DualNum<T>& operator+=(const DualNum<T>& rhs)
    {
        real_ += rhs.real_;
        imag_ += rhs.imag_;
        return *this;
    }
    inline DualNum<T>& operator-=(const DualNum<T>& rhs)
    {
        real_ -= rhs.real_;
        imag_ -= rhs.imag_;
        return *this;
    }
    inline DualNum<T> operator*=(const DualNum<T>& rhs)
    {
        imag_ = imag_ * rhs.real_ + real_ * rhs.imag_;
        real_ *= rhs.real_;
        return *this;
    }
    inline DualNum<T> operator/=(const DualNum<T>& rhs)
    {
        imag_ = (imag_ * rhs.real_ - real_ * rhs.imag_) / (rhs.real_ * rhs.real_);
        real_ /= rhs.real_;
        return *this;
    }

    // real number
    template <typename U>
    inline DualNum<T>& operator+=(const U& rhs)
    {
        real_ += rhs;
        return *this;
    }
    template <typename U>
    inline DualNum<T>& operator-=(const U& rhs)
    {
        real_ -= rhs;
        return *this;
    }
    template <typename U>
    inline DualNum<T>& operator*=(const U& rhs)
    {
        real_ *= rhs;
        imag_ *= rhs;
        return *this;
    }
    template <typename U>
    inline DualNum<T>& operator/=(const U& rhs)
    {
        real_ /= rhs;
        imag_ /= rhs;
        return *this;
    }


    // 二項演算子
    // dual numer & dual number
    inline DualNum<T> operator+(const DualNum<T>& arg) const { return DualNum<T>(*this) += arg; }
    inline DualNum<T> operator-(const DualNum<T>& arg) const { return DualNum<T>(*this) -= arg; }
    inline DualNum<T> operator*(const DualNum<T>& arg) const { return DualNum<T>(*this) *= arg; }
    inline DualNum<T> operator/(const DualNum<T>& arg) const { return DualNum<T>(*this) /= arg; }

    // dual number & real number
    template <typename U>
    inline DualNum<T> operator+(const U& arg) const
    {
        return DualNum<T>(*this) += arg;
    }
    template <typename U>
    inline DualNum<T> operator-(const U& arg) const
    {
        return DualNum<T>(*this) -= arg;
    }
    template <typename U>
    inline DualNum<T> operator*(const U& arg) const
    {
        return DualNum<T>(*this) *= arg;
    }
    template <typename U>
    inline DualNum<T> operator/(const U& arg) const
    {
        return DualNum<T>(*this) /= arg;
    }

    // real number & dual number
    template <typename U>
    inline friend DualNum<T> operator+(const U& arg1, const DualNum<T>& arg2)
    {
        return DualNum<T>(arg1 + arg2.real_, arg2.imag_);
    }
    template <typename U>
    inline friend DualNum<T> operator-(const U& arg1, const DualNum<T>& arg2)
    {
        return DualNum<T>(arg1 - arg2.real_, arg2.imag_);
    }
    template <typename U>
    inline friend DualNum<T> operator*(const U& arg1, const DualNum<T>& arg2)
    {
        return DualNum<T>(arg1 * arg2.real_, arg1 * arg2.imag_);
    }
    template <typename U>
    inline friend DualNum<T> operator/(const U& arg1, const DualNum<T>& arg2)
    {
        return DualNum<T>(arg1 / arg2.real_, -arg1 * arg2.imag_ / (arg2.real_ * arg2.real_));
    }


    // coutをいい感じにする
    inline friend std::ostream& operator<<(std::ostream& out, const DualNum<T>& arg)
    {
        if (arg.imag_ == 0) {
            return out << arg.real_;
        } else if (arg.real_ == 0) {
            return out << arg.imag_ << 'e';
        } else if (arg.imag_ < 0) {
            return out << arg.real_ << arg.imag_ << 'e';
        } else {
            return out << "(" << arg.real_ << '+' << arg.imag_ << "e)";
        }
    }
};

namespace std
{
//プロトタイプ宣言
template <typename T>
DualNum<T> cos(const DualNum<T> arg);


// 一般関数をdual number対応にする

// f(a+bε)=f(a)+bf'(a)ε

// 指数・対数
template <typename T>
DualNum<T> exp(const DualNum<T> arg)
{
    return DualNum<T>(exp(arg.real()), arg.imag() * exp(arg.real()));
}
template <typename T>
DualNum<T> log(const DualNum<T> arg)
{
    return DualNum<T>(log(arg.real()), arg.imag() / arg.real());
}
template <typename T>
DualNum<T> pow(const DualNum<T> base, const DualNum<T> exponent)
{
    return exp(exponent * log(base));
}
template <typename T, typename U>
DualNum<T> pow(const DualNum<T> base, const U exponent)
{
    return exp(exponent * log(base));
}
template <typename T, typename U>
DualNum<T> pow(const U base, const DualNum<T> exponent)
{
    return exp(exponent * log(base));
}
template <typename T>
DualNum<T> sqrt(const DualNum<T> arg)
{
    return DualNum<T>(sqrt(arg.real()), arg.imag() / (2 * sqrt(arg.real())));
}
// 三角関数
template <typename T>
DualNum<T> sin(const DualNum<T> arg)
{
    return DualNum<T>(sin(arg.real()), arg.imag() * cos(arg.real()));
}
template <typename T>
DualNum<T> cos(const DualNum<T> arg)
{
    return DualNum<T>(cos(arg.real()), -arg.imag() * sin(arg.real()));
}
template <typename T>
DualNum<T> tan(const DualNum<T> arg)
{
    return sin(arg) / cos(arg);
}
// 双曲線関数
template <typename T>
DualNum<T> sinh(const DualNum<T> arg)
{
    return (exp(arg) - exp(-arg)) / 2;
}
template <typename T>
DualNum<T> cosh(const DualNum<T> arg)
{
    return (exp(arg) + exp(-arg)) / 2;
}
template <typename T>
DualNum<T> tanh(const DualNum<T> arg)
{
    return sinh(arg) / cosh(arg);
}
//逆三角関数
template <typename T>
DualNum<T> asin(const DualNum<T> arg)
{
    return DualNum<T>(asin(arg.real()), arg.imag() / sqrt(1 - arg.real() * arg.real()));
}
template <typename T>
DualNum<T> acos(const DualNum<T> arg)
{
    return DualNum<T>(acos(arg.real()), -arg.imag() / sqrt(1 - arg.real() * arg.real()));
}
template <typename T>
DualNum<T> atan(const DualNum<T> arg)
{
    return DualNum<T>(atan(arg.real()), arg.imag() / 1 + arg.real() * arg.real());
}
//逆双曲線関数
template <typename T>
DualNum<T> asinh(const DualNum<T> arg)
{
    return DualNum<T>(asinh(arg.real()), arg.imag() / sqrt(1 + arg.real() * arg.real()));
}
template <typename T>
DualNum<T> acosh(const DualNum<T> arg)
{
    return DualNum<T>(acosh(arg.real()), arg.imag() / sqrt(arg.real() * arg.real() - 1));
}
template <typename T>
DualNum<T> atanh(const DualNum<T> arg)
{
    return DualNum<T>(atanh(arg.real()), arg.imag() / 1 - arg.real() * arg.real());
}
}  //end of namespace std
