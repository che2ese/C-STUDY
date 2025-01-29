#pragma once

void PrintMap1D();
void PrintMap2D();

const int MAP_SIZE = 5;
extern int GMap1D[MAP_SIZE * MAP_SIZE]; // 맵 사이즈는 전역변수로 설정해야됨.
extern int GMap2D[MAP_SIZE][MAP_SIZE];