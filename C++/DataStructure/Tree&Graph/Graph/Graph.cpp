#include <iostream>
using namespace std;
#include <vector>
#include <queue>

/* 그래프
	- 지하철 노선도 -> 서로 드문 드문 연결 - 인접리스트 유용
	- 페이스북 친구 -> 서로 빽빽하게 연결 - 인접행렬 유용
*/

// 비효율적
void CreateGraph_1()
{
	struct Vertex
	{
		vector<Vertex*> edges;
	};

	/*
		v.push_back();
		v.push_back();
		v.push_back();
		v.push_back();
		v.push_back();
		v.push_back();

		v.resize(6) - 실제 사용하는 데이터 사이즈
		vector<Vertex> v1(6) - 위에랑 같은 의미
		vector<int> v2(10, -1) - 10개의 데이터를 -1로 초기화
		vector<int> v2{1, 2, 3, 4, 5, 6} - 6개의 데이터 사이즈를 만들고 각각 1, 2, 3, 4, 5, 6으로 초기화
	*/

	vector<Vertex> v(6);

	v[0].edges.push_back(&v[1]); // 0번은 1, 3번과 연결됨
	v[0].edges.push_back(&v[3]);

	v[1].edges.push_back(&v[0]);
	v[1].edges.push_back(&v[2]);
	v[1].edges.push_back(&v[3]);

	v[3].edges.push_back(&v[4]);

	v[5].edges.push_back(&v[4]);

	// 0번과 3번이 연결되어 있나요?
	bool connected = false;

	int size = v[0].edges.size(); // 0번과 연결돼있는 정점 개수
	for (int i = 0; i < size; i++) 
	{
		Vertex* vertex = v[0].edges[i];
		if (vertex == &v[3])
			connected = true;
	}
}

// 인접 리스트 : 실제 연결된 애들만 넣어줌.

void CreateGraph_2()
{
	struct Vertex
	{
		int data;
	};
	vector<Vertex> v(6);

	// 이중 벡터
	// [v][v][v][v][v][v]
	vector<vector<int>> adjacent;
	adjacent.resize(6);
	adjacent[0] = { 1, 3 };
	adjacent[1] = { 0, 2, 3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	bool connected = false;

	int size = adjacent[0].size();
	for (int i = 0; i < size; i++)
	{
		if (adjacent[0][i] == 3)
			connected = true;
	}
}

// 인접 행렬 - 연결된 목록을 행렬로 관리 -> 메모리 소모 심하지만, 빠른 접근
void CreateGraph_3()
{
	struct Vertex
	{
		int data;
	};
	vector<Vertex> v(6);

	/*
		[x][o][x][o][x][x]
		[o][x][o][o][x][x]
		[x][x][x][x][x][x]
		[x][x][x][x][x][x]
		[x][x][x][x][o][x]
		[x][x][x][x][x][x]
		[x][x][x][x][o][x]
	*/

	vector<vector<bool>> adjacent(6, vector<bool>(6, false));
	adjacent[0][1] = true;
	adjacent[0][3] = true;
	adjacent[1][0] = true;
	adjacent[1][2] = true;
	adjacent[1][3] = true;
	adjacent[3][4] = true;
	adjacent[5][4] = true;

	bool connected = adjacent[0][3];

	// 간선 -> -1은 끊긴 간선, 나머지는 가중치
	vector<vector<int>> adjacent1 =
	{
		{ -1, 15, -1, 35, -1, -1 },
		{ 15, -1, 5, 10, -1, -1 },
		{ -1, 5, -1, -1, -1, -1 },
		{ 35, 10, -1, -1, 5, -1 },
		{ -1, -1, -1, 5, -1, 5 },
		{ -1, -1, -1, -1, 5, -1 },
	};
}