#pragma once

void MovePlayer(int x, int y);
void HandleMove();

extern int GPlayerX; // 전역으로 필요없으면 헤더파일에 없어도 됨.
extern int GPlayerY; // 나중에 등장할 것임을 알리는 것이기에 초기값 X