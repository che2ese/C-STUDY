#include <iostream>
using namespace std;
#include "Helper.h"
#include "Map.h"
#include "Player.h"

int main() {
	SetCursorOnOff(false);

	while (true) { // 보통 밑에 3개는 무한 루프
		// 입력
		HandleKeyInput();
		
		// 로직
		HandleMove();

		// 출력
		// PrintMap1D();
		PrintMap2D();
	}
}