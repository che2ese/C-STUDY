#include <iostream>
using namespace std;

// 연산자 오버로딩
/*
 - 멤버 연산자 함수 버전
 - - a operator b 형태에서 왼쪽을 기준으로 실행

 - 전역 연산자 함수 버전
 - - a operator b, a/b 모두를 연산자 함수의 피연산자로 사용
*/

class Pos{
public:
    Pos(){

    }
    explicit Pos(int b){ // 습관
        x = b;
        y = b;
    }
    Pos operator+(const Pos& other){
        Pos pos;
        pos.x = x + other.x;
        pos.y = y + other.y;
        return pos;
    }
    Pos operator+(int b){
        Pos pos;
        pos.x = x + b;
        pos.y = y + b;
        return pos;
    }
    bool operator==(const Pos& b){
        return x == b.x && y == b.y;
    }
    // 대입 연산자
    void operator=(int b){
        x = b;
        y = b;
    }

public:
    int x = 0;
    int y = 0;
};

Pos operator+(int a, const Pos& b){
    Pos pos;
    pos.x = a + b.x;
    pos.y = a + b.y;
    return pos;
}

int main(){
    Pos pos1;
    Pos pos2;

    Pos pos3 = pos1 + pos2;
    Pos pos4 = pos1 + 10;
    // pos3 = pos1.operator+(pos2);

    Pos pos5 = 10 + pos1;

    // 대입
    Pos pos6;
    pos6 = 100;

    // 생성자
    Pos pos7(10);
}