#pragma once

#include <stdint.h>
#include <vector>
#include <limits>
#include <iostream>
#include <iterator>

template<typename Base=uint64_t,
         typename = std::enable_if_t<std::is_unsigned<Base>::value>>
class UBigInt
{
    public:
        using base_t = Base;

        template <typename B>
        friend std::ostream &operator<<(std::ostream& out, const UBigInt<B>& data);
        template <typename B>
        friend UBigInt operator+(const UBigInt& l, const UBigInt& r);

        UBigInt() : base_(std::numeric_limits<base_t>::max()) {}
        UBigInt(const UBigInt&) = default;
        UBigInt(UBigInt&&) = default;

        UBigInt(base_t n) : UBigInt()
        {
            assign(n);
        }

        ~UBigInt() = default;

        UBigInt& operator=(const UBigInt&) = default;
        UBigInt& operator=(UBigInt&&) = default;

        UBigInt& operator=(base_t n)
        {
            number_.clear();
            assign(n);
            return *this;
        }

        UBigInt& operator+=(const UBigInt& r)
        {
            if (number_.size() == r.number_.size()) {
                for (size_t i = 0; i < number_.size(); ++i) {
                    base_t value;
                    base_t carry_over = base_t();
                    if (zero(number_[i])) {
                        value = r.number_[i];
                    } else if (zero(r.number_[i])) {
                        value = number_[i];
                    } else {
                        value = number_[i] + r.number_[i];
                        if (sum_overflow(value, number_[i])) {
                            value =
                            carry_over =
                        }
                    }
                }
            }
            return *this;
        }

    private:
        // little endian
        // if Base is char then number 0x12345678 is an array with 4 elements
        // { 0x78, 0x56, 0x34, 0x12 }
        std::vector<Base> number_;
        base_t base_;

        bool zero(const base_t& v) const { return v == 0; }

        bool sum_overflow(const base_t& value, const base_t& data)
        {
            return (value < data);
        }

        void assign(base_t& n)
        {
            while (n) {
                base_t value = n % base_;
                if (value > 0) {
                    number_.push_back(value);
                    n /= base_;
                } else {
                    number_.push_back(base_);
                    n = 0;
                }
            }
        }
};

template <typename B>
std::ostream &operator<<(std::ostream& out, const UBigInt<B>& data)
{
    std::copy(data.number_.rbegin(), data.number_.rend(),
              std::ostream_iterator<B>(out, ""));
    return out;
}

template <typename B>
UBigInt<B> operator+(const UBigInt<B>& l, const UBigInt<B>& r)
{
    if (l.size() == r.size()) {
        for (size_t i = 0; i < l.size(); ++i) {

        }
    }
}
