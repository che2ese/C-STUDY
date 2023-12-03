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
    
    question("나는 처음 보는 사람에게 자신을 소개하는 것이 두렵지 않다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n내가 스트레스를 푸는 방법은 사람들을 만나는 것이다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n대화를 시작하기보다 맞장구 치는걸 좋아한다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n술자리에서 노는 것보다 집에서 쉬는게 좋다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);
    question("\n친한 친구랑 둘이 노는 것보다 단체 모임을 더 좋아한다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_I_E, &percent_I_E);

    question("\n호기심은 나를 움직이는 원동력이다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n가끔 번뜩이는 아이디어가 생각나 메모를 하곤 한다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n가끔 비현실적인 망상을 하는 편이다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n미래에 내가 어떻게 사는지보다 현생이 더 중요하다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);
    question("\n경험에 의거한 결정보다는 도전적인 결정을 많이 내린다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_S_N, &percent_S_N);

    question("\n상대방에게 고민을 얘기할 때 문제 해결보다는 공감을 원하는 편이다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n상대방의 기분을 많이 살피는 편이다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n다른 사람이 나를 어떻게 생각하는지 지나치게 생각한다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n다른 사람이 우는 모습을 보면 같이 슬퍼진다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);
    question("\n어떤 일에 대해 노력한거보다 성과가 좋네 라고 들으면 기분이 나쁘다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_T_F, &percent_T_F);

    question("\n업무를 하거나 과제를 할 때 계획을 먼저 세운다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n과제나 업무는 최대한 미뤘다가 시작하는 편이다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n계획적인 여행보다 즉흥적인 여행을 좋아한다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n계획이나 약속이 틀어져도 스트레스를 받지 않는다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);
    question("\n만약의 상황에 대비한 계획을 추가로 세우지 않는다.", -3, -1, 1, 3, -10.0, -5.0, 5.0, 10.0, &score_J_P, &percent_J_P);

    percentResult(percent_I_E, percent_S_N, percent_T_F, percent_J_P);
    printResult(score_I_E, score_S_N, score_T_F, score_J_P);

    return 0;
}

void percentResult(float i_e, float s_n, float t_f, float j_p) {
    if (i_e < 50) {
        printf("\n당신의 I는 %.1f%%입니다.\n", 100 - i_e);
    }
    else {
        printf("\n당신의 E는 %.1f%%입니다.\n", i_e);
    }
    if (i_e < 50) {
        printf("\n당신의 T는 %.1f%%입니다.\n", 100 - s_n);
    }
    else {
        printf("\n당신의 F는 %.1f%%입니다.\n", s_n);
    }
    if (i_e < 50) {
        printf("\n당신의 S는 %.1f%%입니다.\n", 100 - t_f);
    }
    else {
        printf("\n당신의 N은 %.1f%%입니다.\n", t_f);
    }
    if (i_e < 50) {
        printf("\n당신의 J는 %.1f%%입니다.\n", 100 - j_p);
    }
    else {
        printf("\n당신의 P는 %.1f%%입니다.\n", j_p);
    }
}

//결과
void printResult(int i_e, int s_n, int t_f, int j_p) {
    char mbti[5]; //마지막은 null문자
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

    printf("\n당신의 mbti 결과는 %s입니다.\n", mbti);

    if (strcmp(mbti, "ISTJ") == 0) {
        printf("\n당신은 현실주의자 유형입니다.\n사실에 대하여 정확하고 체계적으로 기억하며 신중하고 책임감이 있습니다.\n\n관련 인물 : 조지 워싱턴\n");
    }
    else if (strcmp(mbti, "ISFJ") == 0) {
        printf("\n당신은 수호자 유형입니다.\n당신은 조용하고 차분하며 친근합니다. 가장 믿음직스러운 사람입니다.\n\n관련 인물 : 소녀시대 태연\n");
    }
    else if (strcmp(mbti, "INFJ") == 0) {
        printf("\n당신은 옹호자 유형입니다.\n당신은 인내심이 많고 사람들을 좋아합니다. 눈치가 빠르고 영감이 있습니다.\n\n관련 인물 : J.K.롤링(해리포터 작가)\n");
    }
    else if (strcmp(mbti, "INTJ") == 0) {
        printf("\n당신은 전략가 유형입니다.\n당신은 논리적이고 효율성을 중시하는 냉철한 사람입니다.\n\n관련 인물 : 마크 저커버그\n");
    }
    else if (strcmp(mbti, "ISTP") == 0) {
        printf("\n당신은 장인 유형입니다.\n당신은 조용하고 과묵하고 손재주가 있는 공학자 스타일입니다.\n\n관련 인물 : 박명수\n");
    }
    else if (strcmp(mbti, "ISFP") == 0) {
        printf("\n당신은 모험가 유형입니다.\n당신은 다정하고 상대방에 대한 배려심이 많습니다. 주위 사람들에게 많이 휩쓸리는 성격입니다.\n\n관련 인물 : BTS 정국\n");
    }
    else if (strcmp(mbti, "INFP") == 0) {
        printf("\n당신은 중재자 유형입니다.\n당신은 정열적이고 완벽을 추구하며 유토피아를 추구하는 성격입니다.\n\n관련 인물 : 셰익스피어\n");
    }
    else if (strcmp(mbti, "INTP") == 0) {
        printf("\n당신은 논리술사 유형입니다.\n당신은 조용하고 과묵하며 상상을 즐기는 사색가입니다. 사회성이 부족하다는 말을 많이 듣습니다.\n\n관련 인물 : 아인슈타인\n");
    }
    else if (strcmp(mbti, "ESTP") == 0) {
        printf("\n당신은 사업가 유형입니다.\n당신은 사람들과의 상호작용을 즐기고 활동하는 것을 좋아합니다.\n\n관련 인물 : 블랙핑크 지수\n");
    }
    else if (strcmp(mbti, "ESFP") == 0) {
        printf("\n당신은 연예인 유형입니다.\n당신은 자유로운 영혼을 갖고 있습니다. 넘치는 에너지로 주변 사람을 즐겁게 합니다.\n\n관련 인물 : 비\n");
    }
    else if (strcmp(mbti, "ENFP") == 0) {
        printf("\n당신은 활동가 유형입니다.\n당신은 넘치는 상상력을 바탕으로 항상 새로운 가능성을 찾습니다. 인간관계가 넓습니다.\n\n관련 인물 : 로버트 다우니 주니어\n");
    }
    else if (strcmp(mbti, "ENTP") == 0) {
        printf("\n당신은 변론가 유형입니다.\n당신은 논쟁을 즐기며 사람을 만나는 것을 좋아합니다.\n\n관련 인물 : 스티브 잡스\n");
    }
    else if (strcmp(mbti, "ESTJ") == 0) {
        printf("\n당신은 경영자 유형입니다.\n당신은 현실적이고 구체적이며 조직을 이끌어나가는 리더형입니다.\n\n관련 인물 : 김구라\n");
    }
    else if (strcmp(mbti, "ESFJ") == 0) {
        printf("\n당신은 집정관 유형입니다.\n당신은 배려심과 동정심이 넘칩니다. 다른 사람에게 관심을 주는 것을 좋아하며 동료애가 끈끈합니다.\n\n관련 인물 : 박보검\n");
    }
    else if (strcmp(mbti, "ENFJ") == 0) {
        printf("\n당신은 선도자 유형입니다.\n당신은 따뜻하고 적극적이며 사교성이 풍부하고 이타적입니다. 청중을 사로잡는 카리스마가 있습니다.\n\n관련 인물 : 신세경\n");
    }
    else if (strcmp(mbti, "ENTJ") == 0) {
        printf("\n당신은 통솔자 유형입니다.\n당신은 열정적이며 솔직하고 지도력과 통솔력이 있습니다. 활동적이고 장기적인 계획을 좋아합니다.\n\n관련 인물 : 고듬 램지\n");
    }
}

void question(const char* question, int vn, int n, int y, int vy, float vnp, float np, float yp, float vyp, int* target1, float* target2) {
    for (;;) { //루프 걸어서 오류 걸리는거 방지
        printf("%s\n(1: 매우 아니다, 2: 아니다, 3: 그렇다, 4: 매우 그렇다)\n", question);
        printf("답변을 입력해주세요:");
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
            printf("잘못입력했습니다. 다시 입력해주세요\n");
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