#include "Header.h"
#include "include/GL/freeglut.h"

void draw_circle(int x, int y, int xsize, int ysize, int I, int U) {
	glBegin(GL_TRIANGLE_FAN); {
		glVertex2d(x, y);
		for (int i = I; i < U; i++) {
			double theta = M_PI * i / 180;
			double X = x + xsize * cos(theta);
			double Y = y + ysize * sin(theta);
			glVertex2d(X, Y);
		}
	}
	glEnd();
}

void draw_pacman(double r, double g, double b)
{
	glColor3d(r, g, b);			// pacman 몸둥이
	draw_circle(pacX, pacY, pacSize, pacSize, 0, 360);

	glColor3d(1.0, 0.0, 0.0);   // pacman 입
	draw_circle(pacX, pacY, pacSize, pacSize, mouseI, mouseU);

	glColor3d(0.0, 0.0, 0.0);
	glPointSize(4 + count / 2);
	glBegin(GL_POINTS);				// pacman 눈
	{
		glVertex2d(eyeX, eyeY);
	}
	glEnd();
}

void draw_ghost(double r, double g, double b) {
	float xCenter, yCenter, radius;
	if (sival2 == 0) {
		for (int i = 0; i < num2; i++) {
			xarray[i] = minX + rand() % (maxX - minX); // 랜덤 위치 설정
			yarray[i] = minY + rand() % (maxY - minY);
		}
		sival2++;
	}

	for (int j = 0; j < num2; j++) {
		// 유령 본체
		glColor3d(r, g, b);
		draw_circle(xarray[j], yarray[j], ghostSize * 1.15, ghostSize, 0, 180);

		// 유령 하단 물결 모양
		glBegin(GL_TRIANGLE_FAN);
		{
			for (int i = 180; i <= 360; i += 20) {
				double theta = M_PI * i / 180;
				double x = xarray[j] + ghostSize / 2 * cos(theta) / 1.8 + 21;
				double y = yarray[j] + ghostSize * sin(theta) * 1.5; // 물결 높이 감소
				glVertex2d(x, y);
			}
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		{
			for (int i = 180; i <= 360; i += 20) {
				double theta = M_PI * i / 180;
				double x = xarray[j] + ghostSize / 2 * cos(theta) / 1.8 - 21;
				double y = yarray[j] + ghostSize * sin(theta) * 1.5;
				glVertex2d(x, y);
			}
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		{
			for (int i = 180; i <= 360; i += 20) {
				double theta = M_PI * i / 180;
				double x = xarray[j] + ghostSize / 2.4 * cos(theta) - 7.5;
				double y = yarray[j] + ghostSize * sin(theta) * 1.2;
				glVertex2d(x, y);
			}
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		{
			for (int i = 180; i <= 360; i += 20) {
				double theta = M_PI * i / 180;
				double x = xarray[j] + ghostSize / 2.4 * cos(theta) + 7.5;
				double y = yarray[j] + ghostSize * sin(theta) * 1.2;
				glVertex2d(x, y);
			}
		}
		glEnd();

		// 유령 눈
		glColor3d(1.0, 1.0, 1.0); // 눈 색상 (흰색)
		glBegin(GL_TRIANGLE_FAN); // 왼쪽 눈
		{
			glVertex2d(xarray[j] - 5, yarray[j] + 10);
			for (int i = 0; i <= 360; i += 10) {
				double theta = M_PI * i / 180;
				double x = (xarray[j] - 5) + 3 * cos(theta);
				double y = (yarray[j] + 10) + 3 * sin(theta) * 3 - 5;
				glVertex2d(x, y);
			}
		}
		glEnd();

		glBegin(GL_TRIANGLE_FAN); // 오른쪽 눈
		{
			glVertex2d(xarray[j] + 5, yarray[j] + 10);
			for (int i = 0; i <= 360; i += 10) {
				double theta = M_PI * i / 180;
				double x = (xarray[j] + 5) + 3 * cos(theta);
				double y = (yarray[j] + 10) + 3 * sin(theta) * 3 - 5;
				glVertex2d(x, y);
			}
		}
		glEnd();
	}
}

void drawFood(double r, double g, double b) {
	if (sival == 0) {
		for (int i = 0; i < num; i++) {
			xArray[i] = minX + rand() % (maxX - minX);		// ghost를 랜덤수(num2)만큼 랜덤 좌표(윈도우 범위 내)에 찍기
			yArray[i] = minY + rand() % (maxY - minY);
		}
		sival++;
	}
	sival3++;
	if (sival3 % 50 == 0)		// 시간이 지남에 따라 추가 fruit 생성
	{
		xArray[num] = minX + rand() % (maxX - minX);
		yArray[num] = minY + rand() % (maxY - minY);
		num++;
	}
	for (int j = 0; j < num; j++) {
		glColor3d(r, g, b);
		// fruit 본체
		draw_circle(xArray[j], yArray[j], foodSize, foodSize, 0, 360);

		distance2[j] = sqrt(pow((double)pacX - (double)xArray[j], 2) + pow((double)pacY - (double)yArray[j], 2));

		for (int k = 0; k < num2; k++) {			// ghost와 fruit 거리 계산하여 배열에 넣기
			distance3[k][j] = sqrt(pow((double)xarray[k] - (double)xArray[j], 2) + pow((double)yarray[k] - (double)yArray[j], 2));
		}

		glColor3d(0.0, 1.0, 0.0);
		glPointSize(5);
		glBegin(GL_POINTS);		// fruit 꼭지 만들기
		{
			glVertex2d(xArray[j], yArray[j] + 8);
		}
		glEnd();
	}

	for (int z = 0; z < num; z++) {
		if (distance2[z] <= (double)foodSize + (double)pacSize) {		// pacman이 fruit를 먹고 없애는 경우 
			xArray[z] = 800;
			yArray[z] = 800;
			count++;
			pacSize += count;	// pacman이 fruit를 먹는 수만큼 pacman 반지름 증가
		}
		for (int q = 0; q < num2; q++) {
			if (distance3[q][z] <= (double)ghostSize + (double)foodSize) {		// ghost가 fruit를 먹고 없애는 경우
				xArray[z] = 800;
				yArray[z] = 800;
				countghost++;
			}
		}
	}
}
