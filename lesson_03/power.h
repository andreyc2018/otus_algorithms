#pragma once

/* The algorithms are borrowed from 
   "Elements of Programming" by Alexander Stepanov and Paul McJones
*/
template<typename I>
bool odd(I n) { return n%2 == 1; }

template<typename I>
bool even(I n) { return !odd(n); }

template<typename I>
bool one(I n) { return n == 1; }

template<typename I>
bool zero(I n) { return n == 0; }

template<typename I>
I half_nonnegative(I n)
{
    return n / 2;
}

template<typename I, typename Op, typename T> // T = Domain(Op)
T power_accumulate_positive(T r, T a, I n, Op op)
{
    while (true) {
        if (odd(n)) {
            r = op(r, a);
            if (one(n))
                return r;
        }
        a = op(a, a);
        n = half_nonnegative(n);
    }
}

template<typename I, typename Op, typename T>
T power(T a, I n, Op op)
{
    while(even(n)) {
        a = op(a, a);
        n = half_nonnegative(n);
    }
    n = half_nonnegative(n);
    if (zero(n))
        return a;
    return power_accumulate_positive(a, op(a, a), n, op);
}
