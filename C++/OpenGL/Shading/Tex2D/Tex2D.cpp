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

// 텍스처 매핑을 위한 변수
GLuint TexId[2];

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
unsigned char *ReadBmpFile(const char *fname, int *w, int *h);

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

	// 조명 모델 활성화
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// 텍스처 매핑 모드 설정
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // 옵션 : GL_MODULATE, GL_REPLACE

	// 텍스처 아이디 2개 생성
	glGenTextures(2, TexId);

	// 2D 텍스처 생성
	int w, h;
	unsigned char *pImage;
	pImage = ReadBmpFile("./tex/texture0.bmp", &w, &h);
	glBindTexture(GL_TEXTURE_2D, TexId[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	delete[] pImage;

	pImage = ReadBmpFile("./tex/texture1.bmp", &w, &h);
	glBindTexture(GL_TEXTURE_2D, TexId[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pImage);
	delete[] pImage;	

	// 텍스춰 좌표의 확장옵션
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // 옵션: GL_REPEAT (1.2 -> 0.2), GL_CLAMP (1.2 -> 1.0)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // 옵션: GL_REPEAT, GL_CLAMP

	// 확장/축소 필터
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // 옵션: GL_NEAREST, GL_LINEAR
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // 옵션: GL_NEAREST, GL_LINEAR

	// 환경맵을 위한 자동 텍스춰 좌표 생성
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
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

	// 재질을 설정한다.
	GLfloat mat_ambient[] = { 0.1f, 0.1f, 0.1f, 0.0f };
	GLfloat mat_diffuse[] = { 0.7f, 0.7f, 0.7f, 0.0f };
	GLfloat mat_specular[] = { 0.9f, 0.9f, 0.9f, 0.8f };
	GLfloat mat_shininess = 32.0;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mat_shininess);

	// 텍스처 매핑을 활성화 한다.
	glEnable(GL_TEXTURE_2D);

	// 텍스처 TexId[0]로 텍스처 매핑을 한다.
	glBindTexture(GL_TEXTURE_2D, TexId[0]);
	glBegin(GL_POLYGON);
	{
		glTexCoord2d(0.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-6.0f, -2.0f, 0.0);

		glTexCoord2d(1.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-2.0f, -2.0f, 0.0);

		glTexCoord2d(1.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-2.0f, 2.0f, 0.0);

		glTexCoord2d(0.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-6.0f, 2.0f, 0.0);
	}
	glEnd();

	// 텍스처 TexId[1]로 텍스처 매핑을 한다.
	glBindTexture(GL_TEXTURE_2D, TexId[1]);
	glBegin(GL_POLYGON);
	{
		glTexCoord2d(0.3, 0.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(2.0f, -2.0f, 0.0f);

		glTexCoord2d(0.5, 0.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(6.0f, -2.0f, 0.0f);

		glTexCoord2d(1.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(6.0f, 2.0f, 0.0f);

		glTexCoord2d(0.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(2.0f, 2.0f, 0.0f);
	}
	glEnd();

	// 환경 매핑을 수행한다.
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, TexId[1]);
	//glutSolidTeapot(2.0);
	//glutSolidIcosahedron();
	glutSolidTeacup(3.0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	// 텍스처 매핑을 비활성화 한다.
	glDisable(GL_TEXTURE_2D);

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
	glDisable(GL_LIGHTING);
	glColor3f(0.7f, 0.7f, 0.7f);
	for (int x = -10; x <= 10; x++)
	{
		if (x == 0)
			continue;		
		glBegin(GL_LINES);
		glVertex3f((float)x, 0.0, -10.0f);
		glVertex3f((float)x, 0.0, 10.0f);
		glVertex3f(-10.0f, 0.0, (float)x);
		glVertex3f(10.0f, 0.0, (float)x);
		glEnd();
	}

	glLineWidth(2.0f);
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINES);
	glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(0.0f, 0.0, 10.0f);
	glEnd();
	glLineWidth(1.0f);
	glEnable(GL_LIGHTING);
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

/*!
*	\brief	이미지 파일(bmp)을 로드하는 함수
*
*	\param	fname[in]	로드할 파일명
*	\param	w[out]		이미지의 너비가 저장됨
*	\param	h[out]		이지미의 높이가 저장됨
*
*	\return	이미지 데이터의 배열을 반환한다.
*/
unsigned char *ReadBmpFile(const char *fname, int *w, int *h)
{
	// 파일을 오픈한다.
	FILE *fp;
	fopen_s(&fp, fname, "rb");
	
	// BMP 파일의 헤더 정보를 읽는다.
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	RGBTRIPLE rgb;
	fread(&fileheader, sizeof(fileheader), 1, fp);
	fseek(fp, sizeof(fileheader), SEEK_SET); // Jump the fileheader
	fread(&infoheader, sizeof(infoheader), 1, fp); // and read the infoheader

	// 헤더 정보로 너비와 높이를 설정한다.
	*w = infoheader.biWidth;
	*h = infoheader.biHeight;
	
	// 이미지 데이터를 저장할 배열을 생성한다.
	int size = infoheader.biWidth * infoheader.biHeight;
	unsigned char *pData = new unsigned char[size * 4];
	memset(pData, 0, size * 4);

	// 이미지 데이터를 배열에 복사한다.
	for (int i = 0; i < size; ++i)
	{
		fread(&rgb, sizeof(rgb), 1, fp); // load RGB value
		pData[i * 4 + 0] = rgb.rgbtRed;
		pData[i * 4 + 1] = rgb.rgbtGreen;
		pData[i * 4 + 2] = rgb.rgbtBlue;
		pData[i * 4 + 3] = 255; // Alpha value
	}
	fclose(fp);

	// 배열을 반환한다.
	return pData;
}