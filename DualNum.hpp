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

    inline this_type& operator-()
    {
        return this_type(-real_, -imag_);
    }

    inline this_type& operator+=(this_type const& rhs)
    {
        real_ += rhs.real_;
        imag_ += rhs.imag_;
        return *this;
    }

    inline this_type operator-=(this_type const& rhs)
    {
        real_ -= rhs.real_;
        imag_ -= rhs.imag_;
        return *this;
    }

    inline this_type operator*=(this_type const& rhs)
    {
        imag_ = imag_ * rhs.real_ + real_ * rhs.imag_;
        real_ *= rhs.real_;
        return *this;
    }

    inline this_type operator/=(this_type const& rhs)
    {
        imag_ = (imag_ * rhs.real_ - real_ * rhs.imag_) / (rhs.real_ * rhs.real_);
        real_ /= rhs.real_;
        return *this;
    }

    inline this_type operator+(this_type const& rhs) const
    {
        return this_type(*this) += rhs;
    }

    inline this_type operator-(this_type const& rhs) const
    {
        return this_type(*this) -= rhs;
    }

    inline this_type operator*(this_type const& rhs) const
    {
        return this_type(*this) *= rhs;
    }

    inline this_type operator/(this_type const& rhs) const
    {
        return this_type(*this) /= rhs;
    }

    inline T real()
    {
        return real_;
    }

    inline T imag()
    {
        return imag_;
    }

    inline friend std::ostream& operator<<(std::ostream& out, this_type const& rhs)
    {
        return out << rhs.real_ << "+" << rhs.imag_ << "ε";
    }

    inline static this_type abs(this_type const& arg)
    {
        return std::abs(arg.real_);
    }

    inline static this_type sin(this_type const& arg)
    {
        return this_type(std::sin(arg.real_), arg.imag_ * std::cos(arg.real_));
    }

    inline static this_type cos(this_type const& arg)
    {
        return this_type(std::cos(arg.real_), -arg.imag_ * std::sin(arg.real_));
    }

    inline static this_type tan(this_type const& arg)
    {
        return sin(arg) / cos(arg);
    }

    inline static this_type exp(this_type const& arg)
    {
        return this_type(std::exp(arg.real_), arg.imag_ * arg.real_ * std::exp(arg.real_));
    }

    inline static this_type log(this_type const& arg)
    {
        return this_type(std::log(arg.real_), arg.imag_ / arg.real_);
    }

    inline static this_type pow(this_type const& base, this_type const& exponent)
    {
        return exp(exponent * log(base));
    }
};
