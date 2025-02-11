#include <iostream>
using namespace std;

// 싱글톤
// 정말 딱 1개만 존재하고 어디서든 사용할 수 있는 [매니저] 클래스
class UserManager{
public:
    static UserManager* GetInstance(){
        static UserManager um;
        return &um;
    }
public:
    void AddUser() { _userCount++; }
    int GetUserCount() { return _userCount; }
    
private:
    int _userCount = 0;
};

int main(){
    for(int i = 0; i < 10; i++)
        UserManager::GetInstance()->AddUser();
    cout << UserManager::GetInstance()->GetUserCount() << endl;
}