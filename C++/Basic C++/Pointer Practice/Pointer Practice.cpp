#include <iostream>
using namespace std;

struct StatInfo {
	int hp;
	int attack;
	int defence;
};

// 기본 (구조체 복사 - 메모리 복사) - 데이터가 작을 때는 상관없음
StatInfo CreatePlayer() {
	StatInfo info;

	cout << "플레이어 생성" << endl;
	info.hp = 100;
	info.attack = 10;
	info.defence = 2;

	return info;
}

// 데이터 크기가 커진다면 포인터가 유리
void CreateMonster(StatInfo* info) {
	cout << "몬스터 생성" << endl;

	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

// 오류
// 이 함수 안에서만 유효한 변수를 만들어 주소를 반환함.
// main에서 호출된 뒤 함수의 변수는 메모리 구조에서 사라짐.
StatInfo* CreatePlayer2() {
	StatInfo info;

	cout << "플레이어 생성" << endl;
	info.hp = 100;
	info.attack = 10;
	info.defence = 2;

	return &info;
}

void Battle(StatInfo* player, StatInfo* monster) {
	while (true)
	{
		int damage = player->attack - monster->defence;
		if (damage < 0)
			damage = 0;

		monster->hp -= damage;
		if (monster->hp < 0)
			monster->hp = 0;

		cout << "몬스터 HP : " << monster->hp << endl;

		if (monster->hp == 0)
			return;

		damage = monster->attack - player->defence;
		if (damage < 0)
			damage = 0;

		player->hp -= damage;
		if (player->hp < 0)
			player->hp = 0;

		cout << "플레이어 HP : " << player->hp << endl;

		if (player->hp == 0)
			return;
	}
}

int main() {
	StatInfo player;
	player = CreatePlayer();

	StatInfo monster;
	CreateMonster(&monster);

	Battle(&player, &monster);
}