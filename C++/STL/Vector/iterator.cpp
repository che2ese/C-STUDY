#include <iostream>
using namespace std;

template<typename T>
class Iterator
{
public:
    Iterator() : _ptr(nullptr) { }
    Iterator(T* ptr) : _ptr(ptr) { }

    // 전위형 ++it
    Iterator& operator++()
    {
        _ptr++;
        return *this;
    }

    // 후위형 it++
    Iterator& operator++(int)
    {
        Iterator temp = *this;
        _ptr++;
        return temp;
    }

    Iterator operator+(const int count)
    {
        Iterator temp = *this;
        temp._ptr += count;
        return temp;
    }

    bool operator==(const Iterator& other)
    {
        return _ptr == other._ptr;
    }
    
    bool operator!=(const Iterator& other)
    {
        return _ptr != other._ptr;
    }

    T& operator*()
    {
        return *_ptr;
    }

public:
    T* _ptr = nullptr;
};
