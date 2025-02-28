#include "Item.hpp"
#include "Inventory.hpp"

// [시스템] 몬스터를 잡으면 아이템을 떨군다.
Item* DropItem()
{
    if(rand() % 2 == 0)
    {
        Weapon* weapon = new Weapon();
        return weapon;
    }
    else
    {
        Armor* armor = new Armor();
        return armor;
    }
}

int main()
{
    srand((unsigned)time(0)); // 랜덤 쓸 때 꼭 쓰기

    for(int i = 0; i < 100; i++)
    {
        Item* item = DropItem(); // 가상함수를 써서 자신의 객체 파악
        item->PrintInfo(); 

        if (Inventory::GetInstance()->AddItem(item))
        {
            cout << "Added Item To Inven" << endl;
        }
        else
        {
            cout << "Failed To Add Item" << endl;
            delete item;
        }
    }

    // 랜덤으로 일부 아이템 드랍.
    for (int i = 0; i < 20; i++)
    {
        int randIndex = rand() % MAX_SLOT;
        Item* item = Inventory::GetInstance()->GetItemAtSlot(randIndex);
        if (item != nullptr)
        {
            if (Inventory::GetInstance()->RemoveItem(item))
            {
                ItemType itemType = item->GetItemType();
                ItemRarity itemRarity = item->GetItemRarity();

                switch(itemRarity)
                {
                    case 0:
                        cout << "일반 ";
                        break;
                    case 1:
                        cout << "레어 ";
                        break;
                    case 2:
                        cout << "유니크 ";
                        break;
                }
        
                if (itemType == IT_WEAPON) // 타입 변환 (캐스팅)
                {
                    Weapon* weapon = (Weapon*)item;
                    cout << "무기 드랍" << " 공격력 : " << weapon->GetDamage() << endl;
                }
                else if (itemType == IT_ARMOR)
                {
                    Armor* armor = (Armor*)item;
                    cout << "방어구 드랍" << " 방어력 : "  << armor->GetDefence() << endl;
                }
            }
        }
    }
}