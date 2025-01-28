#ifndef __TYPING_GAME_HELPER_H__
#define __TYPING_GAME_HELPER_H__

#include <Windows.h>
#include <cstdio>
#include <string>

void putStringOnPosition(int x, int y, const std::string& content);

void showConsoleCursor(bool showFlag);

void clear();

#endif
