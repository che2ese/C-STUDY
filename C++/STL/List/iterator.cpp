#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
    Node(int data) : data(data), prev(nullptr), next(nullptr) { }

public:
    T data;
    Node* prev;
    Node* next;
};

template <typename T>
class Iterator
{
public:
    Iterator() : _node(nullptr) { }
    Iterator(Node<T>* node) : _node(node) { }

    // ++it
    Iterator& operator++()
    {
        _node = _node->next;
        return _node;
    }
    
    // it++
    Iterator operator++(int)
    {
        Iterator temp = *this;
        _node = _node->next;
        return *this;
    }

    T& operator*()
    {
        return _node->data;
    }

    bool operator==(const Iterator& other)
    {
        return _node == other._node;
    }

    bool operator!=(const Iterator& other)
    {
        return _node != other._node;
    }

public:
    Node<T>* _node;
};
