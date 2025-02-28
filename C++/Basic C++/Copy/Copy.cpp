#include <iostream>
using namespace std;

// 얕은 복사 vs 깊은 복사
/*
1. 얕은 복사(Shallow Copy)  

객체를 복사할 때, 해당 객체만 복사하여 새 객체를 생성한다. 
복사된 객체의 인스턴스 변수는 원본 객체의 인스턴스 변수와 같은 메모리 주소를 참조한다.
따라서, 해당 메모리 주소의 값이 변경되면 원본 객체 및 복사 객체의 인스턴스 변수 값은 같이 변경된다.

단점 - 2개의 객체가 1개의 주소를 갖기 때문에 오류가 발행할 수 있음

2. 깊은 복사(Deep Copy)

객체를 복사 할 때, 해당 객체와 인스턴스 변수까지 복사하는 방식.
전부를 복사하여 새 주소에 담기 때문에 참조를 공유하지 않는다.
*/

class Pet
{
public:
    Pet() { cout << "Pet()" << endl; }
    ~Pet() { cout << "~Pet()" << endl; }

    // 복사 생성자는 컴파일시 기본적으로 만들어줌.
    Pet(const Pet& pet) { cout << "Pet(const Pet& pet)" << endl; }
};

class Knight
{
public:
    Knight()
    {
        _pet = new Pet();
    }
    ~Knight()
    {
        delete _pet;
    }
    Knight(const Knight& k) // 복사 생성자 - 기본 생성자 따로 만들어야 됨.
    {
        _hp = k._hp;
        _pet = new Pet(*(k._pet)); // 복사 연산자의 오류가 생기지 않게 해야됨.
    }

    void operator=(const Knight& k)
    {
        _hp = k._hp;
    }

public:
    int _hp = 100;
    Pet* _pet;
};

int main()
{
    Knight k1;
    k1._hp = 200;

    // Knight k2(k1); // 복사 생성자

    Knight k3; // 기본 생성자
    k3 = k1; // 복사 연산자 - 같은 주소값을 가지게 되어, k3, k1이 동일한 객체가 됨.
}