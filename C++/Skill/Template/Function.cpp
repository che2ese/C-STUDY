#include <iostream>
using namespace std;

// 조커카드
template<typename T>
void Print(T input)
{
	cout << input << endl;
}

template<typename T1, typename T2>
void Print(T1 input1, T2 input2)
{
	cout << input1 << " " << input2 << endl;
}

// 특수 템플릿 - 내가 원하는 자료형일 때만 사용 가능
template<>
void Print(int input)
{
	cout << "int " << input << endl;
}

int main()
{
	// 지정 안하면 알아서 변환
	Print(1);
	Print(3.14f);
	Print("Hello World");
	Print(1, "Hello");

	Print<int>(1);
	Print<float>(3.14f);
	Print<const char*>("Hello World");
	Print<int, const char*>(1, "Hello");
}