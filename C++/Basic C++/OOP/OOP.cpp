#include <iostream>
using namespace std;

// 설계도
class Knight{
public:
    // 기본 생성자 - Knight가 선언될 때 무조건 생성 - 초기값 생성할 때 유용, 변수 초기화 안하면 쓰레기값 출력
    Knight(){
        _hp = 0;
        _attack = 0;
        _defence = 0;
        cout << "Knight()" << endl;
    }
    // 복사 생성자
    Knight(const Knight& other){
        this->_hp = other._hp;
        this->_attack = other._attack;
        this->_defence = other._defence;
        cout << "Knight()" << endl;
    }
    // 기타 생성자 - 변수를 미리 받아줌, 바로 사용 가능
    Knight(int hp, int attack, int defence){
        // 멤버 변수를 이 생성자에 넣음. this - 내 자신을 가리킴
        this->_hp = hp;
        this->_attack = attack;
        this->_defence = defence;
        cout << "Knight()" << endl;
    }
    // 소멸자 - Knight가 소멸될 떄 무조건 생성 - 정리할 때 유용 (특히 메모리 누수 예방)
    ~Knight(){
        cout << "~Knight()" << endl;
    }
    // 멤버 함수 - 메모리에서 코드 영역에 들어감. - 메모리에 영향이 없음
    void Attack(){
        cout << "Attack" << endl;
    }
    void Die(){
        cout << "Die" << endl;
    }
    void HealMe(int value){ // 클래스 밖 HealMe 함수랑 동일한 코드 - 자기 자신이니까 this로 주소 불러오기
    // this->_hp += 10;
        _hp += 10; // 밑의 변수를 가져다 쓸 수 있음
    }

public:
    // 멤버 변수 - 멤버 변수일 때 변수를 다르게 표현하는게 좋음 ex) _, m_
    int _hp;
    int _attack;
    int _defence;
};

void HealMe(Knight* thisPtr, int value){
    thisPtr->_hp += value;
}

int main(){
    // 객체 인스턴스
    Knight k1; // 스택 영역에 복사
    Knight k2(100, 10, 1); // 기타 생성자
    Knight k3(k2); // 복사 생성자 

    cout << k2._hp << endl;
    
    k1._hp = 100;
    k1._attack = 10;
    k1._defence = 1;
    k1.Attack();
    k1.Die();
}