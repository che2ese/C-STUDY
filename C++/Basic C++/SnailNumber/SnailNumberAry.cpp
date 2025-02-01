#include <iostream>
#include <iomanip> // 자리 수 정리
using namespace std;

const int MAX = 100;
int board[MAX][MAX];
int N;

// 보통 주어짐
void PrintBoard(){
    for (int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            cout << setfill('0') << setw(2) << board[y][x] << " "; // 2자리로 하고 나머지는 0으로 채우기.
        }
        cout << endl;
    }
}

enum Dir{
    RIGHT = 0,
    DOWN = 1,
    LEFT = 2,
    UP = 3,
};

// 갈 수 있는지 판단
bool CanGo(int y, int x){
    if(y < 0 || y >= N)
        return false;
    if(x < 0 || x >= N)
        return false;
    if(board[y][x] != 0)
        return false;
    return true;
}

void SetBoard(){
    int dir = RIGHT; // 현재 방향
    int num = 1; // 현재 번호
    int y = 0; // 현재 위치
    int x = 0;

    int dy[] = { 0, 1, 0, -1 }; // 오른쪽 아래 왼쪽 위 - enum 순서에 맞게
    int dx[] = { 1, 0, -1, 0 };

    while(true){
        board[y][x] = num;
        
        if(num == N * N) // 끝날 때까지 루프
            break;
        
        int nextY = y + dy[dir]; // 다음 값
        int nextX = x + dx[dir];
        
        if(CanGo(nextY, nextX)){
            y = nextY;
            x = nextX;
            num++;
        }
        else{ // 못 간다면 시계방향으로 이동
            dir = (dir + 1) % 4; // enum에 맞게
        }
    }
}

int main(){
    cin >> N;
    
    SetBoard();
    PrintBoard();
}