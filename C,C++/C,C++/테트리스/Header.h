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
	
	float elapsed = 0.0f; // 블록이 너무 빨리 떨어지는거 방지
	float controlCheck = 0.0f;

	void init() {
		// 게임 엔진 초기화
		makeUserBlock();
	}
	
	// next는 while 루프에서 매번 불려지는 함수
	void next(float dt, char keyboardInput) {
		if (state == GameState::GAMEOVER) return;
		elapsed += dt;
		if (elapsed >= 0.5f) {
			if (canGoDown()) {
				blockY++;
			}
			else {
				// userblock을 gamegridData로 바꿔줌
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

	// 블록이 아래로 갈 수 있는지
	bool canGoDown() {
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (userBlock[i][k] == 1 && i + blockY + 1 >= GRID_HEIGHT) {
					return false;			// block의 총 높이를 벗어나는지 판단하는 코드
				}
				if (userBlock[i][k] == 1 && gameGridData[i+blockY+1][k+blockX] == 1) { 
					return false;						// i+blockY는 userblock의 제일 밑에 있는 칸
				}                                       // 제일 밑 칸의 밑에 뭐가 있는지 판단하는 코드
			}
		}
		return true; // 저 두개의 조건에 걸리지 않으면 통과 가능
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

	// 한 줄이 채웠는지 확인
	bool isLineFilled(int y) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			if (gameGridData[y][i] == 0) return false; // y번째의 줄이 가득 차 있는지 확인
		}
		point += 10;
		return true;
	}

	// 한 줄이 차면 지움
	void eraseLine(int y) {
		for (int i = 0; i < GRID_WIDTH; i++) {
			gameGridData[y][i] = 0;
		}
	}

	// 한 줄씩 내림
	void drop(int y) {
		for (int i = y; i >= 0; i--) { // y좌표부터 내려야 하기 때문에 i = y 사용
			for (int k = 0; k < GRID_WIDTH; k++) {
				gameGridData[i][k] = i - 1 < 0 ? 0 : gameGridData[i - 1][k];
			}
		}
	}

	void trans() { // userblock을 gamegridData로 바꿔주는 함수
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
		// 새로운 블록 생성
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

	void makeUserBlock() { // 랜덤으로 새로운 블록 생성
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
	// 실제 게임 데이터를 화면에 출력할 수 있는 데이터로 바꿔주는 함수
	void makeDisplayData() {
		for (int i = 0; i < GRID_HEIGHT; i++) {
			for (int k = 0; k < GRID_WIDTH; k++) {
				displayData[i][k] = gameGridData[i][k];
			}
		}
		for (int i = 0; i < USERBLOCK_SIZE; i++) {
			for (int k = 0; k < USERBLOCK_SIZE; k++) {
				if (i + blockY <0 || i + blockY >GRID_HEIGHT) {
					// 배열을 넘어갔을 때는 아무것도 실행하지 않음
				}
				else if (k + blockX<0 || k + blockX>GRID_WIDTH) {
					// 배열을 넘어갔을 때는 아무것도 실행하지 않음
				}
				else { // 기존에 1이 있던 곳이 userblock에 의해 먹히지 않게 함
					displayData[i + blockY][k + blockX] = userBlock[i][k] | displayData[i + blockY][k + blockX];
				}
			}
		}
	}
};
