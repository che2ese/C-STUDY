#include "User.h"

User::User(const std::string& username) {
	this->username = username;

	FILE* fp = fopen(username.c_str(), "r");
	bool exists = fp != nullptr;

	if(exists) fclose(fp);
	
	if (exists) {
		putStringOnPosition(6, 5, "����ڰ� �����մϴ�... �ҷ�������...");
		load();
		putStringOnPosition(6, 6, "����Ϸ��� ���͸� �Է����ּ���.");
		fseek(stdin, 0, SEEK_END);
		fgetc(stdin);
	}

	else {
		putStringOnPosition(6, 5, "����ڰ� �������� �ʽ��ϴ�... ���� �������...");
		save();
		putStringOnPosition(6, 6, "����Ϸ��� ���͸� �Է����ּ���.");
		fseek(stdin, 0, SEEK_END);
		fgetc(stdin);
	}
}

void User::save()
{
	FILE* outfile = fopen(username.c_str(), "w");
	fprintf(outfile, "%f\n", avgSpeed);
	fprintf(outfile, "%d", typingCount);
	fclose(outfile);
}

void User::load()
{
	FILE* infile = fopen(username.c_str(), "r");
	fscanf(infile, "%f", &avgSpeed);
	fgetc(infile);
	fscanf(infile, "%d", &typingCount);
	fclose(infile);
}

void User::printUserInfo()
{	
	char avgSpeed[20];
	sprintf(avgSpeed, "��� Ÿ�� : %f", this->avgSpeed);

	char count[20];
	sprintf(count, "Ÿ���� Ƚ�� : %d", this->typingCount);

	putStringOnPosition(6, 5, avgSpeed);
	putStringOnPosition(6, 6, count);
	putStringOnPosition(6, 7, "��� �Ϸ��� ���� Ű�� �����ּ���.");
	fseek(stdin, 0, SEEK_END);
	fgetc(stdin);
}
