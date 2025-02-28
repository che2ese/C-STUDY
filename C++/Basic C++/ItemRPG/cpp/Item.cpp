#include "../hpp/Item.hpp"
#include <iostream>
using namespace std;

// **************************
//           Item
// **************************

Item::Item(ItemType itemType)
    : _itemId(0), _itemCount(0), _itemType(itemType)
{
    int randValue = rand() % 100;

    if(randValue < 50)
    {
        _rarity = IR_NORMAL;
    }
    else if(randValue < 80)
    {
        _rarity = IR_RARE;
    }
    else
    {
        _rarity = IR_UNIQUE;
    }
}
Item::~Item()
{

}

void Item::PrintInfo()
{
    switch (_rarity)
    {
    case IR_NORMAL:
        cout << "[희귀도] 일반" << endl;
        break;
    case IR_RARE:
        cout << "[희귀도] 레어" << endl;
        break;
    case IR_UNIQUE:
        cout << "[희귀도] 유니크" << endl;
        break;
    }
}

// **************************
//           Weapon
// **************************

Weapon::Weapon() : Item(IT_WEAPON), _damage(0)
// 생성될 때 부모의 생성자도 생성
{   
    switch (_rarity)
    {
    case IR_NORMAL:
        _damage = 5 * (rand() % 5 + 1);
        break;
    case IR_RARE:
        _damage = 10 * (rand() % 20 + 1);
        break;
    case IR_UNIQUE:
        _damage = 50 * (rand() % 40 + 1);
        break;
    }
}
Weapon::~Weapon()
{

}

void Weapon::PrintInfo()
{
    cout << "*****************" << endl;
    cout << "[아이템 타입] : 무기" << endl;
    cout << "[공격력] : " << _damage << endl;
    Item::PrintInfo();
    cout << "*****************" << endl;
}

// **************************
//           Armor
// **************************

Armor::Armor() : Item(IT_ARMOR), _defence(0)
{
    switch (_rarity)
    {
    case IR_NORMAL:
        _defence = 3 * (rand() % 10 + 1);
        break;
    case IR_RARE:
        _defence = 7 * (rand() % 20 + 1);
        break;
    case IR_UNIQUE:
        _defence = 15 * (rand() % 30 + 1);
        break;
    }
}
Armor::~Armor()
{

}

void Armor::PrintInfo()
{
    cout << "*****************" << endl;
    cout << "[아이템 타입] : 방어구" << endl;
    cout << "[방어력] : " << _defence << endl;
    Item::PrintInfo();
    cout << "*****************" << endl;
}