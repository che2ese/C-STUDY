#pragma once
#include "Vector.h"

template<typename T>
class Stack
{
public:
	// 스택의 기능들
	// 데이터 삽입
	void Push(const T& value)
	{
		_container.push_back(value);
	}
	// 데이터 삭제
	void Pop()
	{
		_container.pop_back();
	}
	// 데이터 꺼내오기 - 꺼내오는 동시에 삭제하면 오류가 날 수 있음. 따라서 꺼내오고 삭제하는 2가지 단계로 진행.
	T& Top()
	{
		return _container.back();
	}

	Vector<T>& GetContainer() { return _container; }
	// 비어있는지
	bool empty() { return size() > 0; }
	// 데이터 사이즈
	int size() { return _container.size(); }

private:
	Vector<T> _container;
};

