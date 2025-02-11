#include <iostream>
using namespace std;

// OOP의 3대 요소
/*
    - 상속성 << inheritance
    - 은닉성 << Encapsulation (Data Hiding)
    - 다형성 << Polymorphism 
*/

// 다형성
/*
    - 오버로딩 (overloading) = 함수 이름의 재사용
    - 오버라이딩 (overriding)
*/

// 오버로딩
void Test(){

}
void Test(int a){

}
void Test(float a){

}

// 오버라이딩
class Player{
public:
    virtual void Move() { cout << "Player Move()" << endl; }
    virtual ~Player() { } // 소멸자도 virtual로

public:
    int _hp;
};

// 추상 클래스
/*
class Player{
public:
    virtual void Move() = 0 // 순수 가상 함수 = 나중에 상속받는 클래스에서 구현.

public:
    int _hp;
};
*/
class Knight : public Player{
public:
    virtual void Move() override { cout << "Knight Move()" << endl; } // override 붙이면 오류 검사해줌

public:
    int _stamina;
};

// 바인딩 = 묶는다
// - 정적 바인딩 (Static Binding = 컴파일 시점 결정)
// - 동적 바인딩 (Dynamic Binding = 실행 시점 결정)
void MovePlayer(Player* player){ // 매개변수에 Player 타입을 써서 Player의 주소를 찾아감 -> virtual로 해결
    player->Move();
}

int main(){
    Knight k1;
    MovePlayer(&k1);
}