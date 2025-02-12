#include <iostream>
using namespace std;

// class vs struct
// class는 일반적으로 public을 선언하지 않으면 private으로 작동함.
// 나머지는 별 차이 없지만 그래도 struct는 보통 데이터들을 이용할 때 씀.

struct Knight1
{
    /* data */
    int hp;
};

class Knight2{
public:
    int hp;
};

int main(){
    Knight1 k1;
    k1.hp = 10;
    Knight2 k2;
    k2.hp = 10;
}
