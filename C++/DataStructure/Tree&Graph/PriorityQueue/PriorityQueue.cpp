#include <iostream>
using namespace std;
#include <vector>
#include <queue>

/*
	우선 순위 큐
		큐(Queue)는 먼저 들어오는 데이터가 먼저 나가는 FIFO(First In First Out) 형식의 자료구조이다.
		우선순위 큐(Priority Queue)는 먼저 들어오는 데이터가 아니라, 우선순위가 높은 데이터가 먼저 나가는 형태의 자료구조이다.
		우선순위 큐는 일반적으로 힙(Heap)을 이용하여 구현한다.
		여러 개의 값 중 최댓값 또는 최솟값을 찾아내는 연산이 빠르다.
		시간 복잡도 측면에서 엄청 효율적임.
*/

template<typename T>
class PriorityQueue 
{
public:
	// O(logN) - 보통 절반 보면 logN, 전체 다 보면 N
	void Insert(const T& data)
	{
		// 우선 힙 구조 마지막에 삽입.
		_heap.push_back(data);
		// 도장 깨기
		int now = static_cast<int>(_heap.size()) - 1;
		// 루트 노드까지
		while (now > 0)
		{
			// 부모 노드 구하는 공식
			int next = (now - 1) / 2;
			if (_heap[now] < _heap[next])
				break;

			// 부모보다 크면 데이터 교환
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	// O(logN)
	void Remove()
	{
		// 힙의 루트에 힙의 마지막 값 대입
		_heap[0] = _heap.back();
		// 힙 구조 마지막 삭제
		_heap.pop_back();
		
		int now = 0;

		while (true)
		{
			// 왼쪽 오른쪽 자손 공식
			int left = 2 * now + 1;
			int right = 2 * now - 1;
			// leaf에 도달한 경우
			if (left >= (int)_heap.size())
				break;

			int next = now;

			// 왼쪽과 자신을 비교
			if (_heap[next] < _heap[left])
				next = left;
			// 둘 중 승자를 오른쪽과 비교 + 오른쪽이 있는지 확인하기!
			if (right < _heap.size() && _heap[next] < _heap[right])
				next = right;
			// 왼쪽 / 오른쪽 둘 다 현재값보다 작으면?
			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}
	
	// O(1)
	T& find()
	{
		return _heap[0]; // 루트 값이 가장 큼.
	}

	// O(1)
	bool empty()
	{
		return _heap.empty();
	}

private:
	vector<T> _heap;
};

/*
	우선 순위 큐
	[][][][][][][][][][][][]
*/
int main() {
	PriorityQueue<int> pq;

	pq.Insert(10);
	pq.Insert(40);
	pq.Insert(30);
	pq.Insert(50);
	pq.Insert(20);

	int value = pq.find();
	pq.Remove();
}
