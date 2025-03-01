#include <iostream>
using namespace std;

class Node
{
public:
    Node(int data) : data(data) {}

public:
    int data;
    Node* prev = nullptr;
    Node* next = nullptr;
};

// 노드의 구조
// 데이터 + 이전 노드를 가리키는 포인터 + 다음 노드를 가리키는 포인터

int main()
{
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);
    Node* n4 = new Node(4);
    Node* n5 = new Node(5);

    // [1]->[2]->[3]->[4]->[5]
    // 단방향은 단점이 많음. 삽입, 삭제가 어려움.
    // 따라서 양방향으로 설정.
    // [1]<->[2]<->[3]<->[4]>->[5]
   // [head]                  [tail]

    n1->next = n2;
    n2->prev = n1;

    n2->next = n3;
    n3->prev = n2;
    
    n3->next = n4;
    n4->prev = n3;

    n4->next = n5;
    n5->prev = n4;

    Node* head = n1;
    Node* tail = n5;
}