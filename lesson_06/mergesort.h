#pragma once

#include <iterator>
#include <iostream>

namespace otus {

template <typename T>
class view_range
{
    public:
        using iterator = typename T::iterator;
        using difference_type = typename T::difference_type;
        using size_type = typename T::size_type;

        view_range(T& array, iterator b, iterator e)
            : array_(array), begin_(b), end_(e) {}

        iterator begin() const { return begin_; }
        iterator end() const { return end_; }
        iterator offset(difference_type offset) const { return std::next(begin_, offset); }

        size_type size() const { return std::distance(begin_, end_); }

        T& base() { return array_; }
        const T& base() const { return array_; }

    private:
        T& array_;
        iterator begin_;
        iterator end_;
};

template <typename T, typename I>
void debug_print(const T& result, const T& left, const T& right, const I& l, const I& r)
{
    std::cout << std::distance(left.begin(), l) << ":"
              << std::distance(right.begin(), r) << " ";
    for (const auto& v : result.base()) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

template <typename T, typename I>
void debug_print(const T& result, const I& lbegin, const I& rbegin, const I& l, const I& r)
{
    std::cout << std::distance(lbegin, l) << ":"
              << std::distance(rbegin, r) << " ";
    for (const auto& v : result) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}

template <typename T>
view_range<T> merge(view_range<T>& left, view_range<T>& right)
{
    T result;
    view_range<T> result_view(left.base(), left.begin(), right.end());
    auto e = result_view.begin();
    auto l = left.begin();
    auto r = right.begin();

    debug_print(result_view, left, right, l, r);

    auto next = *l;
    while (l != left.end() && r != right.end()) {
        if (next > *r) {
//            result.push_back(*r);
            *e = *r;
            ++r;
        }
        else if (next < *r) {
//            result.push_back(*l);
            ++l;
            auto tmp = *l;
            *e = next;
            next = tmp;
        }
//        std::swap(*e, next);
        ++e;
        debug_print(result_view, left, right, l, r);
        std::cout << "n = " << next << "\n";
//        debug_print(result, left.begin(), right.begin(), l, r);
    }
    debug_print(result_view, left, right, l, r);
    std::cout << "n = " << next << "\n";

//    for (; l != left.end(); ++l) {
//        result.push_back(*l);
//    }

//    for (; r != right.end(); ++r) {
//        result.push_back(*r);
//    }

//    debug_print(result, left.begin(), right.begin(), l, r);

    return result_view;
}

template <typename T>
view_range<T> merge_array(view_range<T>& left, view_range<T>& right)
{
    T result;
    view_range<T> result_view(left.base(), left.begin(), right.end());
    auto l = left.begin();
    auto r = right.begin();

    debug_print(result_view, left, right, l, r);

    while (l != left.end() && r != right.end()) {
        if (*l > *r) {
            result.push_back(*r);
            ++r;
        }
        else if (*l < *r) {
            result.push_back(*l);
            ++l;
        }
        debug_print(result, left.begin(), right.begin(), l, r);
    }

    for (; l != left.end(); ++l) {
        result.push_back(*l);
    }

    for (; r != right.end(); ++r) {
        result.push_back(*r);
    }

    debug_print(result, left.begin(), right.begin(), l, r);

    return result_view;
}

template <typename T>
view_range<T> split_merge(view_range<T>& view)
{
    if (view.size() < 2) {
        return view;
    }

    auto m = view.size() / 2;
    view_range<T> left(view.base(), view.begin(), view.offset(m));
    split_merge(left);

    view_range<T> right(view.base(), view.offset(m), view.end());
    split_merge(right);

    auto result = merge(left, right);

    return result;
}

template <typename T>
void merge_sort(T& array)
{
    if (array.size() < 2) {
        return;
    }
    view_range<T> view(array, std::begin(array), std::end(array));

    split_merge(view);
}

}
