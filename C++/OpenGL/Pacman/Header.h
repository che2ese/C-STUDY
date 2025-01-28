#ifndef PACMAN_GAME_HEADER_H
#define PACMAN_GAME_HEADER_H

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>

// 전역 변수
extern int Width, Height;  // 게임 윈도우의 너비와 높이
extern int pacX, pacY;  // 팩맨의 위치
extern int count;  // 팩맨이 먹은 과일의 수
extern int pacSize, ghostSize, foodSize;  // 팩맨, 유령, 과일의 크기
extern int eyeX, eyeY;  // 팩맨의 눈 위치
extern int num;  // 과일의 수
extern int num2;  // 유령의 수
extern int xArray[20], yArray[20];  // 과일의 위치 배열
extern int xarray[20], yarray[20];  // 유령의 위치 배열
extern int sival, sival2, sival3;
extern int maxX, maxY;  // 윈도우의 최대 X, Y 값
extern int minX, minY;  // 윈도우의 최소 X, Y 값
extern int mouseI, mouseU;  // 팩맨 입의 각도
extern int state;  // 게임 상태
extern int countghost;  // 유령이 먹은 과일 수
extern double distance1[10];  // 팩맨과 유령 사이의 거리
extern double distance2[10];  // 팩맨과 과일 사이의 거리
extern double distance3[10][10];  // 과일과 유령 사이의 거리
extern float takeTime;  // 게임 시간
extern clock_t start;  // 게임 시작 시간

// 함수 선언
void Display();
void Reshape(int w, int h);
void ArrowCallBack(int key, int x, int y);
void Timer(int id);
void Close();
void draw_pacman(double r, double g, double b);
void draw_ghost(double r, double g, double b);
void drawFood(double r, double g, double b);

#endif //PACMAN_GAME_HEADER_H

