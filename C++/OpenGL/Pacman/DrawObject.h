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
	glColor3d(r, g, b);			// pacman ������
	draw_circle(pacX, pacY, pacSize, pacSize, 0, 360);

	glColor3d(1.0, 0.0, 0.0);   // pacman ��
	draw_circle(pacX, pacY, pacSize, pacSize, mouseI, mouseU);

	glColor3d(0.0, 0.0, 0.0);
	glPointSize(4 + count / 2);
	glBegin(GL_POINTS);				// pacman ��
	{
		glVertex2d(eyeX, eyeY);
	}
	glEnd();
}

void draw_ghost(double r, double g, double b) {
	float xCenter, yCenter, radius;
	if (sival2 == 0) {
		for (int i = 0; i < num2; i++) {
			xarray[i] = minX + rand() % (maxX - minX); // ���� ��ġ ����
			yarray[i] = minY + rand() % (maxY - minY);
		}
		sival2++;
	}

	for (int j = 0; j < num2; j++) {
		// ���� ��ü
		glColor3d(r, g, b);
		draw_circle(xarray[j], yarray[j], ghostSize * 1.15, ghostSize, 0, 180);

		// ���� �ϴ� ���� ���
		glBegin(GL_TRIANGLE_FAN);
		{
			for (int i = 180; i <= 360; i += 20) {
				double theta = M_PI * i / 180;
				double x = xarray[j] + ghostSize / 2 * cos(theta) / 1.8 + 21;
				double y = yarray[j] + ghostSize * sin(theta) * 1.5; // ���� ���� ����
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

		// ���� ��
		glColor3d(1.0, 1.0, 1.0); // �� ���� (���)
		glBegin(GL_TRIANGLE_FAN); // ���� ��
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

		glBegin(GL_TRIANGLE_FAN); // ������ ��
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
			xArray[i] = minX + rand() % (maxX - minX);		// ghost�� ������(num2)��ŭ ���� ��ǥ(������ ���� ��)�� ���
			yArray[i] = minY + rand() % (maxY - minY);
		}
		sival++;
	}
	sival3++;
	if (sival3 % 50 == 0)		// �ð��� ������ ���� �߰� fruit ����
	{
		xArray[num] = minX + rand() % (maxX - minX);
		yArray[num] = minY + rand() % (maxY - minY);
		num++;
	}
	for (int j = 0; j < num; j++) {
		glColor3d(r, g, b);
		// fruit ��ü
		draw_circle(xArray[j], yArray[j], foodSize, foodSize, 0, 360);

		distance2[j] = sqrt(pow((double)pacX - (double)xArray[j], 2) + pow((double)pacY - (double)yArray[j], 2));

		for (int k = 0; k < num2; k++) {			// ghost�� fruit �Ÿ� ����Ͽ� �迭�� �ֱ�
			distance3[k][j] = sqrt(pow((double)xarray[k] - (double)xArray[j], 2) + pow((double)yarray[k] - (double)yArray[j], 2));
		}

		glColor3d(0.0, 1.0, 0.0);
		glPointSize(5);
		glBegin(GL_POINTS);		// fruit ���� �����
		{
			glVertex2d(xArray[j], yArray[j] + 8);
		}
		glEnd();
	}

	for (int z = 0; z < num; z++) {
		if (distance2[z] <= (double)foodSize + (double)pacSize) {		// pacman�� fruit�� �԰� ���ִ� ��� 
			xArray[z] = 800;
			yArray[z] = 800;
			count++;
			pacSize += count;	// pacman�� fruit�� �Դ� ����ŭ pacman ������ ����
		}
		for (int q = 0; q < num2; q++) {
			if (distance3[q][z] <= (double)ghostSize + (double)foodSize) {		// ghost�� fruit�� �԰� ���ִ� ���
				xArray[z] = 800;
				yArray[z] = 800;
				countghost++;
			}
		}
	}
}
