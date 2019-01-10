#pragma once
#include "BArray.h"
#include <tuple>

template<typename T>
class IArray
{
  private:
    using block_t = BArray<T>;
    using array_t = BArray<block_t*>;

    int _size;
    array_t* arr_;
    int block_size_;

    void relocate()
    {
        block_t* block = new block_t(block_size_);
        arr_->add(_size, block);
        _size++;
    }

  public:
    explicit IArray(int block_size = DefaultBlock)
      : _size(0), arr_(new array_t(block_size)), block_size_(block_size)
    {}

    ~IArray() { delete arr_; }

    void add(int index, T element)
    {
        int index1;
        int index2;
        std::tie(index1, index2) = get_index(index);

        if (index1 >= arr_->size()) {
            relocate();
        }
        arr_->get(index1)->add(index2, element);
    }

    void set(int index, T element)
    {
        int index1;
        int index2;
        std::tie(index1, index2) = get_index(index);
        arr_->get(index1)->set(index2, element);
    }

    int size() { return _size; }

    T get(int index)
    {
        int index1;
        int index2;
        std::tie(index1, index2) = get_index(index);
        return arr_->get(index1)->get(index2);
    }

  private:
    std::tuple<int, int> get_index(int index)
    {
        int index1 = index / block_size_;
        int index2 = index % block_size_;
        return std::make_tuple(index1, index2);
    }
};
