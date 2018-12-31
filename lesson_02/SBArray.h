/*********************************************************
SBArray<int>* a = new SBArray<int>();
for (int i = 0; i<10; i++)
	a->add(i, i*i);

for (int i = 0; i < 10; i++)
	cout << a->get(i) << "\n";
*********************************************************/

#pragma once
template <class T> class SBArray
{
private:
	int _size;
	T* _arr;
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
	explicit SBArray(int block_size) : block_size_(block_size)
	{
		_arr = nullptr;
		_size = 0;
	};

	~SBArray()
	{
		if (_arr != nullptr)
			delete _arr;
	}

	T get(int index)
	{
		return _arr[index];
	}

	void add(int index, T element) {
		if (_arr == nullptr || _size <= index) {
			relocate(index + block_size_, index); // SBArray: add 100000 elements took 174.332 milliseconds
		}
		_arr[index] = element;
	}

	void set(int index, T element) 
	{
		_arr[index] = element;
	}

	int size() 
	{
		return _size;
	}

};

