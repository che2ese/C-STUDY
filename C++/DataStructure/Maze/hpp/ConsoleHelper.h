#pragma once

/*
	enum은 다른 enum과 겹치는 이름을 쓰면 안됨.
	그리고 enum값은 정수로 인식.
	enum class는 이름 겹침 문제 해결 + type 그대로 가져옴.
	하지만 정수형도 가지고 있기 때문에 정수로 쓰고 싶으면 캐스팅 쓰면 됨.
*/

/* 
ex)
	enum class ScreenColor
	{
		RED,
		GREEN,
	};
	
	enum class LightColor
	{
		RED,
		GREEN,
	};

	int main()
	{
		int a = static_cast<int>(ScreenColor::RED);
	}
*/


enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

class ConsoleHelper
{
public:
	// 굳이 ConsoleHelper 객체를 생성하지 않고 사용하기 위해 static 사용
	static void SetCursorPosition(int32 x, int32 y);
	static void SetCursorColor(ConsoleColor color);
	static void ShowConsoleCursor(bool flag);
};

