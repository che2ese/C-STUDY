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
float Axis[3] = {1.0, 0.0, 0.0};
float Angle = 0.0;
float RotMat[16] = {1, 0, 0, 0, 
					0, 1, 0, 0, 
					0, 0, 1, 0, 
					0, 0, 0, 1};
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
	   
	// ���� �ε��Ѵ�.
	LoadModel("..\\model\\bunny.txt");
		
	// �޽��� ���� ����
	glutMainLoop();
	return 0;
}

void InitOpenGL()
{
	// ���� �׽�Ʈ�� Ȱ��ȭ
	glEnable(GL_DEPTH_TEST);

	// OpenGL �����Ÿ� Ȱ��ȭ
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ���� �� Ȱ��ȭ
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_FLAT);  //	�ɼ� = GL_FLAT, GL_SMOOTH

	switch (0)
	{
		// ������
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

		// ���⼺ ����
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

		// ���� ����
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
	// ����Ʈ ��ȯ
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
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

	// ���� �ﰢ������ ������ �Ѵ�.
	RenderModelAsTri();

	// ���� ���۸��� ���� ���� ��ȯ
	glutSwapBuffers();
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
		Axis[0] = py * qz -pz * qy; 
		Axis[1] = pz * qx -px * qz; 
		Axis[2] = px * qy -py * qx;
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

void RenderModelAsPoint()
{
	// ������ ��Ȱ��ȭ
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

	// ������ Ȱ��ȭ
	glEnable(GL_LIGHTING);
}


void RenderModelAsWire()
{
	// ������ ��Ȱ��ȭ
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

	// ������ Ȱ��ȭ
	glEnable(GL_LIGHTING);
}

void RenderModelAsTri()
{
	// ������ �����Ѵ�.
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