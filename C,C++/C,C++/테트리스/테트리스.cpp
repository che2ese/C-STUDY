#include "Header.h"

#define INTERVAL (1.0 / 60.0)
#define KEY_COOLDOWN 0.2f // 0.3초의 쿨타임

float prev = (float)clock() / CLOCKS_PER_SEC;
float leftCooldown = 0.0f;
float rightCooldown = 0.0f;
float rotateCooldown = 0.0f;

int main() {
    Display* display = new Display();
    GameEngine* gameEngine = new GameEngine();
    gameEngine->init();
    showConsoleCursor(false);

    while (true) {
        float curr = (float)clock() / CLOCKS_PER_SEC;
        float dt = curr - prev;
        prev = curr;

        bool left = keyState('a');
        bool right = keyState('d');
        bool down = keyState('s');
        bool rotate = keyState('w');

        // 왼쪽 이동
        if (left && leftCooldown <= 0.0f) {
            gameEngine->next(dt, 'a');
            leftCooldown = KEY_COOLDOWN;
        }

        // 오른쪽 이동
        if (right && rightCooldown <= 0.0f) {
            gameEngine->next(dt, 'd');
            rightCooldown = KEY_COOLDOWN;
        }

        // 아래로 이동
        if (down) {
            gameEngine->next(dt, 's');
        }

        // 회전
        if (rotate && rotateCooldown <= 0.0f) {
            gameEngine->rotate();
            rotateCooldown = KEY_COOLDOWN;
        }

        // 그냥 블록 떨어짐
        else {
            gameEngine->next(dt, '0');
        }

        // 쿨타임 감소
        leftCooldown -= dt;
        rightCooldown -= dt;
        rotateCooldown -= dt;

        // 화면 출력
        gameEngine->makeDisplayData();
        display->draw();

        // 게임 상태 판별
        if (gameEngine->state == GameEngine::GameState::GAMEOVER) {
            printf("\n\n게임이 종료되었습니다.");
            printf("\n당신의 점수 : %d", gameEngine->point);
            break;
        }

        printf("\n\n점수 : %d", gameEngine->point);
    }

    return 0;
}
