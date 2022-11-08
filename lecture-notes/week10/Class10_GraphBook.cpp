#include <iostream>
#include <fstream>
using namespace std;
#define MAX_QUEUE_SIZE 100
#define MAX_VTXS 100

class CircularQueue {
	int front;
	int rear;
	int data[MAX_QUEUE_SIZE];
public:
	CircularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return(rear + 1) % MAX_QUEUE_SIZE == front; }
	void enqueue(int n) {
		if (isFull()) cout << "error: ť�� ��ȭ�����Դϴ�" << endl;
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	int dequeue() {
		if (isEmpty()) cout << "error: ť�� ��������Դϴ�" << endl;
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};

class AdjMatGraph {
protected:
	int size;
	char vertices[MAX_VTXS];
	int adj[MAX_VTXS][MAX_VTXS];
public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int  getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }

	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; ++i)
			for (int j = 0; j < MAX_VTXS; ++j)
				setEdge(i, j, 0);
	}
	void insertVertex(char name) {
		if (!isFull()) vertices[size++] = name;
		else cout << "ERROR : �׷��� ���� ���� �ʰ�" << endl;
	}
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}
	void display() {
		cout << size << endl;
		for (int i = 0; i < size; ++i) {
			cout << getVertex(i) << " ";
			for (int j = 0; j < size; ++j)
				cout << getEdge(i, j) << " ";
			cout << endl;
		}
	}
};

class Node {
protected:
	char id; // ������ id
	Node* link; // ���� ����� ������
public:
	Node(int i, Node* l = NULL) : id(i), link(l) { }
	~Node() {
		if (link != NULL) delete link;
	}
	int   getID() { return id; }
	Node* getLink() { return link; }
	void  setLink(Node* l) { link = l; }
};

class AdjListGraph {
protected:
	int size; // ������ ����
	char vertices[MAX_VTXS]; // ���� ����
	Node* adj[MAX_VTXS]; // �� ������ ���� ����Ʈ
public:
	AdjListGraph() : size(0) { }
	~AdjListGraph() { reset(); }
	void reset(void) {
		for (int i = 0; i < size; i++)
			if (adj[i] != NULL) delete adj[i];
		size = 0;
	}
	void insertVertex(char val) { // ���� ���� ����
		if (!isFull()) {
			vertices[size] = val;
			adj[size++] = NULL;
		}
		else cout << "ERROR : �׷��� ���� ���� �ʰ�" << endl;
	}

	void insertEdge(int u, int v) { // ���� ���� ����
		adj[u] = new Node(v, adj[u]); // ���� ����Ʈ�� �߰�
		adj[v] = new Node(u, adj[v]); // ���� �׷��� ==> �ּ� ó����
	}
	void display() {
		cout << "Number of vertex : " << size << endl;
		for (int i = 0; i < size; i++) { // �� ���� ���� ���
			cout << getVertex(i) << " ";
			for (Node* v = adj[i]; v != NULL; v = v->getLink())
				cout << getVertex(v->getID()) << " ";
			cout << endl;
		}
	}
	Node* adjacent(int v) { return adj[v]; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }
	char getVertex(int i) { return vertices[i]; }

};
// Ž�� ����� �߰��� ������� ��� �׷��� Ŭ����
class SrchAMGraph : public AdjMatGraph
{
protected:
	bool visited[MAX_VTXS]; // ������ �湮 ����
public:
	void resetVisited() { // ��� ������ �湮���� �ʾҴٰ� �ʱ�ȭ
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}
	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	void DFS(int v) {
		visited[v] = true;
		cout << getVertex(v);

		for (int w = 0; w < size; w++)
			if (isLinked(v, w) && visited[w] == false)
				DFS(w); // ���� + �湮X => ��ȯȣ��
	}

	void load(string filename) {
		ifstream fin(filename);
		int n;
		fin >> n;
		for (int i = 0; i < n; ++i) {
			char str[80];
			fin >> str;
			insertVertex(str[0]);
			for (int j = 0; j < n; ++j) {
				int val;
				fin >> val;
				if (val != 0) insertEdge(i, j);
			}
		}
		fin.close();
	}
};

class SrchALGraph : public AdjListGraph
{
	bool visited[MAX_VTXS];
public:
	void resetVisited() {
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}

	bool isLinked(int u, int v) {
		for (Node* p = adj[u]; p != NULL; p = p->getLink())
			if (p->getID() == v) return true;
		return false;
	}
	void BFS(int v) {
		visited[v] = true; // ���� ������ �湮��

		cout << getVertex(v) << " ";
		CircularQueue que;
		que.enqueue(v); // ���� ������ ť�� ����
		while (!que.isEmpty()) {
			int v = que.dequeue();
			for (Node* w = adj[v]; w != NULL; w = w->getLink())
			{
				int id = w->getID();
				if (!visited[id]) {
					visited[id] = true;
					cout << getVertex(id) << " ";
					que.enqueue(id);
				}
			}
		}
	}
	void load(string filename) {
		ifstream fin(filename);
		int n;
		fin >> n;
		for (int i = 0; i < n; ++i) {
			char str[80];
			fin >> str;
			insertVertex(str[0]);
			for (int j = 0; j < n; ++j) {
				int val;
				fin >> val;
				if (i > j && val != 0) insertEdge(i, j);
			}
		}
		fin.close();
	}
};
class ConnectedComponentGraph : public SrchAMGraph {  // Ŭ���� ���
	int label[MAX_VTXS]; // CC ���� (���� CC�� ���� ����)
public:
	void labelDFS(int v, int color) { // ���� ���̺�
		visited[v] = true; // ��� v �湮 ���� ���
		label[v] = color; // ��� v�� ����
		for (int w = 0; w < size; w++) // ��� ��忡 ���ؼ�
			if (isLinked(v, w) && visited[w] == false)
				labelDFS(w, color); // ����Ǿ��ְ�, �湮���� ��� DFS
	}
	void findConnectedComponent() {
		int count = 0; // ���Ἲ�� ���� �ʱ�ȭ
		for (int i = 0; i < size; i++) // ��� ��忡 ���ؼ�
			if (visited[i] == false) // �湮���� ����̸�
				labelDFS(i, ++count); // �� ��忡�� DFS����, CC���� ����
		cout << "�׷��� ���Ἲ�� ���� = = " << count << endl;
		for (int i = 0; i < size; i++) // ��� ��忡 ���ؼ�
			cout << getVertex(i) << "=" << label[i] << " ";
		cout << endl;
	}
};

