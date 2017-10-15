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
    inline this_type real() { return real_; }
    inline this_type imag() { return imag_; }

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
    inline this_type operator+(const this_type& rhs) const { return this_type(*this) += rhs; }
    inline this_type operator-(const this_type& rhs) const { return this_type(*this) -= rhs; }
    inline this_type operator*(const this_type& rhs) const { return this_type(*this) *= rhs; }
    inline this_type operator/(const this_type& rhs) const { return this_type(*this) /= rhs; }

    // dual number & real number
    inline this_type operator+(const T& rhs) const { return this_type(*this) += rhs; }
    inline this_type operator-(const T& rhs) const { return this_type(*this) -= rhs; }
    inline this_type operator*(const T& rhs) const { return this_type(*this) *= rhs; }
    inline this_type operator/(const T& rhs) const { return this_type(*this) /= rhs; }

    // real number & dual number
    inline friend this_type operator+(const T& rhs1, const this_type& rhs2) { return this_type(rhs1 + rhs2.real_, rhs2.imag_); }
    inline friend this_type operator-(const T& rhs1, const this_type& rhs2) { return this_type(rhs1 - rhs2.real_, rhs2.imag_); }
    inline friend this_type operator*(const T& rhs1, const this_type& rhs2) { return this_type(rhs1 * rhs2.real_, rhs1 * rhs2.imag_); }
    inline friend this_type operator/(const T& rhs1, const this_type& rhs2) { return this_type(rhs1 / rhs2.real_, -rhs1 * rhs2.imag_ / (rhs2.real_ * rhs2.real_)); }


    // coutをいい感じにする
    inline friend std::ostream& operator<<(std::ostream& out, const this_type& rhs)
    {
        if (rhs.imag_ == 0) {
            return out << rhs.real_;
        } else if (rhs.real_ == 0) {
            return out << rhs.imag_ << 'e';
        } else if (rhs.imag_ < 0) {
            return out << rhs.real_ << rhs.imag_ << 'e';
        } else {
            return out << rhs.real_ << '+' << rhs.imag_ << 'e';
        }
    }

    // 一般関数をdual number対応にする
    // 指数・対数
    inline friend this_type exp(const this_type arg) { return this_type(std::exp(arg.real_), arg.imag_ * std::exp(arg.real_)); }
    inline friend this_type log(const this_type arg) { return this_type(std::log(arg.real_), arg.imag_ / arg.real_); }
    inline friend this_type pow(const this_type base, const this_type exponent) { return exp(exponent * log(base)); }
    inline friend this_type sqrt(const this_type arg) { return this_type(std::sqrt(arg.real_), arg.imag_ / (2 * std::sqrt(arg.real_))); }
    // 三角関数
    inline friend this_type sin(const this_type arg) { return this_type(std::sin(arg.real_), arg.imag_ * std::cos(arg.real_)); }
    inline friend this_type cos(const this_type arg) { return this_type(std::cos(arg.real_), -arg.imag_ * std::sin(arg.real_)); }
    inline friend this_type tan(const this_type arg) { return sin(arg) / cos(arg); }
    // 双曲線関数
    inline friend this_type sinh(const this_type arg) { return (exp(arg) - exp(-arg)) / 2; }
    inline friend this_type cosh(const this_type arg) { return (exp(arg) + exp(-arg)) / 2; }
    inline friend this_type tanh(const this_type arg) { return sinh(arg) / cosh(arg); }
};
