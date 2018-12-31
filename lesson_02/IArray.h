#pragma once
#include <SBArray.h>

template <typename T, typename C = SBArray<SBArray<T>>>
class IArray
{
private:
	int _size;
	C* _arr;
	int block_size_;

	void relocate(int newsize, int index) 
	{
		T* tmp = new T[newsize];

		if (_arr != nullptr) {
			for (int i = 0; i < _size; i++) {
				if (i<index)
					tmp[i] = _arr[i];
				else
					tmp[i + 1] = _arr[i];
			}
		}
		_arr = tmp;
		_size = newsize;
	}

public:
	explicit IArray(int block_size) : block_size_(block_size)
	{
		_arr = nullptr;
		_size = 0;
	};

	~IArray()
	{
		if (_arr != nullptr)
			delete _arr;
	}

	T get(int index)
	{
		return _arr[index];
	}

	void add(int index, T element) {
		if (_arr == nullptr || size() <= index) {
			relocate(); // IArray: add 100000 elements took 174.332 milliseconds
		}
		_arr[index] = element;
	}

	void set(int index, T element) 
	{
		_arr[index] = element;
	}

	int size() 
	{
		return _arr->size() * block_size_;
	}

    T at(int index) 
    {
		int index1 = index / block_size_;
		int index2 = index % block_size_;
		return (T)_arr.get(index1).get(index2);
	}
};
