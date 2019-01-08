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

template <class T> class BArray
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
				if (i<index)
					tmp[i] = arr_[i];
				else
					tmp[i + 1] = arr_[i];
			}
		}
		
		if (arr_) {
			delete [] arr_;
		}

		arr_ = tmp;
		allocated_size_ = newsize;
	}

public:
	explicit BArray(int block_size = DefaultBlock)
		: size_(0)
		, arr_(nullptr)
		, block_size_(block_size)
		, allocated_size_(0)
	{
		if (block_size_ < 1) {
			block_size_ = 1;
		}
		relocate(block_size_, 0);
    }

	~BArray()
	{
		if (arr_ != nullptr)
			delete [] arr_;
	}

	T get(int index)
	{
		return arr_[index];
	}

	void add(int index, T element) {
		if (arr_ == nullptr || allocated_size_ <= index) {
			relocate(index + block_size_, index);
		}
		arr_[index] = element;
		size_ = std::max(size_, index + 1);
	}

	void set(int index, T element) 
	{
		arr_[index] = element;
	}

	int size() 
	{
		return size_;
	}

	int allocated_size()
	{
		return allocated_size_;
	}
};
