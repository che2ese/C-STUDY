#include <iostream>
#include <iomanip> // 자리 수 정리
using namespace std;

const int MAX = 100;
int board[MAX][MAX];
int N;

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

    while(true){
        board[y][x] = num;
        
        if(num == N * N) // 끝날 때까지 루프
            break;
        
        int nextY;
        int nextX;
        
        switch (dir)
        {
            case RIGHT:
                nextY = y;
                nextX = x + 1;
                break;
            case DOWN:
                nextY = y + 1;
                nextX = x;
                break;
            case LEFT:
                nextY = y;
                nextX = x - 1;
                break;
            case UP:
                nextY = y - 1;
                nextX = x;
                break;
        }
        if(CanGo(nextY, nextX)){
            y = nextY;
            x = nextX;
            num++;
        }
        else{ // 못 간다면 시계방향으로 이동
            switch (dir)
            {
                case RIGHT:
                    dir = DOWN;
                    break;
                case DOWN:
                    dir = LEFT;
                    break;
                case LEFT:
                    dir = UP;
                    break;
                case UP:
                    dir = RIGHT;
                    break;
            }
        }
    }
}

int main(){
    cin >> N;
    
    SetBoard();
    PrintBoard();
}