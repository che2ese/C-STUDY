#include <iostream>
using namespace std;

struct StatInfo {
	int hp;
	int attack;
	int defence;
};

// �⺻ (����ü ���� - �޸� ����) - �����Ͱ� ���� ���� �������
StatInfo CreatePlayer() {
	StatInfo info;

	cout << "�÷��̾� ����" << endl;
	info.hp = 100;
	info.attack = 10;
	info.defence = 2;

	return info;
}

// ������ ũ�Ⱑ Ŀ���ٸ� �����Ͱ� ����
void CreateMonster(StatInfo* info) {
	cout << "���� ����" << endl;

	info->hp = 40;
	info->attack = 8;
	info->defence = 1;
}

// ����
// �� �Լ� �ȿ����� ��ȿ�� ������ ����� �ּҸ� ��ȯ��.
// main���� ȣ��� �� �Լ��� ������ �޸� �������� �����.
StatInfo* CreatePlayer2() {
	StatInfo info;

	cout << "�÷��̾� ����" << endl;
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

		cout << "���� HP : " << monster->hp << endl;

		if (monster->hp == 0)
			return;

		damage = monster->attack - player->defence;
		if (damage < 0)
			damage = 0;

		player->hp -= damage;
		if (player->hp < 0)
			player->hp = 0;

		cout << "�÷��̾� HP : " << player->hp << endl;

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