#ifndef PACMAN_GAME_HEADER_H
#define PACMAN_GAME_HEADER_H

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>

// ���� ����
extern int Width, Height;  // ���� �������� �ʺ�� ����
extern int pacX, pacY;  // �Ѹ��� ��ġ
extern int count;  // �Ѹ��� ���� ������ ��
extern int pacSize, ghostSize, foodSize;  // �Ѹ�, ����, ������ ũ��
extern int eyeX, eyeY;  // �Ѹ��� �� ��ġ
extern int num;  // ������ ��
extern int num2;  // ������ ��
extern int xArray[20], yArray[20];  // ������ ��ġ �迭
extern int xarray[20], yarray[20];  // ������ ��ġ �迭
extern int sival, sival2, sival3;
extern int maxX, maxY;  // �������� �ִ� X, Y ��
extern int minX, minY;  // �������� �ּ� X, Y ��
extern int mouseI, mouseU;  // �Ѹ� ���� ����
extern int state;  // ���� ����
extern int countghost;  // ������ ���� ���� ��
extern double distance1[10];  // �Ѹǰ� ���� ������ �Ÿ�
extern double distance2[10];  // �Ѹǰ� ���� ������ �Ÿ�
extern double distance3[10][10];  // ���ϰ� ���� ������ �Ÿ�
extern float takeTime;  // ���� �ð�
extern clock_t start;  // ���� ���� �ð�

// �Լ� ����
void Display();
void Reshape(int w, int h);
void ArrowCallBack(int key, int x, int y);
void Timer(int id);
void Close();
void draw_pacman(double r, double g, double b);
void draw_ghost(double r, double g, double b);
void drawFood(double r, double g, double b);

#endif //PACMAN_GAME_HEADER_H

