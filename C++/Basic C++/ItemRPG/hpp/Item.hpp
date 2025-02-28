#pragma once

#include <iostream>
#include "Enums.hpp"
using namespace std;

/* 
Item
 - weapon
 - armor
 - consumable
*/

// **************************
//           Item
// **************************

class Item // 제일 위의 부모클래스는 공통으로 쓰는 것만 사용
{
protected:
    // Item();
    Item(ItemType itemType);

public:
    virtual ~Item(); // 부모 클래스의 소멸자는 항상 virtual 붙이기

public:
    virtual void PrintInfo();
    ItemType GetItemType() { return _itemType; }
    ItemRarity GetItemRarity() { return _rarity; }

protected: // 자식은 이용 가능
    int _itemId;
    int _itemCount;
    ItemRarity _rarity = IR_NORMAL;
    ItemType _itemType = IT_NONE;
};

// **************************
//           Weapon
// **************************

class Weapon : public Item // 부모가 물려준거 똑같이 물려주겠다.
{
public:
    Weapon();
    virtual ~Weapon();

    virtual void PrintInfo() override;
    
    void SetDamage(int damage) { _damage = damage; }
    int GetDamage() {return _damage; }

private:
    int _damage; // OOP 3대 요소 - 은닉성 이용해서 직접 접근 금지
};

// **************************
//           Armor
// **************************

class Armor : public Item // 부모가 물려준거 똑같이 물려주겠다.
{
public:
    Armor();
    virtual ~Armor();

    virtual void PrintInfo() override;
    
    void SetDefence(int defence) { _defence = defence; }
    int GetDefence() {return _defence; }

private:
    int _defence;
};