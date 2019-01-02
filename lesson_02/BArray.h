#pragma once
/*********************************************************
BArray<int>* a = new BArray<int>();
for (int i = 0; i<10; i++)
	a->add(i, i*i);

for (int i = 0; i < 10; i++)
	cout << a->get(i) << "\n";
*********************************************************/

#include <algorithm>

template <class T> class BArray
{
private:
	int size_;
	T* arr_;
	int block_size_;
	int allocated_size_;

	void relocate(int newsize, int index) 
	{
		T* tmp = new T[newsize];

		if (arr_ != nullptr) {
			for (int i = 0; i < size_; i++) {
				if (i<index)
					tmp[i] = arr_[i];
				else
					tmp[i + 1] = arr_[i];
			}
		}
		arr_ = tmp;
		allocated_size_ = newsize;
	}

public:
	explicit BArray(int initial_size, int block_size) 
		: size_(0)
		, arr_(nullptr)
		, block_size_(block_size)
		, allocated_size_(0)
	{
		relocate(initial_size, 0);
	};

	~BArray()
	{
		if (arr_ != nullptr)
			delete arr_;
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
		size_ = std::max(size_, index);
	}

	void set(int index, T element) 
	{
		arr_[index] = element;
	}

	int size() 
	{
		return size_;
	}

};
