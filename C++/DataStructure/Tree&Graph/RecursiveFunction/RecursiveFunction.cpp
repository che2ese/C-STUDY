#include <iostream>
using namespace std;

// 똑같은 함수를 재사용하면 효율적인 경우가 있음
// 함수가 끝나기 전에 함수를 실행함. 오류가 발생할 수 있음.
// 탈출 코드 항상 만들어야함.

void Func(int input)
{
	if (input == 0)
		return;

	cout << input << endl;
	Func(input - 1);
}

int Factorial(int n)
{
	if (n <= 1)
		return 1;

	return n * Factorial(n - 1);
}

// 유클리드 알고리즘
/*
	1071과 1029의 최대공약수를 구하면,
	
	1071은 1029로 나누어 떨어지지 않기 때문에, 1071을 1029로 나눈 나머지를 구한다. ≫ 42
	1029는 42로 나누어 떨어지지 않기 때문에, 1029를 42로 나눈 나머지를 구한다. ≫ 21
	42는 21로 나누어 떨어진다.
	따라서, 최대공약수는 21이다.
*/

int Euclid(int num1, int num2)
{
	if (num1 % num2 == 0)
		return num2;

	return Euclid(num2, num1 % num2);
}


int main()
{
	Func(5);
	cout << Factorial(5) << endl;
	cout << Euclid(1071, 1029) << endl;
}
