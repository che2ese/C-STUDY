#include <iostream>
using namespace std;

enum PlayerType{
    PT_None = 0,
    PT_Knight = 1,
    PT_Archer = 2,
    PT_Mage = 3
};

enum MonsterType{
    MT_None = 0,
    MT_Slime = 1,
    MT_Orc = 2,
    MT_Skeleton = 3
};

struct StatInfo{ // 구조체 
    int hp;
    int attack;
    int defence;
};

PlayerType playerType;
StatInfo playerStat;

MonsterType monsterType;
StatInfo monsterStat;

void EnterLobby();
void SelectPlayer();
void EnterField();
void CreateRandomMonster();
void EnterBattle();
void WaitForNextKey();

int main(){
    // 랜덤 시드값 설정
    srand(time(0));
    EnterLobby();
}

void EnterLobby(){
    while (true) {
        cout << "---------------" << endl;
        cout << "로비에 입장했습니다." << endl;
        cout << "---------------" << endl;
        
        // 플레이어 직업 선택
        SelectPlayer();

        cout << "---------------" << endl;
        cout << "(1) 필드 입장 (2) 게임 종료" << endl;
        cout << "> ";

        int input;
        cin >> input;

        if(input == 1){
            EnterField();
        }
        else{
            cout << "---------------" << endl;
            cout << "게임을 종료합니다." << endl;
            cout << "---------------" << endl;
            break;
        }
    }
}

void SelectPlayer()
{
    while (true) // 직업이 아닌 다른 것을 누르면 루프
    {        
        cout << "---------------" << endl;
        cout << "직업을 골라주세요." << endl;
        cout << "(1) 기사 (2) 궁수 (3) 법사" << endl;
        cout << "> ";

        int choice;
        cin >> choice;

        if(choice == PT_Knight){
            cout << "기사 생성중..." << endl;
            playerStat.hp = 150;
            playerStat.attack = 10;
            playerStat.defence = 5;
            playerType = PT_Knight;
            break;
        }
        else if(choice == PT_Archer){
            cout << "궁수 생성중..." << endl;
            playerStat.hp = 100;
            playerStat.attack = 15;
            playerStat.defence = 3;
            playerType = PT_Archer;
            break;
        }
        else if(choice == PT_Mage){
            cout << "법사 생성중..." << endl;
            playerStat.hp = 80;
            playerStat.attack = 25;
            playerStat.defence = 0;
            playerType = PT_Mage;
            break;
        }
    }
}

void EnterField()
{
    while(true){
        cout << "---------------" << endl;
        cout << "필드에 입장했습니다." << endl;
        cout << "---------------" << endl;

        cout << "[Player] HP : " << playerStat.hp << " / ATT : " << playerStat.attack << " / DEF : " << playerStat.defence << endl;

        // 몬스터 스폰
        CreateRandomMonster();

        cout << "---------------" << endl;
        cout << "(1) 전투 (2) 도주" << endl;
        cout << "> ";

        int input;
        cin >> input;

        if(input == 1){
            EnterBattle();

            if(playerStat.hp == 0){
                break;
            }
        }
        else{
            cout << "---------------" << endl;
            cout << "도망쳤습니다." << endl;
            cout << "---------------" << endl;
            break;
        }
    }
}

void CreateRandomMonster()
{
    int randomChoice = 1 + rand() % 3; // rand 쓸 때는 항상 시드 값 설정
    switch (randomChoice)
    {
        case MT_Slime:
            cout << "슬라임 생성중...! (HP:30 / ATT:2 / DEF:0)" << endl;
            monsterStat.hp = 30;
            monsterStat.attack = 2;
            monsterStat.defence = 0;
            monsterType = MT_Slime;
            break;
        case MT_Orc:
            cout << "오크 생성중...! (HP:40 / ATT:10 / DEF:3)" << endl;
            monsterStat.hp = 40;
            monsterStat.attack = 10;
            monsterStat.defence = 3;
            monsterType = MT_Orc;
            break;
        case MT_Skeleton:
            cout << "해골 생성중...! (HP:80 / ATT:15 / DEF:5)" << endl;
            monsterStat.hp = 80;
            monsterStat.attack = 15;
            monsterStat.defence = 5;
            monsterType = MT_Skeleton;
            break;
    }
}

void EnterBattle()
{
    while(true){
        int damage = playerStat.attack - monsterStat.defence;
        if(damage < 0){
            damage = 0; // 몬스터의 방어력이 더 크면 피해 없음
        }

        // 선빵
        monsterStat.hp -= damage;
        if(monsterStat.hp < 0){
            monsterStat.hp = 0;
        }
        cout << "몬스터 남은 체력 : " << monsterStat.hp << endl;

        if(monsterStat.hp == 0){
            cout << "몬스터를 처치했습니다!" << endl;
            WaitForNextKey();
            break;
        }

        // 몬스터 반격
        damage = monsterStat.attack - playerStat.defence; // 재사용
        playerStat.hp -= damage;
        if(playerStat.hp < 0){
            playerStat.hp = 0;
        }
        cout << "플레이어 남은 체력 : " << playerStat.hp << endl;

        if(playerStat.hp == 0){
            cout << "당신은 사망했습니다...Game Over..." << endl;
            WaitForNextKey();
            break;
        }
    }
}

void WaitForNextKey()
{
    cout << "계속하려면 아무 키를 눌러주세요." << endl;
    cout << "> ";

    int input;
    cin >> input;

    system("clear"); // cmd 정리
}
