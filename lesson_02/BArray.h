#pragma once
/*********************************************************
BArray<int>* a = new BArray<int>();
for (int i = 0; i<10; i++)
        a->add(i, i*i);

for (int i = 0; i < 10; i++)
        cout << a->get(i) << "\n";
*********************************************************/

#include <algorithm>

const size_t DefaultBlock = 1000;

template<class T>
class BArray
{
  private:
    int size_;
    T* arr_;
    int block_size_;
    int allocated_size_;

    void relocate(int newsize, int index)
    {
        T* tmp = new T[newsize]();

        // DO we need to copy all data? Why not?
        if (arr_ != nullptr) {
            for (int i = 0; i < size_; i++) {
                if (i < index)
                    tmp[i] = arr_[i];
                else
                    tmp[i+1] = arr_[i];
            }
        }

        if (arr_) {
            delete[] arr_;
        }

        arr_ = tmp;
        allocated_size_ = newsize;
    }

    void shift(int index)
    {
        for (int i = size_; i > index; --i) {
            arr_[i] = arr_[i-1];
        }
    }

    int get_new_size(int index)
    {
        int new_size = 0;
        if (arr_ == nullptr
                || allocated_size_ <= index || allocated_size_ <= (size_+1)) {
            new_size = (index > allocated_size_)?
                           index + block_size_ : allocated_size_ + block_size_;
        }
        return new_size;
    }

  public:
    explicit BArray(int block_size = DefaultBlock)
      : size_(0), arr_(nullptr), block_size_(block_size), allocated_size_(0)
    {
        if (block_size_ < 1) {
            block_size_ = DefaultBlock;
        }
    }

    ~BArray()
    {
        if (arr_ != nullptr)
            delete[] arr_;
    }

    T get(int index) { return arr_[index]; }

    void add(int index, T element)
    {
        int new_size = get_new_size(index);
        if (new_size > 0) {
            relocate(new_size, index);
        }
        else {
            shift(index);
        }
        arr_[index] = element;
        size_ = std::max(size_ + 1, index + 1);
    }

    void set(int index, T element) { arr_[index] = element; }

    void remove(int index)
    {
        if (index < 0 && index >= allocated_size_) {
            return;
        }
    }

    int size() { return size_; }

    int allocated_size() { return allocated_size_; }
};
