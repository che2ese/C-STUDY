#include "Header.h"

int main() {
    int score_I_E = 0;
    int score_S_N = 0;
    int score_T_F = 0;
    int score_J_P = 0;
    
    float percent_I_E = 50;
    float percent_S_N = 50;
    float percent_T_F = 50;
    float percent_J_P = 50;
    
    question("���� ó�� ���� ������� �ڽ��� �Ұ��ϴ� ���� �η��� �ʴ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n���� ��Ʈ������ Ǫ�� ����� ������� ������ ���̴�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n��ȭ�� �����ϱ⺸�� ���屸 ġ�°� �����Ѵ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n���ڸ����� ��� �ͺ��� ������ ���°� ����.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\nģ�� ģ���� ���� ��� �ͺ��� ��ü ������ �� �����Ѵ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);

    question("\nȣ����� ���� �����̴� �������̴�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n���� �����̴� ���̵� ������ �޸� �ϰ� �Ѵ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n���� ���������� ������ �ϴ� ���̴�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n�̷��� ���� ��� ��������� ������ �� �߿��ϴ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n���迡 �ǰ��� �������ٴ� �������� ������ ���� ������.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);

    question("\n���濡�� ����� ����� �� ���� �ذẸ�ٴ� ������ ���ϴ� ���̴�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n������ ����� ���� ���Ǵ� ���̴�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n�ٸ� ����� ���� ��� �����ϴ��� ����ġ�� �����Ѵ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n�ٸ� ����� ��� ����� ���� ���� ��������.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n� �Ͽ� ���� ����Ѱź��� ������ ���� ��� ������ ����� ���ڴ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);

    question("\n������ �ϰų� ������ �� �� ��ȹ�� ���� �����.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n������ ������ �ִ��� �̷�ٰ� �����ϴ� ���̴�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n��ȹ���� ���ຸ�� �������� ������ �����Ѵ�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n��ȹ�̳� ����� Ʋ������ ��Ʈ������ ���� �ʴ´�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n������ ��Ȳ�� ����� ��ȹ�� �߰��� ������ �ʴ´�.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);

    percentResult(percent_I_E, percent_S_N, percent_T_F, percent_J_P);
    printResult(score_I_E, score_S_N, score_T_F, score_J_P);

    return 0;
}

void percentResult(float i_e, float s_n, float t_f, float j_p) {
    if (i_e < 50) {
        printf("\n����� I�� %.1f%%�Դϴ�.\n", 100 - i_e);
    }
    else {
        printf("\n����� E�� %.1f%%�Դϴ�.\n", i_e);
    }
    if (i_e < 50) {
        printf("\n����� T�� %.1f%%�Դϴ�.\n", 100 - s_n);
    }
    else {
        printf("\n����� F�� %.1f%%�Դϴ�.\n", s_n);
    }
    if (i_e < 50) {
        printf("\n����� S�� %.1f%%�Դϴ�.\n", 100 - t_f);
    }
    else {
        printf("\n����� N�� %.1f%%�Դϴ�.\n", t_f);
    }
    if (i_e < 50) {
        printf("\n����� J�� %.1f%%�Դϴ�.\n", 100 - j_p);
    }
    else {
        printf("\n����� P�� %.1f%%�Դϴ�.\n", j_p);
    }
}

//���
void printResult(int i_e, int s_n, int t_f, int j_p) {
    char mbti[5]; //�������� null����
    if (i_e < 0) {
        mbti[0] = 'I';
    }
    else {
        mbti[0] = 'E';
    }

    if (s_n< 0) {
        mbti[1] = 'S';
    }
    else {
        mbti[1] = 'N';
    }

    if (t_f < 0) {
        mbti[2] = 'T';
    }
    else {
        mbti[2] = 'F';
    }
    if (j_p < 0) {
        mbti[3] = 'J';
    }
    else {
        mbti[3] = 'P';
    }

    mbti[4] = '\0';

    printf("\n����� mbti ����� %s�Դϴ�.\n", mbti);

    if (strcmp(mbti, "ISTJ") == 0) {
        printf("\n����� ���������� �����Դϴ�.\n��ǿ� ���Ͽ� ��Ȯ�ϰ� ü�������� ����ϸ� �����ϰ� å�Ӱ��� �ֽ��ϴ�.\n\n���� �ι� : ���� ������\n");
    }
    else if (strcmp(mbti, "ISFJ") == 0) {
        printf("\n����� ��ȣ�� �����Դϴ�.\n����� �����ϰ� �����ϸ� ģ���մϴ�. ���� ������������ ����Դϴ�.\n\n���� �ι� : �ҳ�ô� �¿�\n");
    }
    else if (strcmp(mbti, "INFJ") == 0) {
        printf("\n����� ��ȣ�� �����Դϴ�.\n����� �γ����� ���� ������� �����մϴ�. ��ġ�� ������ ������ �ֽ��ϴ�.\n\n���� �ι� : J.K.�Ѹ�(�ظ����� �۰�)\n");
    }
    else if (strcmp(mbti, "INTJ") == 0) {
        printf("\n����� ������ �����Դϴ�.\n����� �����̰� ȿ������ �߽��ϴ� ��ö�� ����Դϴ�.\n\n���� �ι� : ��ũ ��Ŀ����\n");
    }
    else if (strcmp(mbti, "ISTP") == 0) {
        printf("\n����� ���� �����Դϴ�.\n����� �����ϰ� �����ϰ� �����ְ� �ִ� ������ ��Ÿ���Դϴ�.\n\n���� �ι� : �ڸ��\n");
    }
    else if (strcmp(mbti, "ISFP") == 0) {
        printf("\n����� ���谡 �����Դϴ�.\n����� �����ϰ� ���濡 ���� ������� �����ϴ�. ���� ����鿡�� ���� �۾����� �����Դϴ�.\n\n���� �ι� : BTS ����\n");
    }
    else if (strcmp(mbti, "INFP") == 0) {
        printf("\n����� ������ �����Դϴ�.\n����� �������̰� �Ϻ��� �߱��ϸ� �����ǾƸ� �߱��ϴ� �����Դϴ�.\n\n���� �ι� : ���ͽ��Ǿ�\n");
    }
    else if (strcmp(mbti, "INTP") == 0) {
        printf("\n����� ������ �����Դϴ�.\n����� �����ϰ� �����ϸ� ����� ���� ������Դϴ�. ��ȸ���� �����ϴٴ� ���� ���� ����ϴ�.\n\n���� �ι� : ���ν�Ÿ��\n");
    }
    else if (strcmp(mbti, "ESTP") == 0) {
        printf("\n����� ����� �����Դϴ�.\n����� �������� ��ȣ�ۿ��� ���� Ȱ���ϴ� ���� �����մϴ�.\n\n���� �ι� : ����ũ ����\n");
    }
    else if (strcmp(mbti, "ESFP") == 0) {
        printf("\n����� ������ �����Դϴ�.\n����� �����ο� ��ȥ�� ���� �ֽ��ϴ�. ��ġ�� �������� �ֺ� ����� ��̰� �մϴ�.\n\n���� �ι� : ��\n");
    }
    else if (strcmp(mbti, "ENFP") == 0) {
        printf("\n����� Ȱ���� �����Դϴ�.\n����� ��ġ�� ������ �������� �׻� ���ο� ���ɼ��� ã���ϴ�. �ΰ����谡 �н��ϴ�.\n\n���� �ι� : �ι�Ʈ �ٿ�� �ִϾ�\n");
    }
    else if (strcmp(mbti, "ENTP") == 0) {
        printf("\n����� ���а� �����Դϴ�.\n����� ������ ���� ����� ������ ���� �����մϴ�.\n\n���� �ι� : ��Ƽ�� �⽺\n");
    }
    else if (strcmp(mbti, "ESTJ") == 0) {
        printf("\n����� �濵�� �����Դϴ�.\n����� �������̰� ��ü���̸� ������ �̲������ �������Դϴ�.\n\n���� �ι� : �豸��\n");
    }
    else if (strcmp(mbti, "ESFJ") == 0) {
        printf("\n����� ������ �����Դϴ�.\n����� ����ɰ� �������� ��Ĩ�ϴ�. �ٸ� ������� ������ �ִ� ���� �����ϸ� ����ְ� �����մϴ�.\n\n���� �ι� : �ں���\n");
    }
    else if (strcmp(mbti, "ENFJ") == 0) {
        printf("\n����� ������ �����Դϴ�.\n����� �����ϰ� �������̸� �米���� ǳ���ϰ� ��Ÿ���Դϴ�. û���� ������ ī�������� �ֽ��ϴ�.\n\n���� �ι� : �ż���\n");
    }
    else if (strcmp(mbti, "ENTJ") == 0) {
        printf("\n����� ����� �����Դϴ�.\n����� �������̸� �����ϰ� �����°� ��ַ��� �ֽ��ϴ�. Ȱ�����̰� ������� ��ȹ�� �����մϴ�.\n\n���� �ι� : ��� ����\n");
    }
}

void question(const char* question, int vn, int n, int y, int vy, float vnp, float np, float yp, float vyp, int* target1, float* target2) {
    for (;;) { //���� �ɾ ���� �ɸ��°� ����
        printf("%s\n(1: �ſ� �ƴϴ�, 2: �ƴϴ�, 3: �׷���, 4: �ſ� �׷���)\n", question);
        printf("�亯�� �Է����ּ���:");
        int input = getInt();
        if (input == 1) {
            *target1 += vn;
            *target2 += vnp;
            break;
        }
        else if (input == 2) {
            *target1 += n;
            *target2 += np;
            break;
        }
        else if (input == 3) {
            *target1 += y;
            *target2 += yp;
            break;
        }
        else if (input == 4) {
            *target1 += vy;
            *target2 += vyp;
            break;
        }
        else {
            printf("�߸��Է��߽��ϴ�. �ٽ� �Է����ּ���\n");
            continue;
        }
    }
}


int getInt() {
    int input;
    fseek(stdin, 0, SEEK_END);
    scanf_s("%d", &input);
    return input;
}