#pragma once
#include <assert.h>

// 템플릿 클래스 Vector 정의
// 다양한 데이터 타입에 대해 동작하는 동적 배열 구현
template<typename T>
class Vector
{
public:
    // 기본 생성자
    // 빈 벡터를 초기화
    explicit Vector()
    {
    }

    // 소멸자
    // 동적으로 할당된 메모리를 해제
    ~Vector()
    {
        if (_buffer) // _buffer가 nullptr이 아니라면 메모리 해제
            delete[] _buffer;
    }

    // 벡터의 내용을 모두 지우고 초기 상태로 되돌림
    void clear()
    {
        if (_buffer) // 기존의 버퍼가 있다면 해제하고 새로 할당
        {
            delete[] _buffer;
            _buffer = new T[_capacity]; // 기존 용량 유지하며 빈 배열 생성
        }
        _size = 0; // 크기를 0으로 초기화
    }

    // 데이터를 벡터의 끝에 추가
    void push_back(const T& data)
    {
        // 만약 현재 크기가 용량과 같다면, 용량을 증가시킴
        if (_size == _capacity)
        {
            // 용량을 1.5배로 증가
            int newCapacity = static_cast<int>(_capacity * 1.5);
            if (newCapacity == _capacity) // 만약 용량이 증가하지 않았다면 최소 1 증가
                newCapacity++;

            reserve(newCapacity); // 새로운 용량으로 버퍼 재할당
        }

        // 데이터 추가
        _buffer[_size] = data;

        // 데이터 개수 증가
        _size++;
    }

    // 벡터의 마지막 요소 제거
    void pop_back()
    {
        // 크기를 1 줄이기 (데이터 소멸 작업은 따로 없음)
        _size--;
    }

    // 마지막 요소를 참조
    T& back()
    {
        // 마지막 요소의 참조 반환
        return _buffer[_size - 1];
    }

    // 벡터 크기 조정
    void resize(int size)
    {
        // 용량을 새로운 크기에 맞춤
        reserve(size);
        _size = size; // 크기를 설정 (새 요소들은 초기화되지 않음)
    }

    // 벡터 용량 조정
    void reserve(int capacity)
    {
        if (_capacity >= capacity) // 이미 충분한 용량이 있으면 아무것도 하지 않음
            return;

        _capacity = capacity; // 새로운 용량 설정

        // 새로운 버퍼 할당
        T* newData = new T[_capacity];

        // 기존 데이터 복사
        for (int i = 0; i < _size; i++)
            newData[i] = _buffer[i];

        // 기존 버퍼 해제
        if (_buffer)
            delete[] _buffer;

        _buffer = newData; // 새로운 버퍼 적용
    }

    // 인덱스를 통해 요소 접근 (배열 인덱스처럼 동작)
    T& operator[](int index)
    {
        assert(index >= 0 && index < _size); // 유효성 검사
        return _buffer[index];
    }

    // 현재 벡터의 크기 반환
    int size() { return _size; }

    // 현재 벡터의 용량 반환
    int capacity() { return _capacity; }

private:
    T* _buffer = nullptr; // 데이터 저장을 위한 동적 배열
    int _size = 0;         // 현재 데이터 개수
    int _capacity = 0;     // 현재 버퍼 용량
};
