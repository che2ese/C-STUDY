#include "Player.h"
#include "Map.h"
#include "Helper.h"

int GPlayerX = 2;
int GPlayerY = 2;

bool canMove = true;

void HandleMove() {
	// 키보드를 떼야, 다음 번에 움직일 수 있다.
	if (GMoveDir == MD_NONE) {
		canMove = true;
		return;
	}

	// 움직일 수 있는지 판단
	// false 면 다시 위로
	if (canMove == false)
		return;

	canMove = false;

	switch (GMoveDir)
	{
	case MD_LEFT:
		MovePlayer(GPlayerX - 1, GPlayerY);
		break;
	case MD_RIGHT:
		MovePlayer(GPlayerX + 1, GPlayerY);
		break;
	case MD_UP:
		MovePlayer(GPlayerX, GPlayerY - 1);
		break;
	case MD_DOWN:
		MovePlayer(GPlayerX, GPlayerY + 1);
		break;
	}
}

void MovePlayer(int x, int y) {
	// 범위 체크
	if (x < 0 || x >= MAP_SIZE)
		return;
	if (y < 0 || y >= MAP_SIZE)
		return;

	// 벽 체크
	// y가 1 늘어나는건 x가 MAP_SIZE 만큼 늘어나는거
	int index = y * MAP_SIZE + x;
	if (GMap1D[index] == 1) // 벽
		return;

	if (GMap2D[y][x] == 1) // 벽
		return;

	// 이동
	// 기존 위치 정리
	// index - 괄호 안에서만 존재하는 지역변수
	{
		int index = GPlayerY * MAP_SIZE + GPlayerX;
		GMap1D[index] = 0;

		GMap2D[GPlayerY][GPlayerX] = 0;
	}

	// 새 위치 이동
	{
		GPlayerX = x;
		GPlayerY = y;
		int index = GPlayerY * MAP_SIZE + GPlayerX;
		GMap1D[index] = 2;

		GMap2D[GPlayerY][GPlayerX] = 2;
	}
}
