#include <assert.h>

class Array
{
    using T = int;

public:
    explicit Array(int capacity = 100) : _capacity(capacity) 
    {
        _buffer = new T[capacity];
    }
    ~Array()
    {
        delete[] _buffer;
    }

    void push_back(const T& data)
    {
        // TODO
        if (_size == _capacity)
            return;
        
        _buffer[_size] = data;
        _size++;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < _size); // assert 조건 만족 못하면 crash
        return _buffer[index];
    }

    int size() { return _size; }
    int capacity() { return _capacity; }

private:
    T*      _buffer = nullptr;
    int     _size = 0; // 앞으로 채울 데이터
    int     _capacity = 0; // 용량 - 전체 할당한 크기
};

int main()
{
    Array arr(100);

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);

    arr[1] = 2;
}