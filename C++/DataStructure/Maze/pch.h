#pragma once

#include "Types.h"
#include <Windows.h>
#include <iostream>

using namespace std;

// 2D 좌표를 나타내는 구조체
struct Pos
{
    // 기본 생성자: y와 x는 0으로 초기화 (int32 y = 0, x = 0 덕분)
    Pos() { }

    // 사용자 정의 생성자: y, x 값을 받아 초기화
    Pos(int32 y, int32 x) : y(y), x(x) { }

    // == 연산자 오버로딩: 두 좌표가 같으면 true 반환
    /*
        const Pos& 사용 목적:
        참조(&): 불필요한 복사 방지로 성능 최적화.
        const: 함수 내에서 매개변수를 수정하지 않도록 보장(안전성).

        C++에서 객체나 구조체를 인자로 받을 때 거의 필수적인 습관
    */
    bool operator==(const Pos& other)
    {
        return y == other.y && x == other.x;
    }

    // != 연산자 오버로딩: 좌표가 다르면 true 반환
    bool operator!=(const Pos& other)
    {
        return !(*this == other);  // == 연산자 결과를 반전
    }

    // + 연산자 오버로딩: 두 Pos 객체의 좌표를 더한 결과를 새로운 Pos로 반환
    Pos operator+(const Pos& other)
    {
        Pos ret;
        ret.y = y + other.y;
        ret.x = x + other.x;
        return ret;
    }

    // += 연산자 오버로딩: 현재 Pos에 다른 Pos의 좌표를 더한 후 자기 자신을 반환
    Pos& operator+=(const Pos& other)
    {
        y += other.y;
        x += other.x;
        return *this;  // 자기 자신을 참조로 반환 -> pos1 += pos2 += pos3 같은 체이닝 가능
    }

    int32 y = 0;  // 세로 좌표, 기본값 0
    int32 x = 0;  // 가로 좌표, 기본값 0
};

enum Dir
{
    DIR_UP = 0,
    DIR_LEFT = 1,
    DIR_DOWN = 2,
    DIR_RIGHT = 3,

    // 최대값을 만들면 루프 돌리기가 쉬움.
    DIR_COUNT = 4,
};