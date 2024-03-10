#ifndef  __USER_H__
#define __USER_H__

#include "Header.h"

class User {
public:
	// 파일명
	std::string username;

	// 평균 타자 속도
	float avgSpeed = 0.0f;
	
	// 타자 문장을 얼마나 입력했는지
	int typingCount = 0;

	User(const std::string& username);
	void save();
	void load();

	void printUserInfo();

};
#endif // ! __USER_H__

