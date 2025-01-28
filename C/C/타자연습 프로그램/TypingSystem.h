#ifndef __TYPING_SYSTEM_H__
#define __TYPING_SYSTEM_H__

#include "Header.h"
#include "User.h"

class TypingSystem {
private:
	// ������� �����
	std::vector<std::string> sentences;

	// ���� �����
	User* currentUser = nullptr;

	// ��ũ�κ��� �����͸� �о�ͼ� ���� ����Ʈ�� �ʱ�ȭ�ϴ� �Լ�
	void loadData();
public:

	void printData();	

	void start();

	void printMenu();

	char getChar();

	std::string getString();

	void typingStart();

	int compare(const std::string& original, const std::string& input);

};
#endif // !__TYPING_SYSTEM_H__

