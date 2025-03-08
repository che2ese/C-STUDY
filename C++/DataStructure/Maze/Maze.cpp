#include "pch.h"
#include "Board.h"
#include "Player.h"

// 언젠가 나오기 때문에 미리 선언
Board board;
Player player;

int main()
{
	::srand(static_cast<uint32>(time(nullptr)));
	
	board.Init(25, &player);
	player.Init(&board);


	uint64 lastTick = 0;

	// 게임은 항상 무한루프를 돌고 있음
	while (true)
	{
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick;
		lastTick = currentTick;

		// 입력

		// 로직
		player.Update(deltaTick);

		// 렌더링
		board.Render();
	}
}