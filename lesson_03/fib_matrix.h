#pragma once
#include "power.h"
#include <utility>

/* The algorithms are borrowed from 
   "Elements of Programming" by Alexander Stepanov and Paul McJones
*/

template<typename I>
std::pair<I, I> fib_matrix_mul(const std::pair<I, I>& x,
                               const std::pair<I, I>& y)
{
    /*
        [x1, x2] * [y1, y2] = [x1 * (y2 + y1) + x2 * y1, x1 * y1 + x2 * y2]
    */
    return std::make_pair(x.first * (y.second + y.first) + x.second * y.first,
                          x.first * y.first + x.second * y.second);
}

template<typename I>
I fib(I n)
{
    if (n == static_cast<I>(0)) {
        return static_cast<I>(0);
    }

    return power(std::make_pair(static_cast<I>(1), static_cast<I>(0)),
                 n,
                 fib_matrix_mul<I>).first;
}
