#include <assert.h>
#include <iostream>
using namespace std;

// 동적 배열
class Vector
{
    using T = int;

public:
    explicit Vector()
    {
        // 벡터는 처음에 작게 시작해서 점점 증설함.
    }

    ~Vector()
    {
        if(_buffer)
            delete[] _buffer;
    }

    void clear()
    {
        // capacity는 변하지 않고 size만 바뀜
        if (_buffer)
        {
            delete[] _buffer;
            _buffer = new T[_capacity];
        }

        _size = 0;
    }

    void push_back(const T& data)
    {
        // TODO
        if (_size == _capacity)
        {
            // 증설 작업 - 배열 크기 넓히기
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity)
                newCapacity++;

            reserve(newCapacity);
        }
        
        // 데이터 저장
        _buffer[_size] = data;

        // 데이터 개수 증가
        _size++;
    }

    void pop_back()
    {
        // 소멸
        _size--;
    }

    T& back()
    {
        return _buffer[_size - 1];
    }

    void reserve(int capacity)
    {
        if (_capacity >= capacity)
            return;
        
        _capacity = capacity;

        T* newData = new T[_capacity];

        // 데이터 복사
        for (int i = 0; i < _size; i++)
        {
            newData[i] = _buffer[i];
        }

        if (_buffer)
            delete[] _buffer;

        _buffer = newData;
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
    Vector v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    int a = v[1];

    cout << a << endl;
}