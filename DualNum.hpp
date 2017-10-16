// dual number
#pragma once
#include <ostream>
#include <cmath>

template <typename T = double>
class DualNum
{
private:
    T real_;
    T imag_;

public:
    using this_type = DualNum<T>;

    inline DualNum(T real, T imag = T(0))
        : real_(real), imag_(imag){};

    // getter
    inline T real() { return real_; }
    inline T imag() { return imag_; }

    /*----------------------------------------------------------------------
                            算術演算子
    ----------------------------------------------------------------------*/
    // 単項演算子
    inline this_type operator-() const { return this_type(-real_, -imag_); }
    inline this_type operator+() const { return *this; }

    // 代入演算子
    // dual number
    inline this_type& operator+=(const this_type& rhs)
    {
        real_ += rhs.real_;
        imag_ += rhs.imag_;
        return *this;
    }
    inline this_type& operator-=(const this_type& rhs)
    {
        real_ -= rhs.real_;
        imag_ -= rhs.imag_;
        return *this;
    }
    inline this_type& operator*=(const T& rhs)
    {
        real_ *= rhs;
        imag_ *= rhs;
        return *this;
    }
    inline this_type& operator/=(const T& rhs)
    {
        real_ /= rhs;
        imag_ /= rhs;
        return *this;
    }

    // real number
    inline this_type& operator+=(const T& rhs)
    {
        real_ += rhs;
        return *this;
    }
    inline this_type& operator-=(const T& rhs)
    {
        real_ -= rhs;
        return *this;
    }
    inline this_type operator*=(const this_type& rhs)
    {
        imag_ = imag_ * rhs.real_ + real_ * rhs.imag_;
        real_ *= rhs.real_;
        return *this;
    }
    inline this_type operator/=(const this_type& rhs)
    {
        imag_ = (imag_ * rhs.real_ - real_ * rhs.imag_) / (rhs.real_ * rhs.real_);
        real_ /= rhs.real_;
        return *this;
    }

    // 二項演算子
    // dual numer & dual number
    inline this_type operator+(const this_type& arg) const { return this_type(*this) += arg; }
    inline this_type operator-(const this_type& arg) const { return this_type(*this) -= arg; }
    inline this_type operator*(const this_type& arg) const { return this_type(*this) *= arg; }
    inline this_type operator/(const this_type& arg) const { return this_type(*this) /= arg; }

    // dual number & real number
    inline this_type operator+(const T& arg) const { return this_type(*this) += arg; }
    inline this_type operator-(const T& arg) const { return this_type(*this) -= arg; }
    inline this_type operator*(const T& arg) const { return this_type(*this) *= arg; }
    inline this_type operator/(const T& arg) const { return this_type(*this) /= arg; }

    // real number & dual number
    inline friend this_type operator+(const T& arg1, const this_type& arg2) { return this_type(arg1 + arg2.real_, arg2.imag_); }
    inline friend this_type operator-(const T& arg1, const this_type& arg2) { return this_type(arg1 - arg2.real_, arg2.imag_); }
    inline friend this_type operator*(const T& arg1, const this_type& arg2) { return this_type(arg1 * arg2.real_, arg1 * arg2.imag_); }
    inline friend this_type operator/(const T& arg1, const this_type& arg2) { return this_type(arg1 / arg2.real_, -arg1 * arg2.imag_ / (arg2.real_ * arg2.real_)); }


    // coutをいい感じにする
    inline friend std::ostream& operator<<(std::ostream& out, const this_type& arg)
    {
        if (arg.imag_ == 0) {
            return out << arg.real_;
        } else if (arg.real_ == 0) {
            return out << arg.imag_ << 'e';
        } else if (arg.imag_ < 0) {
            return out << arg.real_ << arg.imag_ << 'e';
        } else {
            return out << arg.real_ << '+' << arg.imag_ << 'e';
        }
    }

    // 一般関数をdual number対応にする
    // 指数・対数
    inline friend this_type exp(const this_type arg) { return this_type(exp(arg.real_), arg.imag_ * exp(arg.real_)); }
    inline friend this_type log(const this_type arg) { return this_type(log(arg.real_), arg.imag_ / arg.real_); }
    inline friend this_type pow(const this_type base, const this_type exponent) { return exp(exponent * log(base)); }
    inline friend this_type sqrt(const this_type arg) { return this_type(sqrt(arg.real_), arg.imag_ / (2 * sqrt(arg.real_))); }
    // 三角関数
    inline friend this_type sin(const this_type arg) { return this_type(sin(arg.real_), arg.imag_ * cos(arg.real_)); }
    inline friend this_type cos(const this_type arg) { return this_type(cos(arg.real_), -arg.imag_ * sin(arg.real_)); }
    inline friend this_type tan(const this_type arg) { return sin(arg) / cos(arg); }
    // 双曲線関数
    inline friend this_type sinh(const this_type arg) { return (exp(arg) - exp(-arg)) / 2; }
    inline friend this_type cosh(const this_type arg) { return (exp(arg) + exp(-arg)) / 2; }
    inline friend this_type tanh(const this_type arg) { return sinh(arg) / cosh(arg); }
    //逆三角関数
    /*
    inline friend this_type asin(const this_type arg) { return this_type(asin(arg.real_), arg.imag_ / sqrt(1 - real_ * real_)); }
    inline friend this_type acos(const this_type arg) { return this_type(acos(arg.real_), -arg.imag_ / sqrt(1 - real_ * real_)); }
    inline friend this_type atan(const this_type arg) { return this_type(atan(arg.real_), arg.imag_ / 1 + real_ * real_); }
    //逆双曲線関数
    inline friend this_type asinh(const this_type arg) { return this_type(asinh(arg.real_), arg.imag_ / sqrt(1 + real_ * real_)); }
    inline friend this_type acosh(const this_type arg) { return this_type(acosh(arg.real_), arg.imag_ / sqrt(real_ * real_ - 1)); }
    inline friend this_type atanh(const this_type arg) { return this_type(atanh(arg.real_), arg.imag_ / 1 - real_ * real_); }
    */
};
