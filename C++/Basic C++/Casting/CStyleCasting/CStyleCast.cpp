#include <iostream>
using namespace std;

/* 
C 스타일 캐스팅
    - 의미를 유지하기 위해서 원본 객체와 다른 비트열 구성
*/

int main()
{
    // 값 타입 변환
    {
        int a = 123456789; // int - 2의 보수법으로 정확한 값 표현.
        float b = (float)a; // float - 부동소수점으로 근사값 표현.

        cout << a << endl;
        cout << b << endl;
    }
    // 참조 타입 변환
    {
        int a = 123456789;
        float b = (float&)a; // 참조 - 데이터값이 변하지 않은 상태로 형 변환이 돼 이상한 값 발생.

        cout << a << endl;
        cout << b << endl;
    }
    // 안전한 변환 (의미가 100% 일치할 경우)
    // ex) int -> _int64 - 작은 바구니에서 큰 바구니
    {
        int a = 123456789;
        int64_t b = (int64_t)a;

        cout << a << endl;
        cout << b << endl;
    }
    // 암시적 변환 - 알아서 변환(생략)
    {
        int a = 123456789;
        float b = a;

        cout << a << endl;
        cout << b << endl;
    }
}