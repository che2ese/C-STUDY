#include "Header.h"

int main() {

	Employee* employee[100];
	int count = 0;

	for (;;) {
		printf("\n명령을 입력하세요\n");
		printf("1. 사원 보기\n");
		printf("2. 사원 추가\n");
		printf("3. 사원 삭제\n");
		printf("4. 프로그램을 종료하겠습니다.\n");

		int input;
		fseek(stdin, 0, SEEK_END);
		scanf("%d", &input);

		if (input == 1) { //사원 보기
			for (int i = 0; i < count; i++) {
				employee[i]->printinfo();
			}
		}
		else if (input == 2) { //사원 추가
			char* name = getchar("\n이름을 입력하세요:");
			int gen = getint("성별을 입력하세요(1 : 남성 2 : 여성):");
			char* rank = getchar("직급을 입력하세요:");
			
			Employee* e = new Employee(name, gen, rank); //생성자 호출
			delete[] name;
			delete[] rank; //동적할당 메모리 삭제

			employee[count++] = e; // 자료구조에 추가
		}
		else if (input == 3) { // 사원 삭제
			int delete_no = getint("삭제할 사원의 사원 번호를 입력하세요:");
			int deleteindex = -1; 
			for (int i = 0; i < count; i++) {
				if (delete_no == employee[i]->no) { //삭제할 사원의 번호를 지정
					delete employee[i]; //그 사원의 정보 삭제
					deleteindex = i; //삭제된 번호를 deleteindex라고 저장
					break;
				}
			}
			if (deleteindex >= 0) { 
				for (int i = deleteindex; i < count; i++) {
					employee[i] = employee[i + 1]; //한칸씩 뒤로 밀기
				}
			}
			count--;
		}
		else if (input == 4) {
			printf("프로그램을 종료하겠습니다.");
			break;
		}
		else {
			printf("잘못된 입력입니다.\n");
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