int m[100][100]; // ��� �Է�
int label[100][100]; // ���̺�
int countNum[100]; // CC ���� ����
int n; // ��� ����

bool isValid(int a, int b) {
	return (0 <= a && a < n) && (0 <= b && b < n);
}

void dfs(int a, int b, int lb) {
	int x, y;
	label[a][b] = lb;

	for (int i = 0; i < 4; i++) {
		switch (i)
		{
		case 0: x = a - 1; y = b; break;
		case 1: x = a + 1; y = b; break;
		case 2: x = a; y = b - 1; break;
		case 3: x = a; y = b + 1; break;
		}
		if (isValid(x, y) && label[x][y] == 1) dfs(x, y, lb);
	}
}

bool isAllZero() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (label[i][j] != 0) return false;
	return true;
}

int getMax(int a[], int n) {
	int max = -1;
	for (int i = 0; i < n; i++)
		if (max < a[i]) max = a[i];
	return max;
}

void safeArea(int n) {
	for (int h = 0; h < 100; h++) { // height h : 1~100
		int count = 0; // CC ���� �ʱ�ȭ
		for (int i = 0; i < n; i++) // label �迭�� 0�� 1�� ǥ��
			for (int j = 0; j < n; j++)
				if (m[i][j] > h + 1) label[i][j] = 1; // ���� h���� ū �κи� 1��
				else label[i][j] = 0;

		if (isAllZero()) break; // ���� h���� ū �κ��� ������(all zero) stop

		for (int i = 0; i < n; i++) { // test : �������� ���
			for (int j = 0; j < n; j++)
				cout << label[i][j];
			cout << endl;
		}

		for (int i = 0; i < n; i++) // Connected Component �˰���
			for (int j = 0; j < n; j++) // ���� Ž���ϸ鼭 label 1�� �κ��� dfs��
				if (label[i][j] == 1) {
					count++; // ���ο� CC�� ã�� ������ ����  dfs(i, j, count + 1); // 2���� labeling
				}
		countNum[h] = count; // �� ���� h������ CC ���� ����
		cout << "����: " << h << "  �������� ����: " << count << endl;
	}
}


int main()
{
	//AdjMatGraph g;
	//for (int i = 0; i < 4; i++)
	//    g.insertVertex('A' + i);

	//g.insertEdge(0, 1);
	//g.insertEdge(0, 3);
	//g.insertEdge(1, 2);
	//g.insertEdge(1, 3);
	//g.insertEdge(2, 3);
	//cout << "���� ��ķ� ǥ���� �׷���" << endl;
	//g.display();



	cout << endl << endl;
	AdjListGraph LG; // ���ο� �׷��� ��ü ����
	for (int i = 0; i < 4; i++)
		LG.insertVertex('A' + i); // ���� ����: 'A' 'B', ...


	LG.insertEdge(0, 1); //A,B // ���� ����
	LG.insertEdge(0, 3); //A,D
	LG.insertEdge(1, 2); //B,C
	LG.insertEdge(1, 3); //B,D
	LG.insertEdge(2, 3); //C,D
	cout << "���� ����Ʈ�� ǥ���� �׷���" << endl;
	LG.display();



	//cout << endl << endl;
	//SrchAMGraph DG; // DFS Ž������� �ִ� �׷��� ��ü ����
	//DG.load("graph.txt"); // ���� "graph.txt"�κ��� g�� ������
	//cout << "�׷���(grap.txt)" << endl;
	//DG.display(); // ��������� ȭ�鿡 ���

	//cout << "DFS ==> ";
	//DG.resetVisited(); // ��� ������ �湮���� ���� ������ �ʱ�ȭ
	//DG.DFS(0); // 0��° ����(A)���� ���� �켱 Ž�� ����
	//cout << endl;



	//cout << endl << endl;
	//SrchALGraph BG;
	//BG.load("graph.txt"); // �׷��� ������ �б�
	//cout << "�׷���(grap.txt)" << endl;
	//BG.display();

	//cout << "BFS ==> ";
	//BG.resetVisited();
	//BG.BFS(0); // vertex A
	//cout << endl;


	//cout << endl << endl;
	//ConnectedComponentGraph cc;

	//for (int i = 0; i < 5; i++)
	//    cc.insertVertex('A' + i);

	//cc.insertEdge(1, 0);
	//cc.insertEdge(2, 0);
	//cc.insertEdge(3, 4);

	//cout << "���� ���� �׽�Ʈ �׷��� " << endl;
	//cc.display();
	//cc.resetVisited();
	//cc.findConnectedComponent();




	////cout << endl << endl;
	//cin >> n;
	//for (int i = 0; i < n; i++)
	//    for (int j = 0; j < n; j++)
	//        cin >> m[i][j];

	//// �������� ���ϱ�
	//safeArea(n);

	//// ���
	//cout << getMax(countNum, 100) << endl;
	return 0;
}
