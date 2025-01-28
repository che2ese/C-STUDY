#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <cstdlib>

int number_counter = 1;

class Employee {
public:
	int no;
	char name[20];
	int gen;
	char rank[20];

	Employee(char* name, int gen, char* rank) { //생성자 : class 소환시 자동으로 초기화
		strcpy(this->name, name);
		this->gen = gen;
		strcpy(this->rank, rank);
		no = number_counter;
		number_counter++;
	}

	void printinfo() {
		printf("사원번호: %d\n", no);
		printf("이름 : %s\n", name);
		printf("성별 : %s\n", gen == 1? "남성" : "여성");
		printf("직급 : %s\n\n", rank);
	}
};

int getint(const char* prompt);
char* getchar(const char* prompt);
