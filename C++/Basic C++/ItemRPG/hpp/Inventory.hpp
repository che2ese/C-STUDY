/*
#include "Item.hpp"
생각보다 무거운 작업.
hpp파일에는 class로 전방 선언하고 
cpp파일에 다시 include 선언
*/

enum
{
    MAX_SLOT = 100
};

class Item;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    bool AddItem(Item* item);
    bool RemoveItem(Item* item);

    Item* GetItemAtSlot(int slot);

    // 싱글톤
    static Inventory* GetInstance();

    void Clear();

private:
    int FindEmptySlot();
    int FindItemSlot(Item* item);
        
private:
    // Item _items[MAX_SLOT]; - 컴파일시 아이템의 변수대로 메모리 미리 생성. 따라서 추가 어려움.
    Item* _items[MAX_SLOT];
    int _itemCount = 0;

    // 싱글톤
    static Inventory* s_instance;
};  
