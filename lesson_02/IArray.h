#pragma once
#include "BArray.h"

template<typename T>
class IArray
{
  private:
    int _size;
    BArray<BArray<T>>* arr_;
    int block_size_;

    void relocate()
    {
        arr_.add(0, BArray<T>(block_size));
    }

  public:
    explicit IArray(int block_size) : block_size_(block_size)
    {
        arr_ = new BArray<BArray<T>>(block_size_);
        arr_.add(0, BArray<T>(block_size));
    };

    ~IArray()
    {
        if (arr_ != nullptr)
            delete [] arr_;
    }

    void add(int index, T element)
    {
        if (size() <= index) {
            relocate();
        }
        arr_[index] = element;
    }

    void set(int index, T element) { arr_[index] = element; }

    int size() { return arr_->size() * block_size_; }

    T get(int index)
    {
        int index1 = index / block_size_;
        int index2 = index % block_size_;
        return (T)arr_.get(index1).get(index2);
    }
};
