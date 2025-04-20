#include <iostream>
using namespace std;

void Print()
{
    cout << "Hello World" << endl;
}
int Add(int a, int b)
{
    return a + b;
}

// 함수 포인터를 사용하는 예

// 콜백 함수
/*
    ex) 
        UI
        온라인 게임
            클라1 -> 나 10(변수)번 유저 공격(함수)할래
            클라2 -> 나 10, 20(변수, 변수) 좌표로 이동(함수)할래 - 좌표가 계속 변한다면 그 값을 바인딩 못함 -> 함수 객체로 해결
        키보드 입력 (사용자가 방향키를 바꾸는 경우)
*/

// 행동 자체를 인자로 넘기고 싶을 때
/*
    ex)
        using FuncType = int(*)(int a, int b);
        
        int DoSomething(int a, int b, FuncType func)
        {
            return func(a, b); 
        }
*/

// 희귀도가 1인 아이템 찾기 (2,3,4인 아이템 찾기 이런거 할 때마다 코드 새로 쓰기 귀찮아짐)
class Item
{
public:

public:
    int _itemId = 0;
    int _rarity = 0;
    int _ownderId = 0;
};

using ItemSelectorType = bool(*)(Item* item);

Item* FindItem(Item items[], int itemCount, ItemSelectorType selector)
{
    for (int i = 0; i < itemCount; i++)
    {
        Item* item = &items[i];
        if (selector(item))
            return item;
    }
    return nullptr;
}

bool IsRare(Item* item)
{
    return item->_rarity == 1;
}

// 멤버 함수 포인터 - 클래스 안에 있는 함수 (일반 전역/정적 함수랑 다름)
class Test
{
public:
    void PrintTest(){ };
};

int main()
{
    // 거의 안씀
    using FuncType = void();
    FuncType* ptr = &Print;
    ptr();

    // 거의 안씀
    using FuncIntType =  int(int, int);
    FuncIntType* intPtr = &Add;
    cout << intPtr(10, 20) << endl;

    // 대부분 이렇게 씀
    using FuncPtrType = void(*)();
    FuncPtrType funcPtr = &Print;
    funcPtr();

    // 클래스에서 사용
    Item items[10];
    items[3]._rarity = 1;

    FindItem(items, 10, IsRare);

    // 멤버 함수 포인터 - 일반적인 호출 불가능
    using MFuncPtrType = void(Test::*)();
    MFuncPtrType func = &Test::PrintTest;

    // 함수 호출을 늦출 수 있음
    Test t;
    (t.*func)();
}
