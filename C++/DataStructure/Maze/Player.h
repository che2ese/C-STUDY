#pragma once
#include "Vector.h"

// 전방 선언: Board 클래스는 이 파일에서 정의되지 않지만,
// Player 클래스 내부에서 Board 객체를 포인터로 사용하므로 전방 선언이 필요합니다.
class Board;

class Player
{
    enum
    {
        // 0.1초 단위로 실행
        MOVE_TICK = 100,
    };

public:
    // 초기화 함수: Player 객체가 초기화될 때 Board 객체를 참조하기 위해 포인터를 전달받습니다.
    void Init(Board* board);
    void Update(uint64 deltaTick);

    // 플레이어의 위치를 설정하는 함수.
    // pos: 설정할 위치
    void SetPos(Pos pos) { _pos = pos; }

    // 플레이어의 현재 위치를 반환하는 함수.
    // 반환 값: 현재 플레이어의 위치
    Pos GetPos() { return _pos; }

    bool CanGo(Pos pos);

private:
    // 경로 계산 함수: 플레이어가 이동할 경로를 계산하는 함수입니다.
    void CaculatePath();

private:
    // 멤버 변수들
    Pos _pos;               // 플레이어의 위치를 나타내는 변수
    int32 _dir = DIR_UP;    // 플레이어의 방향을 나타내는 변수 (기본값: 위쪽)
    Board* _board = nullptr; // 플레이어가 참조하는 Board 객체의 포인터

    // 동적 배열
    Vector<Pos> _path;
    int32 _pathIndex = 0;
    uint64 _sumTick = 0;
};