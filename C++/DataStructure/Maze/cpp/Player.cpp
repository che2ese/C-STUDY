#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	CaculatePath();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;

	// 0.1초
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		// 이동
		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::CaculatePath()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// 목적지
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos(-1, 0),
		Pos(0, -1),
		Pos(1, 0),
		Pos(0, 1),
	};

	// 바라보는 방향 기준 앞에 있는 좌표
	Pos next = pos + front[_dir];

	// 오른쪽 / 왼쪽 90도 회전
	_dir = (_dir - 1) % DIR_COUNT;
	// _dir = (_dir + 1) % DIR_COUNT;

	// 목적지 찾을 때까지
	while (pos != dest)
	{
		// 1. 현재 바라보는 방향 기준으로, 오른쪽으로 갈 수 있는지 확인.
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			// 오른쪽 방향 회전
			_dir = newDir;
			// 앞으로 한 칸 전진
			pos += front[_dir];
			// 좌표 기록
			_path.push_back(pos);
		}
		// 2. 현재 바라보는 방향을 기준으로 전진할 수 있는지 확인.
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 칸 전진
			pos += front[_dir];
			// 좌표 기록
			_path.push_back(pos);
		}
		else
		{
			// 왼쪽 방향 회전
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}
}
