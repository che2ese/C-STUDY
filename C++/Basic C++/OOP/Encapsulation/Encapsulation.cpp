#include <iostream>
using namespace std;

// OOP의 3대 요소
/*
    - 상속성 << inheritance
    - 은닉성 << Encapsulation (Data Hiding)
    - 다형성
*/

// 은닉성

// 자동차 제조 과정
/*
    - 핸들, 페달, 엔진, 문, 전기선, 휘발유
    구매자 입장에서 사용 : 핸들, 페달, 문
    몰라도 되는 부분 : 엔진, 전기선, 휘발유
*/

// 접근 지정자
/*
    public 
    protected
    private
*/
class Car{
public:
    void MoveHandle(){}
    void PushPedat(){}
    void OpenDoor(){}
    void TurnKey(){
        // 차 키를 돌리면
        putFuelInEngine(); // 밖에서는 마음대로 쓰면 안된다.
    }

private: // 부모 클래스에서 정의한거고 밖에서 못 쓰게 했으니 자식 클래스에도 물려주지 못함.
    // 몰라도 되는 부분 - 주로 소문자로 함수를 설정하는 경우도 있음.
    void disassemble(){} // 차를 분해한다?
    void putFuelInEngine(){}

protected: // 부모 클래스와 자식 클래스에는 물려줌.
    void connectCircuit(){}

public:
    // 핸들
    // 페달
    // 엔진
    // 문
    // 전기선
};

class SuperCar : public Car{
public:
    void Test(){
        MoveHandle();
        // disassemble(); 사용 불가
        connectCircuit();
    }
};

// 상속 접근 지정자 : 다음 세대한테 부모한테 받은 유산을 상속할 것인가? - 잘 안 씀
/*
    - public : 공개 상속
    - protected : 보호받는 상속 - 내 자식들에게만 물려줌 (public -> protected)
    - private : 아무도 못 씀 (public, protected -> private)
*/
class UltraSuperCar : private Car{
public:
    void Test(){
        MoveHandle();
    }
};
class SuperUltraCar : public UltraSuperCar{
public:
    void Test(){
        // MoveHandle(); UltraSuperCar가 Car의 유산을 private로 돌려서 물려 받지 못함
    }
};

class Knight{
public:
    void SetHp(int hp){ // 이걸 사용하는 모든 함수에서 적용 가능. 엄청난 효율
        _hp = hp;
        if(_hp <= 50){
            // TODO
        }
    }
    int GetHp(){
        return _hp;
    }

private:
    int _hp = 100; // 이 변수는 다른 곳에서 함부로 바꾸는건 위험함.
};

int main(){
    Car c;
    // c.Disassemble(); // 다른 곳에서 분해를 시킬 수 있으면 안됨.
    Knight k1;
    k1.SetHp(100);
}