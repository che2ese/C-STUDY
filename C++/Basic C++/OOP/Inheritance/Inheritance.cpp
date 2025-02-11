#include <iostream>
using namespace std;

// OOP의 3대 요소
/*
    - 상속성 << inheritance
    - 은닉성
    - 다형성
*/

// 상속성

// 일반적인 게임의 계층 구조
/*
    GameObject
    - Creature
    - - Player, Monster, Npc, Pet;
    - Projectile
    - - Arrow, FireBall
    - Env // 길 다니면서 줍는 아이템
*/

// 아이템 계층 구조
/*
    Item
    - Weapon
    - - Sword, Bow, Lance
    - Armor
    - - Helmet, Boots, Armor, Glove
    - Consumable
    - - Potion, Scroll 
*/ 
class Player{
public:
    void Move(){}
    void Attack(){}
    void Die(){}

public:
    int _type;
    int _hp;
    int _attack;
    int _defence;
};

class Knight : public Player{

};
class Archer : public Player{
public:

public:
    int _arrowCount;
};
class Mage : public Player{
public:

public:
    int _mp;
};

void Fight(Player* p1, Player* p2){
    (Knight*) p1; // knight 로 형변환
    p1->_hp -= p2->_attack;
}

int main(){
    Knight k1;
    k1._hp = 100;
    Mage m1;
    m1._mp = 10;

    Player* p1 = &k1; // k1의 주소값을 가리키는 포인터
    Player* p2 = &m1;

    Fight(&k1, &m1);
}




// 이런식으로 쓰면 비효율적임.

/*
class Knight{
public:
    void Move(){}   
    void Attack(){}
    void Die(){}

public:
    int _hp;
    int _attack;
    int _defence;
};

void Fight(Knight& k1, Knight& k2){
    // 기사끼리 싸우는 코드이므로 3가지 캐릭터면 3 x 3 해서 9 개의 함수를 만들어야됨... 비효율적!
}

class Archer{
public:
    void Move(){}
    void Attack(){}
    void Die(){}

public:
    int _hp;
    int _attack;
    int _defence;
    int _arrowCount;
};

class Mage{
public:
    void Move(){}
    void Attack(){}
    void Die(){}

public:
    int _hp;
    int _attack;
    int _defence;
    int _mp;
};
*/