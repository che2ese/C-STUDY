#include <iostream>
using namespace std;
#include <vector>
#include <queue>

// DFS (Depth First Search) - 재귀함수 = stack -> 트리랑 다르게 돌아오는게 가능
struct Vertex
{
	// int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

// 내가 방문한 목록
vector<bool> visited;

void CreateGraph()
{
	vertices.resize(6);

	// 인접 리스트
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = {4};
	adjacent[5] = {4};

	// 인접 행렬
	adjacent = vector<vector<int>>
	{
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 1, 0, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0 },
	};
}

void Dfs(int here) // 시작점
{
	// 방문 도장
	visited[here] = true;
	cout << "Visited : " << here << endl;

	// 인접 리스트
	// 인접한 길 체크
	// dfs(x)의 시간복잡도 : O(N+E)
	const int size = adjacent[here].size();
	for (int i = 0; i < size; i++)
	{
		int there = adjacent[here][i];
		if (visited[there] == false)
			Dfs(there);
	}

	// 인접 행렬 - 4번에서 끊겨서 5번 스캔 못함.
	// 모든 정점을 다 찾아봐야 하기 때문에 dfs(x)의 시간 복잡도 : O(V^2)
	for (int there = 0; there < 6; there++)
	{
		// 길은 있는지
		if (adjacent[here][there] == 0)
			continue;

		// 아직 방문하지 않은 곳 방문
		if (visited[there] == false)
			Dfs(there);
	}
}

// 인접 행렬의 단점 해결
void DfsAll()
{
	visited = vector<bool>(6, false);
	for (int i = 0; i < 6; i++)
	{
		if (visited[i] == false)
			Dfs(i);
	}
}

int main()
{
	CreateGraph();

	visited = vector<bool>(6, false);
	Dfs(0);

	DfsAll();
}