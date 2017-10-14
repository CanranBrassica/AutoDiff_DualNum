// dual number
#pragma once

#include <ostream>
#include <cmath>

template <typename T = double>
class DualNum
{
private:
    T real_;
    T img_;

public:
    using this_type = DualNum<T>;

    inline DualNum(T real, T img = T(0))
        : real_(real), img_(img){};

    inline this_type& operator-()
    {
        return this_type(-real_, -img_);
    }

    inline this_type& operator+=(this_type const& rhs)
    {
        real_ += rhs.real_;
        img_ += rhs.img_;
        return *this;
    }

    inline this_type operator-=(this_type const& rhs)
    {
        real_ -= rhs.real_;
        img_ -= rhs.img_;
        return *this;
    }

    inline this_type operator*=(this_type const& rhs)
    {
        img_ = img_ * rhs.real_ + real_ * rhs.img_;
        real_ *= rhs.real_;
        return *this;
    }

    inline this_type operator/=(this_type const& rhs)
    {
        img_ = (img_ * rhs.real_ - real_ * rhs.img_) / (rhs.real_ * rhs.real_);
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

    inline T img()
    {
        return img_;
    }

    inline friend std::ostream& operator<<(std::ostream& out, this_type const& rhs)
    {
        return out << rhs.real_ << "+" << rhs.img_ << "ε";
    }

    inline static this_type abs(this_type const& arg)
    {
        return std::abs(arg.real_);
    }

    inline static this_type sin(this_type const& arg)
    {
        return this_type(std::sin(arg.real_), arg.img_ * std::cos(arg.real_));
    }

    inline static this_type cos(this_type const& arg)
    {
        return this_type(std::cos(arg.real_), -arg.img_ * std::sin(arg.real_));
    }

    inline static this_type tan(this_type const& arg)
    {
        return sin(arg) / cos(arg);
    }

    inline static this_type exp(this_type const& arg)
    {
        return this_type(std::exp(arg.real_), arg.img_ * arg.real_ * std::exp(arg.real_));
    }

    inline static this_type log(this_type const& arg)
    {
        return this_type(std::log(arg.real_), arg.img_ / arg.real_);
    }

    inline static this_type pow(this_type const& base, this_type const& exponent)
    {
        return exp(exponent * log(base));
    }
};
