#include <iostream>
using namespace std;
#include <vector>

int main()
{
    // size (resize) -  실제 데이터 크기
    // capacity (reserve) - 할당된 공간
    // 삽입 / 삭제
    // - 시작   O(N)
    // - 중간   O(N)
    // - 끝    O(1)
    // push_back, front, back
    // 임의 접근 v[i]
    // v.remove(10) ?

    // 추가
    // 삭제
    // 순회
    // 검색
    
    /*
        vector<int> v(5)
        vector<int> v(5, 0)
        vector<int> v{1, 2, 3, 4, 5}

        v.clear()
        v.size() -> 0
        v.capacity() -> 5
    */

   {
        vector<int> v{1, 2, 3, 4, 5};
        int* ptr = &v[0];
        int* ptrEnd = &v[4] + 1;
        while (ptr != ptrEnd)    
        {
             cout << *ptr << endl;
             ptr++; // 다음 데이터 주소로 넘어간다고 ptr + 4 아님
        }
   }

   {
    // iterator
        vector<int> v{1, 2, 3, 4, 5};
        vector<int>::iterator it = v.begin();
        vector<int>::iterator itEnd = v.end();
        while (it != itEnd)    
        {
             cout << *it << endl;
             it++;
        }
        // 보통 for문 사용
        for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
        {
            int data = *it;
            cout << data << endl;
        }

        // 3?
        vector<int>::iterator it;
        for(it = v.begin(); it != v.end(); it++)
        {
            int data = *it;
            if(data == 3)
            {
                // 찾음 
                break;
            }
        }
        // 3이면 지움
        if(it != v.end())
        {
            cout << "찾음" << endl;
            v.erase(it);
        }

        // 순회를 하면서 삭제할 때는 삭제할 때와 아닐 때를 나눠서 해야함.
        for(it = v.begin(); it != v.end();)
        {
            int value = *it;
            if(value % 2 == 0)
                it = v.erase(it); // 현재 지운 위치를 반환함
            else 
                it++;
        }
   }
}       
