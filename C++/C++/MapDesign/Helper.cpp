#include "Helper.h"
#include <windows.h>

MoveDir GMoveDir;

void HandleKeyInput() {
	if (::GetAsyncKeyState(VK_LEFT) & 0x8000)
		GMoveDir = MD_LEFT;
	else if (::GetAsyncKeyState(VK_RIGHT) & 0x8000)
		GMoveDir = MD_RIGHT;
	else if (::GetAsyncKeyState(VK_UP) & 0x8000)
		GMoveDir = MD_UP;
	else if (::GetAsyncKeyState(VK_DOWN) & 0x8000)
		GMoveDir = MD_DOWN;
	else
		GMoveDir = MD_NONE;
}

void SetcursorPosition(int x, int y) {
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE); // :: 내가 만들지 않았다는 표시
	COORD pos = { (SHORT)x, (SHORT)y };
	::SetConsoleCursorPosition(output, pos);
}

void SetCursorOnOff(bool visible) {
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = visible;
	::SetConsoleCursorInfo(output, &cursorInfo);
}