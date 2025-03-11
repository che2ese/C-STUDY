#pragma once
#include "Vector.h"

template<typename T>
class Queue
{
public:
	Queue()
	{
		_container.resize(100);
	}

	void Enqueue(const T& value)
	{
		if (_size == _container.size())
		{

		}

		_container[_back] = value;
		// size 영역을 벗어나면 한 바퀴 리셋
		_back = (_back + 1) % _container.size();
		_size++;
	}
	void Dequeue()
	{
		// size 영역을 벗어나면 한 바퀴 리셋
		_front = (_front + 1) % _container.size();
		/*
			ex)
				[ front ] [ ] [ ] [ ] [ ] [ back ]
				[ 삭제 ] [ front ] [ ] [ ] [ ] [ back ]
				front == back 이면 데이터 1개
		*/
		_size--; // 사이즈 줄이기
	}

	T& Front()
	{
		return _container[_front];
	}

	Vector<T>& GetContainer() { return _container; }
	bool empty() { return _size == 0; }
	int size() { return _size; }

private:
	Vector<T> _container;

	// 직접 위치 관리
	int _front = 0; // 앞 데이터 삭제시 사용
	int _back = 0; // 뒤 데이터 삽입시 사용
	int _size = 0;
};

