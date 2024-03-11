#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "..\include\GL\freeglut.h"
#include <vector>

// 윈도우 크기
int Width = 800, Height = 800;

// 장면 조작을 위한 변수들
int ManipulateMode = 0; // 1: 회전, 2: 이동
int StartPt[2];
float Axis[3] = { 1.0, 0.0, 0.0 };
float Angle = 0.0;
float RotMat[16] = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1 };
float Zoom = -30.0;
float Pan[3] = { 0.0, 0.0, 0.0 };

// 콜백 함수들
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void MouseWheel(int button, int dir, int x, int y);
void Render();

// 사용자 정의 함수들
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
	// GLUT 초기화(더블 칼라버퍼, RBGA, 깊이버퍼 사용)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// 윈도우 생성
	glutInitWindowSize(Width, Height);
	glutCreateWindow("3DViewer");

	// OpenGL 초기화
	InitOpenGL();

	// 콜백함수 등록
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion); // 마우스 버튼 누리고 움직일 때, 자동으로 호출되는 함수
	glutMouseWheelFunc(MouseWheel);
	glutDisplayFunc(Render);

	// 메시지 루프 진입
	glutMainLoop();
	return 0;
}


void InitOpenGL()
{
	// 깊이 테스트를 활성화
	glEnable(GL_DEPTH_TEST);

	// OpenGL 면제거를 활성화
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	// 조명 모델 활성화
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	// 1차원 무지개 텍스처 배열을 생성
	for (int i = 0; i < 128; ++i)
	{
		double t = i / 127.0;

		int X = (int)(6 * t); // X = 0, 1, 2, 3, 4, 5, 6
		t = 6.0 * t - X;	  // t = 0.0 ~ 1.0	
		
		switch (X)
		{
		case 0:	// 빨강 ~ 주황
			RainBow[i][0] = (GLubyte)((1.0 - t) * 255 + t * 255);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 0 + t * 127);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][3] = 255;
			break;

		case 1:	// 주황 ~ 노랑
			RainBow[i][0] = (GLubyte)((1.0 - t) * 255 + t * 255);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 127 + t * 255);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][3] = 255;
			break;

		case 2:	// 노랑 ~ 초록
			RainBow[i][0] = (GLubyte)((1.0 - t) * 255 + t * 0);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 255 + t * 255);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][3] = 255;
			break;

		case 3:	// 초록 ~ 파랑
			RainBow[i][0] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 255 + t * 0);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 0 + t * 255);
			RainBow[i][3] = 255;
			break;

		case 4:	// 파랑 ~ 남색
			RainBow[i][0] = (GLubyte)((1.0 - t) * 0 + t * 75);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 255 + t * 130);
			RainBow[i][3] = 255;
			break;

		case 5:	// 남색 ~ 보라
			RainBow[i][0] = (GLubyte)((1.0 - t) * 75 + t * 148);
			RainBow[i][1] = (GLubyte)((1.0 - t) * 0 + t * 0);
			RainBow[i][2] = (GLubyte)((1.0 - t) * 130 + t * 211);
			RainBow[i][3] = 255;
			break;

		case 6:	// 보라
			RainBow[i][0] = 148;
			RainBow[i][1] = 0;
			RainBow[i][2] = 211;
			RainBow[i][3] = 255;
			break;
		}

		// 범위 밖은 검정색을 할당한다.
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
	// 색상 버퍼 초기화
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 깊이버퍼 = 1.0으로 초기화됨

	// 관측공간 지정 (직교투영: 직육면체형태, 원근투영: 절두체 모양)
	SetupViewVolume();

	// 관측변환 설정 (장면 조작이 여기서 수행됨)
	SetupViewTransform();

	// 장면 렌더링
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

	// 더블 버퍼링을 위한 버퍼 교환
	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	// 뷰포트 변환
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}


void SetupViewVolume()
{
	// 관측 공간 지정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)Width / (double)Height, 1.0, 10000.0);
}

void SetupViewTransform()
{
	// 모델 뷰 행렬을 단위 행렬로 초기화, M = I
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 줌 인/아웃을 위한 변환, M = I * T_zoom
	glTranslatef(0.0, 0.0, Zoom);

	// 새로운 회전을 적용, M = I * T_zoom * R_new
	glRotatef(Angle, Axis[0], Axis[1], Axis[2]);

	// 기존 회전을 적용, M = I * T_zoom * R_new * R_old	//   R_n .... * R3 * R2 * R1
	glMultMatrixf(RotMat);

	// 회전 행렬 추출, R_old = R_new * R_old
	glGetFloatv(GL_MODELVIEW_MATRIX, RotMat);
	RotMat[12] = RotMat[13] = RotMat[14] = 0.0;

	// 이동 변환을 적용, M = I * T_zoom * R_new * R_old * T_pan
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
			ManipulateMode = 1;	// 회전

		if (button == GLUT_RIGHT_BUTTON)
			ManipulateMode = 2;	// 이동
	}
	if (state == GLUT_UP)
	{
		ManipulateMode = 0;	// 리셋
		StartPt[0] = StartPt[1] = 0;
		Angle = 0.0;
	}
}

void Motion(int x, int y)
{
	// 회전축과 회전 각도 계산
	if (ManipulateMode == 1)
	{
		// 단위 구 위의 좌표 계산
		float px, py, pz, qx, qy, qz;
		GetSphereCoord(StartPt[0], StartPt[1], &px, &py, &pz);
		GetSphereCoord(x, y, &qx, &qy, &qz);

		// 회전 축과 각도 계산
		Axis[0] = py * qz - pz * qy;
		Axis[1] = pz * qx - px * qz;
		Axis[2] = px * qy - py * qx;
		Angle = 0.0;
		float len = Axis[0] * Axis[0] + Axis[1] * Axis[1] + Axis[2] * Axis[2];
		if (len > 0.0001) // 일정 변위 이상만 처리
			Angle = acos(px * qx + py * qy + pz * qz) * 180.0f / 3.141592f;
	}

	// 이동 변위 계산
	if (ManipulateMode == 2)
	{
		float dx = (float)(x - StartPt[0]) * 0.01f;
		float dy = (float)(StartPt[1] - y) * 0.01f;
		// 회전 행렬 및 역행렬
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
*	\brief 마우스 스크롤을 처리하는 콜백 함수
*
*	\param button[in]	마우스 버튼 정보(GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON)
*	\param dir[in]		스크롤의 방향
*	\param x[in]		좌측 상단을 (0, 0) 기준으로 마우스 포인터의 가로 위치
*	\param y[in]		좌측 상단을 (0, 0) 기준으로 마우스 포인터의 세로 위치
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

	float r = (*px) * (*px) + (*py) * (*py); // 원점으로부터의 거리 계산
	if (r >= 1.0f)
	{
		*px = *px / sqrt(r);
		*py = *py / sqrt(r);
		*pz = 0.0f;
	}
	else
		*pz = sqrt(1.0f - r);  // 일반적인 경우
}
