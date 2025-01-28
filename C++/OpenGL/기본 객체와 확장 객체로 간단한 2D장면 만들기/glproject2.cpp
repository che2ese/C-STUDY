#include <iostream>
#include <math.h>
#include<vector>
#include ".\include\GL\freeglut.h"

int Width = 600, Height = 600;

void Render();
void Reshape(int w, int h);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(Width, Height);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("assignment1");
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}

void draw_ellipse(double ccx, double ccy, double ssx, double ssy, double rr, double gg, double bb, int ssnum, float aaa, float bbb, float ccc) {
	glColor3d(aaa,bbb,ccc);
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex2d(ccx, ccy);
		for (int ii = 0; ii < ssnum; ++ii) {
			double ttheta = ii / (double)(ssnum - 1) * 2.0 * 3.141592;
			double xx = ccx + ssx * cos(ttheta);
			double yy = ccy + ssy * sin(ttheta);
			glVertex2d(xx, yy);
		}
	}
	glEnd();
}


void Render()
{
	glClearColor(0.5f, 0.0f, 1.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	{

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor3d(0.0, 0.7, 0.3); //땅
		glBegin(GL_QUADS);
		glVertex2d(-10.0, -4.0);
		glVertex2d(-10.0, -10.0);
		glVertex2d(10.0, -10.0);
		glVertex2d(10.0, -4.0);
		glEnd();
	}
	glDisable(GL_BLEND);

	glColor3d(1.0, 5.0, 0.0); //집 본체
	glBegin(GL_QUADS);
	glVertex2d(-6.0f, -7.0f);
	glVertex2d(-6.0f, -2.0f);
	glVertex2d(1.0f, -2.0f);
	glVertex2d(1.0f, -7.0f);
	glEnd();

	glColor3d(0.0, 1.0, 5.0); //왼쪽 창문
	glBegin(GL_QUADS);
	glVertex2d(-5.6f, -4.5f);
	glVertex2d(-5.6f, -2.5f);
	glVertex2d(-4.0f, -2.5f);
	glVertex2d(-4.0f, -4.5f);
	glEnd();

	glColor3d(0.0, 1.0, 5.0); //오른쪽 창문
	glBegin(GL_QUADS);
	glVertex2d(0.6f, -4.5f);
	glVertex2d(0.6f, -2.5f);
	glVertex2d(-1.0f, -2.5f);
	glVertex2d(-1.0f, -4.5f);
	glEnd();



	glColor3d(0.0, 0.0, 0.0); // 창틀
	glBegin(GL_LINES);
	glVertex2d(-4.8f, -4.5f);
	glVertex2d(-4.8f, -2.5f);
	glEnd();
	glColor3d(0.0, 0.0, 0.0); // 창틀
	glBegin(GL_LINES);
	glVertex2d(-0.2f, -4.5f);
	glVertex2d(-0.2f, -2.5f);
	glEnd();
	glColor3d(0.0, 0.0, 0.0); // 창틀
	glBegin(GL_LINES);
	glVertex2d(0.6f, -3.5f);
	glVertex2d(-1.0f, -3.5f);
	glEnd();
	glColor3d(0.0, 0.0, 0.0); // 창틀
	glBegin(GL_LINES);
	glVertex2d(-5.6f, -3.5f);
	glVertex2d(-4.0, -3.5f);
	glEnd();

	glColor3d(0.0, 0.0, 1.0); //문
	glBegin(GL_QUADS);
	glVertex2d(-1.25f, -7.0f);
	glVertex2d(-3.75f, -7.0f);
	glVertex2d(-3.75f, -4.0f);
	glVertex2d(-1.25f, -4.0f);
	glEnd();

	glColor3d(0.0, 0.0, 0.0); // 문 나누기
	glBegin(GL_LINES);
	glVertex2d(-2.5f, -7.0f);
	glVertex2d(-2.5f, -4.0f);
	glEnd();

	glColor3d(0.0, 0.0, 0.0); // 손 잡이
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex2i(-2.0f, -5.5f);
	glVertex2i(-3.0f, -5.5f);
	glEnd();

	glColor3d(1.0, 0.0, 0.0); //지붕
	glBegin(GL_POLYGON);
	glVertex2d(2.0, -2.0);
	glVertex2d(-7.0, -2.0);
	glVertex2d(-5.0, 1.0);
	glVertex2d(0.0, 1.0);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f); //굴뚝
	glBegin(GL_QUADS);
	glVertex2d(-2.0f, 0.5f);
	glVertex2d(-2.0f, 3.0f);
	glVertex2d(-0.5f, 3.0f);
	glVertex2d(-0.5f, 0.5f);
	glEnd();
	glEnable(GL_BLEND);
	{

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glColor4f(1.0, 1.0, 1.0, 0.3);
		glBegin(GL_QUADS);
		glVertex2d(-2.0f, 0.5f);
		glVertex2d(-2.0f, 2.5f);
		glVertex2d(-0.5f, 2.5f);
		glVertex2d(-0.5f, 0.5f);
		glEnd();
	}
	glDisable(GL_BLEND);

	glColor3f(0.0f, 0.0f, 0.0f); //굴뚝
	glBegin(GL_QUADS);
	glVertex2d(-2.2f, 3.0f);
	glVertex2d(-2.2f, 2.5f);
	glVertex2d(-0.3f, 2.5f);
	glVertex2d(-0.3f, 3.0f);
	glEnd();

	glColor3d(0.0, 0.0, 0.0); // 굴뚝 선 긋기
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 0.75f);
	glVertex2d(-0.5f, 0.75f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 1.0f);
	glVertex2d(-0.5f, 1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 1.25f);
	glVertex2d(-0.5f, 1.25f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 1.5f);
	glVertex2d(-0.5f, 1.5f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 1.75f);
	glVertex2d(-0.5f, 1.75f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 2.0f);
	glVertex2d(-0.5f, 2.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(-2.0f, 2.25f);
	glVertex2d(-0.5f, 2.25f);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f); //나무
	glBegin(GL_QUADS);
	glVertex2d(6.5f, -2.0f);
	glVertex2d(5.5f, -2.0f);
	glVertex2d(5.0f, -6.8f);
	glVertex2d(7.0f, -6.8f);
	glEnd();
	glEnable(GL_BLEND);
	{

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		glColor4f(0.0, 0.0, 0.0, 0.55);
		glBegin(GL_QUADS);
		glVertex2d(6.5f, -2.0f);
		glVertex2d(5.5f, -2.0f);
		glVertex2d(5.0f, -6.8f);
		glVertex2d(7.0f, -6.8f);
		glEnd();
	}
	glDisable(GL_BLEND);

	glColor3d(0.0, 0.0, 0.0); // 바퀴
	glBegin(GL_POLYGON);
	double wheelRadius = 0.5; // 바퀴의 반지름
	int numSegments = 50; // 원을 그릴 때 사용할 세그먼트 수
	for (int i = 0; i < numSegments; i++) {
		double theta = 2.0 * 3.1415926 * double(i) / double(numSegments);
		double x = wheelRadius * cos(theta);
		double y = wheelRadius * sin(theta);
		glVertex2d(x + 3.0, -7.4 + y); // 원의 중심 위치를 조정하여 차 아래에 그립니다.
	}
	glEnd();
	
	glColor3d(0.0, 0.0, 0.0); // 바퀴
	glBegin(GL_POLYGON);
	double wheelRadius1 = 0.5; // 바퀴의 반지름
	int numSegments1 = 50; // 원을 그릴 때 사용할 세그먼트 수
	for (int i = 0; i < numSegments1; i++) {
		double theta = 2.0 * 3.1415926 * double(i) / double(numSegments1);
		double x = wheelRadius * cos(theta);
		double y = wheelRadius * sin(theta);
		glVertex2d(x + 5.5, -7.4 + y); // 원의 중심 위치를 조정하여 차 아래에 그립니다.
	}
	glEnd();




	glColor3d(0.0, 0.0, 1.0); //차 앞부분
	glBegin(GL_POLYGON);
	glVertex2d(2.0, -7.0);
	glVertex2d(2.0, -6.0);
	glVertex2d(3.0, -5.0);
	glVertex2d(4.0, -5.0);
	glVertex2d(4.0, -7.0);
	glEnd();

	glColor3d(0.0, 1.0, 5.0); //차 앞부분 유리
	glBegin(GL_POLYGON);
	glVertex2d(2.0, -6.5);
	glVertex2d(2.0, -6.0);
	glVertex2d(2.7, -5.3);
	glVertex2d(3.5, -5.3);
	glVertex2d(3.5, -6.5);
	glEnd();

	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(4.0f, -7.0f);
	glVertex2d(4.0f, -6.2f);
	glEnd();


	glColor3d(0.0, 0.0, 1.0); //차 뒷부분
	glBegin(GL_POLYGON);
	glVertex2d(4.0, -7.0);
	glVertex2d(4.0, -6.2);
	glVertex2d(7.0, -6.2);
	glVertex2d(7.0, -7.0);
	glEnd();



	glColor3d(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(4.0f, -6.8f);
	glVertex2d(7.0f, -6.8f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(4.0f, -6.6f);
	glVertex2d(7.0f, -6.6f);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(4.0f, -6.4f);
	glVertex2d(7.0f, -6.4f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	double rad = 3;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 180; i++)
	{
		double angle = i * 3.141592 / 180;
		double x = rad * cos(angle);
		double y = rad * sin(angle);
		double cx = 6;
		double cy = -3;
		glVertex2f(x + cx, y + cy);

	}
	glEnd();
	glFinish();

	glColor3f(0.0f, 1.0f, 0.0f);
	double r = 2;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double q = r * cos(angle);
		double p = r * sin(angle);
		double cp = 6;
		double cq = -1;
		glVertex2f(p + cp, q + cq);

	}
	glEnd();
	glFinish();

	glColor3f(0.0f, 1.0f, 0.0f);
	double rd = 1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double angle = i * 3.141592 / 180;
		double z = rd * cos(angle);
		double w = rd * sin(angle);
		double cz = 6;
		double cw = 1;
		glVertex2f(z + cz, w + cw);

	}
	glEnd();
	glFinish();


	draw_ellipse(6.5, 6.5, 2.0, 2.0, 1.0, 0.0, 0.0, 100, 1.0,1.0,0.0); //초승달
	draw_ellipse(7.0, 7.0, 2.0, 2.0, 1.0, 0.0, 0.0, 100, 0.5, 0.0, 1.5);
	
	draw_ellipse(-6.7, 4.5, 1.0, 1.0, 1.0, 0.0, 0.0, 100, 0.5, 0.5, 0.5); //  구름
	draw_ellipse(-4.3, 4.5, 1.0, 1.0, 1.0, 0.0, 0.0, 100, 0.5, 0.5, 0.5);
	draw_ellipse(-5.5, 4.5, 1.3, 1.3, 1.0, 0.0, 0.0, 100, 0.5, 0.5, 0.5);

	draw_ellipse(-1.2, 5.8, 1.0, 1.0, 1.0, 0.0, 0.0, 100, 0.5, 0.5, 0.5);
	draw_ellipse(1.2, 5.8, 1.0, 1.0, 1.0, 0.0, 0.0, 100, 0.5, 0.5, 0.5);
	draw_ellipse(0.0, 5.8, 1.3, 1.3, 1.0, 0.0, 0.0, 100, 0.5, 0.5, 0.5);

	draw_ellipse(8.0, 8.0, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0); // 별
	draw_ellipse(2.5, 7.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(4.5, 4.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(1.5, 2.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(1.0, 9.6, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(-4.5, 6.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(-7.5, 8.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(-8.5, 4.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(-8.0, 1.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);
	draw_ellipse(8.0, 1.5, 0.1, 0.1, 1.0, 0.0, 0.0, 100, 1.0, 1.0, 0.0);

	glutSwapBuffers();

}


void Reshape(int w, int h)
{

	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}