#define _CRT_SECURE_NO_WARNINGS

#include "TetrisHelper.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define GRID_WIDTH  15
#define GRID_HEIGHT  20
#define USERBLOCK_SIZE 3

int displayData[GRID_HEIGHT][GRID_WIDTH] = { 0, };

class Display {
public:
	void draw() {
		for (int i = 0; i < GRID_HEIGHT; i++) {
			for (int k = 0; k < GRID_WIDTH; k++) {
				if (displayData[i][k] == 0) {
					drawPosition(k, i, false);
				}
				else {
					drawPosition(k, i, true);
				}
			}
		}
	}
};

class GameEngine {
public:
	enum class GameState {
		PLAYING, GAMEOVER
	};
	GameState state = GameState::PLAYING;

	int gameGridData[GRID_HEIGHT][GRID_WIDTH] = { 0, };
	int userBlock[USERBLOCK_SIZE][USERBLOCK_SIZE] = { 0, };

	int userBlockVarious[4][USERBLOCK_SIZE][USERBLOCK_SIZE] = {
		{
			{0,1,0},
			{0,1,0},
			{0,1,0},
		},
		{
			{0,0,0},
			{1,1,1},
			{0,1,0}
		},
		{
			{1,1,1},
			{1,1,1},
			{1,1,1},
		},
		{
			{0,0,0},
			{1,1,0},
			{0,1,1}
		}

	};

	int point = 0;

	int blockX = 0;
	int blockY = 0;
	
	float elapsed = 0.0f; // ����� �ʹ� ���� �������°� ����
	float controlCheck = 0.0f;

	void init() {
		// ���� ���� �ʱ�ȭ
		makeUserBlock();
	}
	
	// next�� while �������� �Ź� �ҷ����� �Լ�
	void next(float dt, char keyboardInput) {
		if (state == GameState::GAMEOVER) return;
		elapsed += dt;
		if (elapsed >= 0.5f) {
			if (canGoDown()) {
				blockY++;
			}
			else {
				// userblock�� gamegridData�� �ٲ���
				trans();
				if (gameOverDecision()) state = GameState::GAMEOVER;
			}
			elapsed -= 0.5f;
		}
		
		controlCheck += dt;

		if (keyboardInput == 'a' && canGoLeft() && controlCheck > 0.1) {
			blockX--;
			controlCheck = 0.0f;
		}
		if (keyboardInput == 'd' && canGoRight() && controlCheck > 0.1) {
			blockX++;
			controlCheck = 0.0f;
		}
		if (keyboardInput == 's' && canGoDown() && controlCheck > 0.1) {
			blockY++;
			controlCheck = 0.0f;
		}
	}

	// ����� �Ʒ��� �� �� �ִ���
	bool canGoDown() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (userBlock[i][k] == 1 && i + blockY + 1 >= GRID_HEIGHT) {
					return false;			// block�� �� ���̸� ������� �Ǵ��ϴ� �ڵ�
				}
				if (userBlock[i][k] == 1 && gameGridData[i+blockY+1][k+blockX] == 1) { 
					return false;						// i+blockY�� userblock�� ���� �ؿ� �ִ� ĭ
				}                                       // ���� �� ĭ�� �ؿ� ���� �ִ��� �Ǵ��ϴ� �ڵ�
			}
		}
		return true; // �� �ΰ��� ���ǿ� �ɸ��� ������ ��� ����
	}

	bool canGoLeft() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (userBlock[i][k] == 1 && k + blockX - 1 < 0) {
					return false;
				}
				if (userBlock[i][k] == 1 && gameGridData[i + blockY][k + blockX - 1] == 1) {
					return false;
				}
			}
		}
		return true;
	}

	bool canGoRight() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (userBlock[i][k] == 1 && k + blockX + 2 > GRID_WIDTH) {
					return false;
				}
				if (userBlock[i][k] == 1 && gameGridData[i + blockY][k + blockX + 1] == 1) {
					return false;
				}
			}
		}
		return true;
	}

	// �� ���� ä������ Ȯ��
	bool isLineFilled(int y) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			if (gameGridData[y][i] == 0) return false; // y��°�� ���� ���� �� �ִ��� Ȯ��
		}
		point += 10;
		return true;
	}

	// �� ���� ���� ����
	void eraseLine(int y) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			gameGridData[y][i] = 0;
		}
	}

	// �� �پ� ����
	void drop(int y) {
		for (int i = y; i >= 0; i--) { // y��ǥ���� ������ �ϱ� ������ i = y ���
			for (int k = 0; k < GRID_WIDTH; k++) {
				gameGridData[i][k] = i - 1 < 0 ? 0 : gameGridData[i - 1][k];
			}
		}
	}

	void trans() { // userblock�� gamegridData�� �ٲ��ִ� �Լ�
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				gameGridData[i + blockY][k + blockX] = userBlock[i][k] == 1 ? userBlock[i][k] : gameGridData[i + blockY][k + blockX];
			}
		}

		for (int i = 0; i < GRID_HEIGHT; i++) {
			if (isLineFilled(i)) {
				eraseLine(i);
				drop(i);
			}
		}
		// ���ο� ��� ����
		makeUserBlock();
	}

	bool gameOverDecision() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (userBlock[i][k] == 1 && gameGridData[i + blockY][k + blockX] == 1) {
					return true;
				}
			}
		}
		return false;
	}

	void makeUserBlock() { // �������� ���ο� ��� ����
		blockX = GRID_WIDTH / 2 - USERBLOCK_SIZE / 2;
		blockY = 0;

		srand(time(0));

		int various = rand() % 4;
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				userBlock[i][k] = userBlockVarious[various][i][k];
			}
		}
	}

	void rotate() {
		int tmp[USERBLOCK_SIZE][USERBLOCK_SIZE] = { 0, };
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				tmp[i][k] = userBlock[USERBLOCK_SIZE - k - 1][i];
			}
		}
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				userBlock[i][k] = tmp[i][k];
			}
		}
	}
	// ���� ���� �����͸� ȭ�鿡 ����� �� �ִ� �����ͷ� �ٲ��ִ� �Լ�
	void makeDisplayData() {
		for (int i = 0; i < GRID_HEIGHT; i++) {
			for (int k = 0; k < GRID_WIDTH; k++) {
				displayData[i][k] = gameGridData[i][k];
			}
		}
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (i + blockY <0 || i + blockY >GRID_HEIGHT) {
					// �迭�� �Ѿ�� ���� �ƹ��͵� �������� ����
				}
				else if (k + blockX<0 || k + blockX>GRID_WIDTH) {
					// �迭�� �Ѿ�� ���� �ƹ��͵� �������� ����
				}
				else { // ������ 1�� �ִ� ���� userblock�� ���� ������ �ʰ� ��
					displayData[i + blockY][k + blockX] = userBlock[i][k] | displayData[i + blockY][k + blockX];
				}
			}
		}
	}
};
