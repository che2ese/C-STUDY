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

	Employee(char* name, int gen, char* rank) { //������ : class ��ȯ�� �ڵ����� �ʱ�ȭ
		strcpy(this->name, name);
		this->gen = gen;
		strcpy(this->rank, rank);
		no = number_counter;
		number_counter++;
	}

	void printinfo() {
		printf("�����ȣ: %d\n", no);
		printf("�̸� : %s\n", name);
		printf("���� : %s\n", gen == 1? "����" : "����");
		printf("���� : %s\n\n", rank);
	}
};

int getint(const char* prompt);
char* getchar(const char* prompt);
