#pragma once

#include <iterator>

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

        T& base() { return array_; };

    private:
        T& array_;
        iterator begin_;
        iterator end_;
};

template <typename T>
view_range<T> merge(view_range<T>& left, view_range<T>& right)
{
    view_range<T> result(left.base(), left.begin(), right.end());
    return result;
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
