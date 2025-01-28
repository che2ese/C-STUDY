#include "Header.h"

int main() {

	Employee* employee[100];
	int count = 0;

	for (;;) {
		printf("\n����� �Է��ϼ���\n");
		printf("1. ��� ����\n");
		printf("2. ��� �߰�\n");
		printf("3. ��� ����\n");
		printf("4. ���α׷��� �����ϰڽ��ϴ�.\n");

		int input;
		fseek(stdin, 0, SEEK_END);
		scanf("%d", &input);

		if (input == 1) { //��� ����
			for (int i = 0; i < count; i++) {
				employee[i]->printinfo();
			}
		}
		else if (input == 2) { //��� �߰�
			char* name = getchar("\n�̸��� �Է��ϼ���:");
			int gen = getint("������ �Է��ϼ���(1 : ���� 2 : ����):");
			char* rank = getchar("������ �Է��ϼ���:");
			
			Employee* e = new Employee(name, gen, rank); //������ ȣ��
			delete[] name;
			delete[] rank; //�����Ҵ� �޸� ����

			employee[count++] = e; // �ڷᱸ���� �߰�
		}
		else if (input == 3) { // ��� ����
			int delete_no = getint("������ ����� ��� ��ȣ�� �Է��ϼ���:");
			int deleteindex = -1; 
			for (int i = 0; i < count; i++) {
				if (delete_no == employee[i]->no) { //������ ����� ��ȣ�� ����
					delete employee[i]; //�� ����� ���� ����
					deleteindex = i; //������ ��ȣ�� deleteindex��� ����
					break;
				}
			}
			if (deleteindex >= 0) { 
				for (int i = deleteindex; i < count; i++) {
					employee[i] = employee[i + 1]; //��ĭ�� �ڷ� �б�
				}
			}
			count--;
		}
		else if (input == 4) {
			printf("���α׷��� �����ϰڽ��ϴ�.");
			break;
		}
		else {
			printf("�߸��� �Է��Դϴ�.\n");
			continue;
		}
	}
}

int getint(const char* prompt) {
	int input;
	printf("%s", prompt);
	fseek(stdin, 0, SEEK_END);
	scanf("%d", &input);
	return input;
}

char* getchar(const char* prompt) {
	char* input = new char[100];
	printf("%s", prompt);
	fseek(stdin, 0, SEEK_END);
	scanf("%99[^\n]s", input);
	return input;
}