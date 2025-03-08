#pragma once
#include <assert.h>

template<typename T>
class Vector
{
public:
	explicit Vector()
	{
	}

	~Vector()
	{
		if (_buffer)
			delete[] _buffer;
	}

	void clear()
	{
		// TODO
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}

		_size = 0;
	}

	void push_back(const T& data)
	{
		// TODO
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장
		_buffer[_size] = data;

		// 데이터 개수 증가
		_size++;
	}

	void pop_back()
	{
		// TODO : 소멸
		_size--;
	}

	T& back()
	{
		return _buffer[_size - 1];
	}

	void resize(int size)
	{
		// TODO
		reserve(size);
		_size = size;
	}

	void reserve(int capacity)
	{
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity];

		// 데이터 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		if (_buffer)
			delete[] _buffer;

		_buffer = newData;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < _size);
		return _buffer[index];
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T* _buffer = nullptr;
	int		_size = 0;
	int		_capacity = 0;
};
