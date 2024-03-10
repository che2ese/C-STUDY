#include "Header.h"

#define INTERVAL (1.0 / 60.0)
#define KEY_COOLDOWN 0.2f // 0.3���� ��Ÿ��

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

        // ���� �̵�
        if (left && leftCooldown <= 0.0f) {
            gameEngine->next(dt, 'a');
            leftCooldown = KEY_COOLDOWN;
        }

        // ������ �̵�
        if (right && rightCooldown <= 0.0f) {
            gameEngine->next(dt, 'd');
            rightCooldown = KEY_COOLDOWN;
        }

        // �Ʒ��� �̵�
        if (down) {
            gameEngine->next(dt, 's');
        }

        // ȸ��
        if (rotate && rotateCooldown <= 0.0f) {
            gameEngine->rotate();
            rotateCooldown = KEY_COOLDOWN;
        }

        // �׳� ��� ������
        else {
            gameEngine->next(dt, '0');
        }

        // ��Ÿ�� ����
        leftCooldown -= dt;
        rightCooldown -= dt;
        rotateCooldown -= dt;

        // ȭ�� ���
        gameEngine->makeDisplayData();
        display->draw();

        // ���� ���� �Ǻ�
        if (gameEngine->state == GameEngine::GameState::GAMEOVER) {
            printf("\n\n������ ����Ǿ����ϴ�.");
            printf("\n����� ���� : %d", gameEngine->point);
            break;
        }

        printf("\n\n���� : %d", gameEngine->point);
    }

    return 0;
}
