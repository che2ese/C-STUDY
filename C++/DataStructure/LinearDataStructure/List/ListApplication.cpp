#include <iostream>
using namespace std;

class Node
{
    // typedef int T;
    using T = int;
public:
    Node(int data) : data(data), prev(nullptr), next(nullptr) {}

public:
    T       data;
    Node*   prev;
    Node*   next;
};

/*
    [dummy] [dummy]
[head]          [tail]
        [node]
*/
class List
{
public:
    List() 
    {
        _head = new Node(0);
        _tail = new Node(0);
        _head->next = _tail;
        _tail->prev = _head;
    }
    ~List()
    {
        Node* node = _head;
        while(node != nullptr)
        {
            // node가 커서 역할로 한 칸씩 이동
            Node* deleteNode = node;
            node = node->next; 
            delete deleteNode;
        }
    }

    Node* GetNode(int index)
    {
        Node* node = _head->next;

        if (node == _tail)
            return nullptr;

        for (int i = 0; i < index; i++)
        {
            if (node == _tail->prev)
                return nullptr;

            node = node->next;
        }
        return node;
    }

    void Print()
    {
        Node* node = _head->next;
        while(node != _tail)
        {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    // head에 새로운 노드 생성  
    // dummy 가 없는 버전
    Node* AddAtHeadNoDummy(int data)
    {
        Node* node = new Node(data);
        /*
        [head]          [tail]
                [node]
        */
        if (_head == nullptr)
        {
            _head = node;
            _tail = node;
        }
        /*
                     [head]             [tail]
        [node] <-> [nextNode] <-> [2] <-> [3]
        */
        else
        {
            Node* nextNode = _head;
            node->next = nextNode;
            nextNode->prev = node;
            _head = node;
        }
        return node;
    }
    // dummy 가 있는 버전
    /*
        [dummy]<->[nextNode]<->[2]<->[3]<->[dummy]
        [head]                       [tail]
    */
    Node* AddAtHead(int data)
    {
        Node* node = new Node(data);
        Node* nextNode = _head->next;
        
        node->next = nextNode;
        nextNode->prev = node;

        _head->next = node;
        node->prev = _head;

        return node;
    }

    // dummy 가 있는 버전
    /*
        [dummy]<->[1]<->[2]<->[prevNode]<->[dummy]
        [head]                              [tail]
    */
    Node* AddAtTail(int data)
    {
        Node* node = new Node(data);
        Node* prevNode = _tail->prev;
        
        prevNode->next = node;
        node->prev = prevNode;

        node->next = _tail;
        _tail->prev = node;

        return node;
    }

    /*                    [node]  
        [dummy]<->[prevNode]<->[posNode]<->[3]<->[dummy]
        [head]                             [tail]
    */
    Node* Insert(Node* posNode, int data)
    {
        Node* node = new Node(data);
        Node* prevNode = posNode->prev; // prev를 설정해놓고 그 사이에 값 넣기

        prevNode->next = node;
        node->prev = prevNode;
        node->next = posNode;
        posNode->prev = node;

        return node;
    }
    
    /*                          [node]
        [dummy]<->[1]<->[prevNode]<->[nextNode]<->[dummy]
        [head]                                     [tail]
    */
    Node* Remove(Node* node)
    {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete node;

        return nextNode;
    }

private:
    Node* _head = nullptr;
    Node* _tail = nullptr;
};

int main()
{
    List li;
    li.AddAtTail(1);
    Node* delNode = li.AddAtTail(2);
    Node* insNode = li.AddAtTail(3);

    li.Print();

    li.Remove(delNode);

    li.Print();

    li.Insert(insNode, 5);

    li.Print();
}