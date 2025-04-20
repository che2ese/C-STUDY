#include <iostream>
using namespace std;

/*
함수 객체
    함수 포인터의 단점 해결
    - 타입 안 맞으면 사용 불가
    - 상태를 가질 수 없음(데이터 바인딩 불가능)
*/

class Functor
{
public:
    void operator() ()
    {
        cout << "Functor Test" << endl;
        cout << _value << endl;
    }
    void operator() (int n)
    {
        cout << "Functor Test + n" << endl;
        _value += n;
        cout << _value << endl;
    }

public:
    int _value = 0;
};

struct AddStruct
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};

template<typename T>
int DoSomething(int a, int b, T func)
{
    return func(a, b);
}

class MoveJob
{
public:
    MoveJob(int x, int y) : x(x), y(y) {}

    void operator()()
    {
        cout << "player move" << endl;
    }
public:
    int x; 
    int y;
};

int main()
{
    Functor func;
    func._value = 10;

    func();

    AddStruct function;
    DoSomething(10, 20, function);

    // 클라 : (10, 20) 좌표로 이동할래
    MoveJob* job = new MoveJob(10, 20);
}
