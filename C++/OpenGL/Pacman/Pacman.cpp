#include "DrawObject.h"


// ���� ������ �� ������Ʈ ũ�� ����
int Width = 600, Height = 600;
int pacX = 300, pacY = 300;  
int count = 0;               
int pacSize = 25, ghostSize = 25, foodSize = 15;
int eyeX = pacX + 5, eyeY = pacY + 15;  
int num;                               
int num2;                              
int xArray[20], yArray[20];            
int xarray[20], yarray[20];            
int sival = 0, sival2 = 0, sival3 = 0;
int maxX = Width - 5, maxY = Height - 5; 
int minX = 5, minY = 5;
int mouseI = -20, mouseU = 20;         
int state;                             
int countghost = 0;                    

double distance1[10];                  
double distance2[10];                  
double distance3[10][10];              
float takeTime;                        
clock_t start = clock();


// �Լ� ����
void Display();
void Reshape(int w, int h);
void ArrowCallBack(int key, int x, int y);
void Timer(int id);
void Close();
void draw_pacman(double r, double g, double b);
void draw_ghost(double r, double g, double b);
void drawFood(double r, double g, double b);

int main(int argc, char** argv) {
	srand(time(NULL));
	num = rand() % 7 + 1; // �ʱ� ���� ���� ���� (�ִ� 7��)
	num2 = rand() % 3 + 1; // �ʱ� ���� ���� ���� (�ִ� 3��)

	// OpenGL �� GLUT �ʱ�ȭ
	glutInit(&argc, argv);
	glutInitWindowSize(Width, Height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("PacMan Game");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(ArrowCallBack);
	glutTimerFunc(100, Timer, 0);
	glutCloseFunc(Close);
	glutMainLoop();

	return 0;
}

void Display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ȭ�� ���� ����
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);

	glMatrixMode(GL_MODELVIEW);

	// ���� ������Ʈ �׸���
	draw_pacman(1.0, 1.0, 0.0); // �Ѹ� �׸���
	draw_ghost(0.5, 0.5, 0.5);  // ���� �׸���
	drawFood(1.0, 0.0, 0.0);    // ���� �׸���

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void ArrowCallBack(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if (pacX - pacSize <= minX) {		// ������ ���� ���� �̵� ����
			return;
		}
		eyeX = pacX - 5 - count * 2;
		eyeY = pacY + 15 + count * 2;
		pacX -= 30;
		eyeX -= 30;
		mouseI = 160;						// pacman ���⼺ ��Ÿ���� ���� ���� ����
		mouseU = 200;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (pacX + pacSize >= maxX) {		// ������ ���� ���� �̵� ����
			return;
		}
		eyeX = pacX + 5 + count * 2;
		eyeY = pacY + 15 + count * 2;
		pacX += 30;
		eyeX += 30;
		mouseI = -20;						// pacman ���⼺ ��Ÿ���� ���� ���� ����
		mouseU = 20;
	}
	if (key == GLUT_KEY_UP)
	{
		if (pacY + pacSize >= maxY) {		// ������ ���� ���� �̵� ����
			return;
		}
		eyeX = pacX - 15 - count * 2;
		eyeY = pacY + 10 + count * 2;
		pacY += 30;
		eyeY += 30;
		mouseI = 70;						// pacman ���⼺ ��Ÿ���� ���� ���� ����
		mouseU = 110;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (pacY - pacSize <= minY) {		// ������ ���� ���� �̵� ����
			return;
		}
		eyeX = pacX + 15 + count * 2;
		eyeY = pacY - 10 - count * 2;
		pacY -= 30;
		eyeY -= 30;
		mouseI = 250;						// pacman ���⼺ ��Ÿ���� ���� ���� ����
		mouseU = 290;
	}
}

void Timer(int id)
{
	for (int i = 0; i < num2; i++) {
		if (pacX > xarray[i]) {					// ghost�� pacman�� �Ѿƿ����� ����
			xarray[i] += (3 + countghost);		// ghost�� fruit ���������� �ӵ� ����
		}
		else {
			xarray[i] -= (3 + countghost);
		}
		if (pacY > yarray[i]) {
			yarray[i] += (3 + countghost);
		}
		else {
			yarray[i] -= (3 + countghost);
		}

		distance1[i] = sqrt(pow((double)pacX - (double)xarray[i], 2) + pow((double)pacY - (double)yarray[i], 2));
	}


	for (int j = 0; j < num2; j++) {
		if (distance1[j] <= (double)pacSize + (double)ghostSize) {		// pacman�� ghost���� ������ ���
			state = 1;			// ���� ���� ����
			Close();
			exit(0);
		}
	}
	takeTime = (float)(clock() - start) / CLOCKS_PER_SEC;
	if (takeTime >= (float)30) {		// 30 �� ���� ghost���� ������ �ʴ� ���
		state = 0;				// ���� ���� ����
		Close();
		exit(0);
	}
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 0);
}

void Close() {
	if (state == 0) {			// ���� ���� 
		printf("-----TIME OVER-----\n");
		printf("You win!!\n");
		printf("Collected Fruit : %d\n", count);
	}
	else {						// ���� ����
		printf("You Lose...\n");
		printf("Collected Fruit : %d\n", count);	// ���� fruit ��
		printf("Time Later : %.4f\n", takeTime);	// ���� ���� �� �ɸ� �ð�
	}
}