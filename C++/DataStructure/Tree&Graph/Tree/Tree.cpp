#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	Node(const char* data) : data(data){ }
public:
	const char* data;
	vector<Node*> children;
};

Node* CreateTree()
{
	Node* root = new Node("R1 : 개발실");
	{
		Node* node = new Node("디자인");
		root->children.push_back(node);
		{
			Node* leaf = new Node("전투");
			node->children.push_back(leaf);

		}
		{
			Node* leaf = new Node("경제");
			node->children.push_back(leaf);

		}
		{
			Node* leaf = new Node("스토리");
			node->children.push_back(leaf);

		}
	}
	{
		Node* node = new Node("프로그래밍");
		root->children.push_back(node);
		{
			Node* leaf = new Node("클라");
			node->children.push_back(leaf);

		}
		{
			Node* leaf = new Node("서버");
			node->children.push_back(leaf);

		}
		{
			Node* leaf = new Node("엔");
			node->children.push_back(leaf);

		}
	}
	{
		Node* node = new Node("아트");
		root->children.push_back(node);
		{
			Node* leaf = new Node("배경");
			node->children.push_back(leaf);

		}
		{
			Node* leaf = new Node("캐릭터");
			node->children.push_back(leaf);

		}
	}
	return root;
}

// 깊이가 깊어지면 비효율
void PrintTree(Node* root)
{
	cout << root->data << endl;
	int size = root->children.size(); // 벡터의 데이터 사이즈
	for (int i = 0; i < size; i++)
	{
		Node* node = root->children[i];
		cout << node->data << endl;
	}
}

// 재귀 함수 이용
void RecursiveTree(Node* root, int depth = 0)
{
	// 깊이(depth) : 루트에서 어떤 노드에 도달하기 위해 거쳐야 하는 간선의 개수
	for (int i = 0; i < depth; i++)
		cout << "-";

	cout << root->data << endl;

	int size = root->children.size(); // children 이 0개이면 알아서 종료.
	for (int i = 0; i < size; i++)
	{
		Node* node = root->children[i];
		RecursiveTree(node, depth + 1);
	}
}

// 높이(height) 구하기
int GetHeight(Node* root) 
{
	int height = 1;

	int size = root->children.size();
	for (int i = 0; i < size; i++) 
	{
		Node* node = root->children[i];
		int childHeight = GetHeight(node) + 1;

		height = max(height, childHeight);
	}

	return height;
}

int main()
{
	Node* root = CreateTree();
	PrintTree(root);
	cout << endl;
	cout << "재귀 함수 이용" << endl;
	cout << "--------------" << endl;
	RecursiveTree(root);

	cout << endl;
	cout << "트리의 높이 구하기" << endl;
	cout << GetHeight(root) << endl;
}
