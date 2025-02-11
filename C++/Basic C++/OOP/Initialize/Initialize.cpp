#include <iostream>
using namespace std;

class Player{
public:
    Player()
    {
        cout << "Player()" << endl;
    }
    ~Player()
    {
        cout << "~Player()" << endl;
    }
public:
};

class Inventory{
public:
    Inventory()
    {
        cout << "Inventory()" << endl;
    }
    ~Inventory()
    {
        cout << "~Inventory()" << endl;
    }

public:
    int _a;
};

class Knight : public Player{
public:
    Knight() : _hp(0) // hp값 초기화
    /*
        선처리 영역
        Player()
    */
    {
        cout << "Knight()" << endl;
    }
    ~Knight()
    {
        cout << "~Knight()" << endl;
    }

public:
    int _hp;
    Inventory _inventory; // 생성될 때 inventory 메모리 영역까지 생성
};

int main(){
    Knight k1;
}