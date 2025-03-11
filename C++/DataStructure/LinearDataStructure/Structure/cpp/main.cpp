#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;

/*
	Stack - 후입선출
		- 브라우저의 뒤로가기
		- 실행 취소 (Ctrl + z)
		- 재귀 함수
		- 역순 문자열 (문자열 거꾸로 뒤집기)

	Queue - 선입선출
		- BFS 알고리즘
		- 프로세스 관리 (JS의 콜백 큐)
		- 프린터의 대기열
		- 택배 상하차

	// List로 구현하는건 너무 단순하지만, 효율적인(속도) 측면에서 Vector로 구현해야함. - Stack은 쉽지만 Vector는 어려움 ㅠ
*/

int main()
{
	cout << "-----Stack-----" << endl;
	Stack<int> stack;
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);

	int stack_remove = stack.Top();
	stack.Pop();

	Vector<int>& stack_Container = stack.GetContainer();
	for (int i = 0; i < stack.size(); i++) // 스택 크기만큼 반복
	{
		cout << stack_Container[i] << endl;
	}
	cout << endl;
	cout << "-----Queue-----" << endl;
	Queue<int> queue;
	queue.Enqueue(10);
	queue.Enqueue(20);
	queue.Enqueue(30);

	int queue_Remove = queue.Front();
	queue.Dequeue();
	Vector<int>& queue_Container = queue.GetContainer();
	for (int i = 0; i < queue.size(); i++) // 스택 크기만큼 반복
	{
		cout << queue_Container[i] << endl;
	}
}
