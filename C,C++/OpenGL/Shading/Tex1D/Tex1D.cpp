#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "..\include\GL\freeglut.h"
#include <vector>

// ������ ũ��
int Width = 800, Height = 800;

// ��� ������ ���� ������
int ManipulateMode = 0; // 1: ȸ��, 2: �̵�
int StartPt[2];
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 };
float Zoom = -30.0;
float Pan[3] = { 0.0, 0.0, 0.0 };

// �ݹ� �Լ���
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Render();

// ����� ���� �Լ���
void InitOpenGL();
void GetSphereCoord(int x, int y, float *px, float *py, float *pz);
void RenderFloor();
void SetupViewVolume();
void SetupViewTransform();
void Sub(double out[3], double a[3], double b[3]);
void Add(double out[3], double a[3], double b[3]);
void Cross(double out[3], double a[3], double b[3]);

void Cross(double out[3], double a[3], double b[3])
{
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0];
}

void Sub(double out[3], double a[3], double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

void Add(double out[3], double a[3], double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

GLubyte RainBow[128][4];
GLubyte RainBow2[128];
GLuint TexId;

GLubyte CheckBoard[64][64][3];

int main(int argc, char **argv)
{
	// GLUT �ʱ�ȭ(���� Į�����, RBGA, ���̹��� ���)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// ������ ����
	glutInitWindowSize(Width, Height);
	glutCreateWindow("3DViewer");

	// OpenGL �ʱ�ȭ
	InitOpenGL();

	// �ݹ��Լ� ���
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion); // ���콺 ��ư ������ ������ ��, �ڵ����� ȣ��Ǵ� �Լ�
	glutMouseWheelFunc(MouseWheel);
	glutDisplayFunc(Render);

	// �޽��� ���� ����
	glutMainLoop();
	return 0;
}


void InitOpenGL()
{
	// ���� �׽�Ʈ�� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);

	// OpenGL �����Ÿ� Ȱ��ȭ
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// ���� �� Ȱ��ȭ
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	// 1���� ������ �ؽ�ó �迭�� ����
	for (int i = 0; i < 128; ++i)
	{
		double t = i / 127.0;

		int X = (int)(6 * t); // X = 0, 1, 2, 3, 4, 5, 6
		t = 6.0 * t - X;	  // t = 0.0 ~ 1.0	
		
		switch (X)
		{
		case 0:	// ���� ~ ��Ȳ
			RainBow[i][0] = (GLubyte)((1.0 - t) * 255 + t * 255);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 0 + t * 127);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][3] = 255;
			break;

		case 1:	// ��Ȳ ~ ���
			RainBow[i][0] = (GLubyte)((1.0 - t) * 255 + t * 255);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 127 + t * 255);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][3] = 255;
			break;

		case 2:	// ��� ~ �ʷ�
			RainBow[i][0] = (GLubyte)((1.0 - t) * 255 + t * 0);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 255 + t * 255);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][3] = 255;
			break;

		case 3:	// �ʷ� ~ �Ķ�
			RainBow[i][0] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 255 + t * 0);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 255);
			RainBow[i][3] = 255;
			break;

		case 4:	// �Ķ� ~ ����
			RainBow[i][0] = (GLubyte)((1.0 - t) * 0 + t * 75);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 255 + t * 130);
			RainBow[i][3] = 255;
			break;

		case 5:	// ���� ~ ����
			RainBow[i][0] = (GLubyte)((1.0 - t) * 75 + t * 148);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 130 + t * 211);
			RainBow[i][3] = 255;
			break;

		case 6:	// ����
			RainBow[i][0] = 148;
			RainBow[i][1] = 0;
			RainBow[i][2] = 211;
			RainBow[i][3] = 255;
			break;
		}

		// ���� ���� �������� �Ҵ��Ѵ�.
		if (t < 0.0 || t > 1.0)
		{
			RainBow[i][0] = 0;
			RainBow[i][1] = 0;
			RainBow[i][2] = 0;
			RainBow[i][3] = 255;
		}
	}
	glEnable(GL_TEXTURE_1D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TexId);
	glBindTexture(GL_TEXTURE_1D, TexId);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, RainBow);

	//for (int i = 0; i < 64; ++i)
	//{
	//	for (int j = 0; j < 64; ++j)
	//	{
	//		int c = (((((i & 0x8) == 0) ^ ((j & 0x8)) == 0))) * 255;
	//		//printf("%d  ", c);
	//		CheckBoard[i][j][0] = (GLubyte)c;
	//		CheckBoard[i][j][1] = (GLubyte)c;
	//		CheckBoard[i][j][2] = (GLubyte)c;
	//		//CheckBoard[i][j][3] = 255;
	//	}
	//}

	//glEnable(GL_TEXTURE_2D);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glGenTextures(1, &TexId);
	//glBindTexture(GL_TEXTURE_2D, TexId);
	////glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, (void *)CheckBoard);
	//glDisable(GL_TEXTURE_2D);
}

