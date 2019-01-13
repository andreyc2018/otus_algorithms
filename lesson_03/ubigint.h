#pragma once

#include <stdint.h>
#include <vector>
#include <limits>
#include <iostream>
#include <iterator>

class UBigInt
{
    public:
        using base_t = uint16_t;
        using sum_t = uint64_t;

        friend std::ostream &operator<<(std::ostream& out, const UBigInt& data);
        friend UBigInt operator+(const UBigInt& l, const UBigInt& r);

        UBigInt() : base_(std::numeric_limits<base_t>::max()) {}
        UBigInt(const UBigInt&) = default;
        UBigInt(UBigInt&&) = default;

        explicit UBigInt(base_t n) : UBigInt()
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
            sum_t sum;
            base_t carry_over = 0;
            if (number_.size() == r.number_.size()) {
                for (size_t i = 0; i < r.number_.size(); ++i) {
                    sum = number_[i] + r.number_[i] + carry_over;
                    carry_over = assign(sum);
                }
                if (carry_over > 0) {
                    number_.push_back(carry_over);
                }
            }
            return *this;
        }

    private:
        // little endian
        // if Base is char then number 0x12345678 is an array with 4 elements
        // { 0x78, 0x56, 0x34, 0x12 }
        std::vector<base_t> number_;
        base_t base_;

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

        sum_t assign(sum_t& n)
        {
            base_t value = n % base_;
            if (value > 0) {
                number_.push_back(value);
                return n / base_;
            }
            number_.push_back(base_);
            return 0;
        }
};

std::ostream &operator<<(std::ostream& out, const UBigInt& data)
{
    std::copy(data.number_.rbegin(), data.number_.rend(),
              std::ostream_iterator<UBigInt::base_t>(out, ""));
    return out;
}

UBigInt operator+(const UBigInt& l, const UBigInt& r)
{
//    if (l.size() == r.size()) {
//        for (size_t i = 0; i < l.size(); ++i) {

//        }
//    }
}
