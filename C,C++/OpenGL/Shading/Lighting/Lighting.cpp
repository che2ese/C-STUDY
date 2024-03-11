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
float Axis[3] = {1.0, 0.0, 0.0};
float Angle = 0.0;
float RotMat[16] = {1, 0, 0, 0, 
					0, 1, 0, 0, 
					0, 0, 1, 0, 
					0, 0, 0, 1};
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

struct Vertex
{
	double P[3];
	double N[3];
};

struct Face
{
	int vIdx[3];
};

struct Object
{
	std::vector<Vertex> VertList;
	std::vector<Face> FaceList;
};
Object MyModel;

void LoadModel(const char *fname);
void Sub(double out[3], double a[3], double b[3]);
void Add(double out[3], double a[3], double b[3]);
void Cross(double out[3], double a[3], double b[3]);
void RenderModelAsPoint();
void RenderModelAsWire();
void RenderModelAsTri();

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

void LoadModel(const char *fname)
{
	// Open the user-specified file
	FILE *fp;
	fopen_s(&fp, fname, "r");

	// Read the numbers of vertex and triangle
	int vnum, fnum;
	fscanf_s(fp, "%d", &vnum);
	fscanf_s(fp, "%d", &fnum);

	// Read vertex coordinates
	for (int i = 0; i < vnum; ++i)
	{
		Vertex v;
		fscanf_s(fp, "%lf%lf%lf", &v.P[0], &v.P[1], &v.P[2]);
		v.N[0] = v.N[1] = v.N[2] = 0.0;
		MyModel.VertList.push_back(v);
	}

	// Read triangles
	for (int i = 0; i < fnum; ++i)
	{
		// Read vertex indices from a file.
		int vidx0, vidx1, vidx2;
		fscanf_s(fp, "%d%d%d", &vidx0, &vidx1, &vidx2);

		Face f;
		f.vIdx[0] = vidx0;
		f.vIdx[1] = vidx1;
		f.vIdx[2] = vidx2;
		MyModel.FaceList.push_back(f);

		// Compute the normal vector of a triangle
		double e1[3], e2[3], n[3];
		double *p0 = MyModel.VertList[vidx0].P;
		double *p1 = MyModel.VertList[vidx1].P;
		double *p2 = MyModel.VertList[vidx2].P;
		Sub(e1, p1, p0);
		Sub(e2, p2, p0);
		Cross(n, e1, e2);

		// Add the normal vector to each vertex
		double *n0 = MyModel.VertList[vidx0].N;
		double *n1 = MyModel.VertList[vidx1].N;
		double *n2 = MyModel.VertList[vidx2].N;
		Add(n0, n0, n);
		Add(n1, n1, n);
		Add(n2, n2, n);
	}

	// Normalize the normal vector assigned to each vertex
	for (int i = 0; i < vnum; ++i)
	{
		double *n = MyModel.VertList[i].N;
		double norm = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
		n[0] /= norm;
		n[1] /= norm;
		n[2] /= norm;
	}
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
	   
	// 모델을 로드한다.
	LoadModel("..\\model\\bunny.txt");
		
	// 메시지 루프 진입
	glutMainLoop();
	return 0;
}

void InitOpenGL()
{
	// 깊이 테스트를 활성화
	glEnable(GL_DEPTH_TEST);

	// OpenGL 면제거를 활성화
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// 조명 모델 활성화
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_FLAT);  //	옵션 = GL_FLAT, GL_SMOOTH

	switch (0)
	{
		// 점광원
		case 0:
		{
			GLfloat light0_position[] = { 0.0f, 0.0f, 5.0f, 1.0f };
			GLfloat light0_ambient[] = { 0.2, 0.2, 0.2 };
			GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8 };
			GLfloat light0_specular[] = { 0.7, 0.7, 0.7 };
			glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
		}
		break;

		// 방향성 광원
		case 1:
		{
			GLfloat light0_position[] = { 0.0f, 0.0f, 5.0f, 0.0f };
			GLfloat light0_ambient[] = { 0.2, 0.2, 0.2 };
			GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8 };
			GLfloat light0_specular[] = { 0.7, 0.7, 0.7 };
			glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
		}
		break;

		// 집중 광원
		case 2:
		{
			GLfloat light0_position[] = { 0.0f, 5.0f, 5.0f, 1.0f };
			GLfloat light0_direction[] = { 0.0f, 0.0f, -1.0f, 0.0f };
			GLfloat light0_ambient[] = { 0.2, 0.2, 0.2 };
			GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8 };
			GLfloat light0_specular[] = { 0.7, 0.7, 0.7 };

			glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 7.0);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 8);
		}
		break;
	}
}

void Reshape(int w, int h)
{
	// 뷰포트 변환
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
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

	// 모델을 삼각형으로 렌더링 한다.
	RenderModelAsTri();

	// 더블 버퍼링을 위한 버퍼 교환
	glutSwapBuffers();
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
		Axis[0] = py * qz -pz * qy; 
		Axis[1] = pz * qx -px * qz; 
		Axis[2] = px * qy -py * qx;
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

void RenderModelAsPoint()
{
	// 조명을 비활성화
	glDisable(GL_LIGHTING);

	// Specify the color
	glColor3f(0.0, 0.0, 0.0);

	// Draw the model as point clouds
	glBegin(GL_POINTS);
	for (int i = 0; i < MyModel.VertList.size(); ++i)
	{
		glVertex3dv(MyModel.VertList[i].P);
	}
	glEnd();

	// 조명을 활성화
	glEnable(GL_LIGHTING);
}


void RenderModelAsWire()
{
	// 조명을 비활성화
	glDisable(GL_LIGHTING);

	// Specify the color
	glColor3f(0.0, 0.0, 0.0);

	// Draw the model as wireframe
	for (int i = 0; i < MyModel.FaceList.size(); ++i)
	{
		int idx0, idx1, idx2;
		idx0 = MyModel.FaceList[i].vIdx[0];
		idx1 = MyModel.FaceList[i].vIdx[1];
		idx2 = MyModel.FaceList[i].vIdx[2];

		glBegin(GL_LINE_LOOP);
		glVertex3dv(MyModel.VertList[idx0].P);
		glVertex3dv(MyModel.VertList[idx1].P);
		glVertex3dv(MyModel.VertList[idx2].P);
		glEnd();
	}

	// 조명을 활성화
	glEnable(GL_LIGHTING);
}

void RenderModelAsTri()
{
	// 재질을 설정한다.
	float mat0_ambient[] = { 0.3, 0.0, 0.0 };
	float mat0_diffuse[] = { 0.6, 0.6, 0.0 };
	float mat0_specular[] = { 0.9, 0.9, 0.9 };
	float mat0_shininess = 64;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat0_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mat0_shininess);
	
	// Draw the model as triangles
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < MyModel.FaceList.size(); ++i)
	{
		int idx0, idx1, idx2;
		idx0 = MyModel.FaceList[i].vIdx[0];
		idx1 = MyModel.FaceList[i].vIdx[1];
		idx2 = MyModel.FaceList[i].vIdx[2];

		glNormal3dv(MyModel.VertList[idx0].N);
		glVertex3dv(MyModel.VertList[idx0].P);

		glNormal3dv(MyModel.VertList[idx1].N);
		glVertex3dv(MyModel.VertList[idx1].P);

		glNormal3dv(MyModel.VertList[idx2].N);
		glVertex3dv(MyModel.VertList[idx2].P);
	}
	glEnd();
}