void Render()
{
	// ���� ���� �ʱ�ȭ
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���̹��� = 1.0���� �ʱ�ȭ��

	// �������� ���� (��������: ������ü����, ��������: ����ü ���)
	SetupViewVolume();

	// ������ȯ ���� (��� ������ ���⼭ �����)
	SetupViewTransform();

	// ��� ������
	glMatrixMode(GL_MODELVIEW);
	RenderFloor();

	glEnable(GL_TEXTURE_1D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_1D, TexId);
	glBegin(GL_TRIANGLES);
	{
		//glTexCoord2d(0.0, 0.0);
		glTexCoord1d(1.0);
		//glColor3f(1.0, 0.0, 0.0);
		glVertex3d(-2.0, 0.0, 0.0);

		//glTexCoord2d(1.0, 0.0);
		glTexCoord1d(0.0);
		glVertex3d(2.0, 0.0, 0.0);

		//glTexCoord2d(0.0, 1.0);
		//glColor3f(1.0, 0.0, 1.0);
		glTexCoord1d(1.0);
		glVertex3d(0.0, 5.0, 0.0);
	}
	glEnd();
	glDisable(GL_TEXTURE_1D);

	// ���� ���۸��� ���� ���� ��ȯ
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// ����Ʈ ��ȯ
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}


void SetupViewVolume()
{
	// ���� ���� ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)Width / (double)Height, 1.0, 10000.0);
}

void SetupViewTransform()
{
	// �� �� ����� ���� ��ķ� �ʱ�ȭ, M = I
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// �� ��/�ƿ��� ���� ��ȯ, M = I * T_zoom
	glTranslatef(0.0, 0.0, Zoom);

	// ���ο� ȸ���� ����, M = I * T_zoom * R_new
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

	// ���� ȸ���� ����, M = I * T_zoom * R_new * R_old	//   R_n .... * R3 * R2 * R1
	glMultMatrixf(RotMat);

	// ȸ�� ��� ����, R_old = R_new * R_old
	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;

	// �̵� ��ȯ�� ����, M = I * T_zoom * R_new * R_old * T_pan
	glTranslatef(Pan[0], Pan[1], Pan[2]);
}

void RenderFloor()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	for (float x = -10.0; x <= 10.0; x += 1.0)
	{
		glBegin(GL_LINES);
		glVertex3f(x, 0.0, -10.0f);
		glVertex3f(x, 0.0, 10.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(-10.0f, 0.0, x);
		glVertex3f(10.0f, 0.0, x);
		glEnd();
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		StartPt[0] = x;
		StartPt[1] = y;
		if (button == GLUT_LEFT_BUTTON)
			ManipulateMode = 1;	// ȸ��

		if (button == GLUT_RIGHT_BUTTON)
			ManipulateMode = 2;	// �̵�
	}
	if (state == GLUT_UP)
	{
		ManipulateMode = 0;	// ����
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void Motion(int x, int y)
{
	// ȸ����� ȸ�� ���� ���
	if (ManipulateMode == 1)
	{
		// ���� �� ���� ��ǥ ���
		float px, py, pz, qx, qy, qz;
		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		// ȸ�� ��� ���� ���
		Axis[0] = py * qz - pz * qy;
		Axis[1] = pz * qx - px * qz;
		Axis[2] = px * qy - py * qx;
		Angle = 0.0;
		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len > 0.0001) // ���� ���� �̻� ó��
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
	}

	// �̵� ���� ���
	if (ManipulateMode == 2)
	{
		float dx = (float)(x - StartPt[0]) * 0.01f;
		float dy = (float)(StartPt[1] - y) * 0.01f;
		// ȸ�� ��� �� �����
		// R = 0 4 8   invR = 0 1 2
		//     1 5 9          4 5 6    
		//     2 6 10         8 9 10
		// invR * (dx, dy, 0)
		Pan[0] += RotMat[0] * dx + RotMat[1] * dy;
		Pan[1] += RotMat[4] * dx + RotMat[5] * dy;
		Pan[2] += RotMat[8] * dx + RotMat[9] * dy;
	}

	StartPt[0] = x;	// Update startpt as current position
	StartPt[1] = y;
	glutPostRedisplay();
}

/*!
*	\brief ���콺 ��ũ���� ó���ϴ� �ݹ� �Լ�
*
*	\param button[in]	���콺 ��ư ����(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param dir[in]		��ũ���� ����
*	\param x[in]		���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*	\param y[in]		���� ����� (0, 0) �������� ���콺 �������� ���� ��ġ
*/
void MouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
		Zoom += 1.0;
	else
		Zoom -= 1.0;
	glutPostRedisplay();
}

void GetSphereCoord(int x, int y, float *px, float *py, float *pz)
{
	*px = (2.0f * x - Width) / Width;
	*py = (-2.0f * y + Height) / Height;

	float r = (*px) * (*px) + (*py) * (*py); // �������κ����� �Ÿ� ���
	if (r >= 1.0f)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0f;
	}
	else
		*pz = sqrt(1.0f - r);  // �Ϲ����� ���
}
