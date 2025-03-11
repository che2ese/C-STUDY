#include <iostream>
using namespace std;

// 자료형을 나중에 정해야할 때 미리 템플릿 선언
template<typename T, int SIZE>
class RandomBox
{
public:
	T GetRandomData()
	{
		T index = rand() % SIZE;
		return data[index];
	}

public:
	T data[SIZE];
};

int main()
{
	// 아예 다른 함수로 컴파일 됨. 2개의 함수가 생성되는것.
	RandomBox<int, 100> rb1;
	RandomBox<float, 200> rb2;
}
