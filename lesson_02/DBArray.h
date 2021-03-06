#pragma once

/*********************************************************
DBArray<int>* a = new DBArray<int>();
for (int i = 0; i<10; i++)
	a->add(i, i*i);

for (int i = 0; i < 10; i++)
	cout << a->get(i) << "\n";
*********************************************************/

template <class T> class DBArray
{
private:
	int _size;
	T* _arr;

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
	explicit DBArray(int initial_size = 100) 
		: _size(0)
		, _arr(nullptr)
	{
		if (initial_size > 0) {
			relocate(initial_size, 0);
		}
	};

	~DBArray()
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
			relocate(index * 2, index); // DBArray: add 100000 elements took 0.880762 milliseconds
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

