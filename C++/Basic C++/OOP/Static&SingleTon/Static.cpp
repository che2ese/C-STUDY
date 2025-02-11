#include <iostream>
using namespace std;

// static
// 
class Marine{
public:
    void TakeDamage(int damage){
        hp -= damage;
    }

public:
    // 특정 마린 객체와 연관
    int hp = 40;

    // 특정 마린 객체와 무관
    static int attack; // 공격력은 다 같은데 복사할 때마다 메모리 잡아먹음. static을 사용하면 밖에서 따로 저장됨.
};

int Marine::attack = 6; // 따로 초기화해야됨. 모든 marine이 사용하는 공공재.

int main(){
    Marine m1;
    m1.hp = 40;

    Marine m2;
    m2.hp = 10;

    Marine::attack = 7;
}