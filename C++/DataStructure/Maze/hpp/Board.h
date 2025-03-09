#pragma once
#include "ConsoleHelper.h"

enum // 상수 만들 때도 쓰기 좋음
{
	BOARD_MAX_SIZE = 100
};

enum class TileType
{
	NONE = 0,
	EMPTY,
	WALL,
};

class Player;

class Board
{
public:
	Board();
	~Board();

	void Init(int32 size, Player* player);
	void Render();

	void GenerateMap();
	// GetTileType 에서 x, y 값을 가지고 사칙연산을 이용해야 됨.
	// 따라서 연산자 오버로딩 만들기
	TileType GetTileType(Pos pos);
	ConsoleColor GetTileColor(Pos pos);

	Pos GetEnterPos() { return Pos(1, 1); }
	Pos GetExitPos() { return Pos(_size - 2, _size - 2); }

private:
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE]; // 최대 크기
	int32 _size = 0; // 실제 사용하는 맵 크기
	// board 에서 player 사용.
	Player* _player = nullptr;
};

