#include "DrawObject.h"


// 게임 윈도우 및 오브젝트 크기 설정
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


// 함수 선언
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
	num = rand() % 7 + 1; // 초기 과일 개수 설정 (최대 7개)
	num2 = rand() % 3 + 1; // 초기 유령 개수 설정 (최대 3개)

	// OpenGL 및 GLUT 초기화
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 화면 배경색 설정
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);

	glMatrixMode(GL_MODELVIEW);

	// 게임 오브젝트 그리기
	draw_pacman(1.0, 1.0, 0.0); // 팩맨 그리기
	draw_ghost(0.5, 0.5, 0.5);  // 유령 그리기
	drawFood(1.0, 0.0, 0.0);    // 과일 그리기

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
		if (pacX - pacSize <= minX) {		// 윈도우 범위 내로 이동 제한
			return;
		}
		eyeX = pacX - 5 - count * 2;
		eyeY = pacY + 15 + count * 2;
		pacX -= 30;
		eyeX -= 30;
		mouseI = 160;						// pacman 방향성 나타내기 위한 입의 각도
		mouseU = 200;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		if (pacX + pacSize >= maxX) {		// 윈도우 범위 내로 이동 제한
			return;
		}
		eyeX = pacX + 5 + count * 2;
		eyeY = pacY + 15 + count * 2;
		pacX += 30;
		eyeX += 30;
		mouseI = -20;						// pacman 방향성 나타내기 위한 입의 각도
		mouseU = 20;
	}
	if (key == GLUT_KEY_UP)
	{
		if (pacY + pacSize >= maxY) {		// 윈도우 범위 내로 이동 제한
			return;
		}
		eyeX = pacX - 15 - count * 2;
		eyeY = pacY + 10 + count * 2;
		pacY += 30;
		eyeY += 30;
		mouseI = 70;						// pacman 방향성 나타내기 위한 입의 각도
		mouseU = 110;
	}
	if (key == GLUT_KEY_DOWN)
	{
		if (pacY - pacSize <= minY) {		// 윈도우 범위 내로 이동 제한
			return;
		}
		eyeX = pacX + 15 + count * 2;
		eyeY = pacY - 10 - count * 2;
		pacY -= 30;
		eyeY -= 30;
		mouseI = 250;						// pacman 방향성 나타내기 위한 입의 각도
		mouseU = 290;
	}
}

void Timer(int id)
{
	for (int i = 0; i < num2; i++) {
		if (pacX > xarray[i]) {					// ghost가 pacman을 쫓아오도록 구현
			xarray[i] += (3 + countghost);		// ghost가 fruit 먹을때마다 속도 증가
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
		if (distance1[j] <= (double)pacSize + (double)ghostSize) {		// pacman이 ghost에게 잡히는 경우
			state = 1;			// 게임 실패 상태
			Close();
			exit(0);
		}
	}
	takeTime = (float)(clock() - start) / CLOCKS_PER_SEC;
	if (takeTime >= (float)30) {		// 30 초 동안 ghost에게 잡히지 않는 경우
		state = 0;				// 게임 성공 상태
		Close();
		exit(0);
	}
	glutPostRedisplay();
	glutTimerFunc(100, Timer, 0);
}

void Close() {
	if (state == 0) {			// 게임 성공 
		printf("-----TIME OVER-----\n");
		printf("You win!!\n");
		printf("Collected Fruit : %d\n", count);
	}
	else {						// 게임 실패
		printf("You Lose...\n");
		printf("Collected Fruit : %d\n", count);	// 먹은 fruit 수
		printf("Time Later : %.4f\n", takeTime);	// 게임 실패 시 걸린 시간
	}
}