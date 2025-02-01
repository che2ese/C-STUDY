#include <iostream>
using namespace std;

struct StatInfo // 메모리 중 데이터 영역에 존재
{
    int hp;
    int attack;
    int defence;
};
// 1. 값(복사) 전달 방식 - 메모리를 복사하기 때문에 값이 많아지면 문제가 생김
void PrintByCopy(StatInfo player){
    cout << "----------------------" << endl;
    cout << "Hp : " << player.hp << endl;
    cout << "Att : " << player.attack << endl;
    cout << "Def : " << player.defence << endl;
    cout << "----------------------" << endl;
}
// 2. 주소 전달 방식
void PrintByPointer(StatInfo* player){
    cout << "----------------------" << endl;
    cout << "Hp : " << player->hp << endl;
    cout << "Att : " << player->attack << endl;
    cout << "Def : " << player->defence << endl;
    cout << "----------------------" << endl;
}
// 3. 참조 전달 방식 - 포인터처럼 귀찮게 쓰지 않아도 되고 메모리 비용도 많이 들지 않음.
void PrintByReference(const StatInfo& player){ // 복사 비용을 아끼면서 원본을 건들지 않음.
    cout << "----------------------" << endl;
    cout << "Hp : " << player.hp << endl;
    cout << "Att : " << player.attack << endl;
    cout << "Def : " << player.defence << endl;
    cout << "----------------------" << endl;
}
#define OUT
void PrintByRef(OUT StatInfo& player){ // const랑 같은 기능.
    cout << "----------------------" << endl;
    cout << "Hp : " << player.hp << endl;
    cout << "Att : " << player.attack << endl;
    cout << "Def : " << player.defence << endl;
    cout << "----------------------" << endl;
}
int main(){
    StatInfo player = {100, 10, 1};
    PrintByCopy(player);
    PrintByPointer(&player);

    StatInfo* ptr = &player;
    StatInfo& ref = player; // 포인터처럼 주소를 이용하지만 기능은 복사랑 비슷함. 하지만 항상 값을 지정해줘야됨. 비워둘 수 없음.
    PrintByReference(player); // 원본을 건드리기 때문에 조심해야됨. 그래서 값을 변경하지 못하게 const를 붙여주는게 좋음.
    PrintByRef(OUT player);
}