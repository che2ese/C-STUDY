#include <iostream>
using namespace std;

// 캐스팅 4총사
/*
 - static_cast
 - dynamic_cast
 - const_cast
 - reinterpret_cast
*/

class Player
{
public:
    virtual ~Player() {}
};

class Knight : public Player
{
public:
    virtual ~Knight() {}
};

class Dog
{

};

int main()
{
    /* 어떻게 보면 위험
     - static_cast : 타입 원칙에 비춰볼 때 상식적인 캐스팅만 허용
     ex) 
        1. int <-> float
        2. Player* -> Knight*
    */
   int hp = 100;
   int maxHp = 200;
   // float ratio = (float)hp / maxHp;
   float ratio = static_cast<float>(hp) / maxHp; // 둘 중 하나만 float로 변환해도 됨.

   Knight* k = new Knight();
   Player* p = k; // 자식이 부모가 되는건 가능.

   // Knight* k2 = (Knight*)p;
   Knight* k2 = static_cast<Knight*>(p);

   /* 안전함
     - dynamic_cast : 상속 관계에서의 안전 변환
     다형성을 활용하는 방식 (하나라도 virtual함수 있어야 함)
     RTTI (RunTime Type Information)

     - 원본 객체가 Knight 타입이면 전환해주지만 아니면 null로 밀어버림.
     따라서 원복 객체 확인 가능한 casting 
    */
   Knight* k3 = dynamic_cast<Knight*>(p);
   if (k3 != nullptr)
   {
        // 원본 객체가 기사였네?
   }

   /* 거의 안씀
     - const_cast : const 전환
    */
   const char* name = "Minseong";
   char* name2 = const_cast<char*>(name);

    /* 위험하고 강력함
     - reinterpret_cast :  포인터 -> 전혀 관계 없는 다른 타입 변환
    */
   // Dog* dog = (Dog*)k;
   Dog* dog = reinterpret_cast<Dog*>(k);
}