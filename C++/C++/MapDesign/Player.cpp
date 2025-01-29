#include "Player.h"
#include "Map.h"
#include "Helper.h"

int GPlayerX = 2;
int GPlayerY = 2;

bool canMove = true;

void HandleMove() {
	// Ű���带 ����, ���� ���� ������ �� �ִ�.
	if (GMoveDir == MD_NONE) {
		canMove = true;
		return;
	}

	// ������ �� �ִ��� �Ǵ�
	// false �� �ٽ� ����
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
	// ���� üũ
	if (x < 0 || x >= MAP_SIZE)
		return;
	if (y < 0 || y >= MAP_SIZE)
		return;

	// �� üũ
	// y�� 1 �þ�°� x�� MAP_SIZE ��ŭ �þ�°�
	int index = y * MAP_SIZE + x;
	if (GMap1D[index] == 1) // ��
		return;

	if (GMap2D[y][x] == 1) // ��
		return;

	// �̵�
	// ���� ��ġ ����
	// index - ��ȣ �ȿ����� �����ϴ� ��������
	{
		int index = GPlayerY * MAP_SIZE + GPlayerX;
		GMap1D[index] = 0;

		GMap2D[GPlayerY][GPlayerX] = 0;
	}

	// �� ��ġ �̵�
	{
		GPlayerX = x;
		GPlayerY = y;
		int index = GPlayerY * MAP_SIZE + GPlayerX;
		GMap1D[index] = 2;

		GMap2D[GPlayerY][GPlayerX] = 2;
	}
}
