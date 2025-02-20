#include <iostream>
using namespace std;

// 동적 할당
/*
데이터 영역과 스택 영역에 할당되는 메모리의 크기는 컴파일 타임(Compile time)에 미리 결정됩니다. 
그러나 힙 영역의 크기는 프로그램이 실행 도중인 런 타임(Run time) 에 사용자가 직접 결정합니다. 
런 타임에 메모리를 할당 받는 것을 메모리의 동적 할당 이라고 합니다.
*/

class Monster
{
public:
    Monster() : _hp(0)  // 기본 생성자: _hp를 0으로 초기화
    {
        cout << "Monster()" << endl;
    }
    ~Monster()
    {
        cout << "~Monster()" << endl;
    }

public:
    int _hp;  // 몬스터의 HP
};

int main(){
    // malloc + free -> 생성자 소멸자 호출 안됨
    void* ptr = malloc(1000);
    Monster* m = (Monster*)ptr;
    m->_hp = 100;
    free(ptr);

    // new + delete -> 생성자 소멸자 호출
    Monster* m1 = new Monster(); // 메모리 할당하고 주소 지정
    m1->_hp = 100;
    delete m1;

    m1 = nullptr; // delete 후 사용하지 않게 메모리 주소값 삭제. 그럼 밑의 경우 crash 발생.

    // Use-After-Free
    // m1->_hp = 200; // delete하고 사용하면 그 주소에 해당하는 메모리가 사라지는건 아님.
}