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
		if (isFull()) cout << "error: 큐가 포화상태입니다" << endl;
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	int dequeue() {
		if (isEmpty()) cout << "error: 큐가 공백상태입니다" << endl;
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
		else cout << "ERROR : 그래프 정점 개수 초과" << endl;
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
	char id; // 정점의 id
	Node* link; // 다음 노드의 포인터
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
	int size; // 정점의 개수
	char vertices[MAX_VTXS]; // 정점 정보
	Node* adj[MAX_VTXS]; // 각 정점의 인접 리스트
public:
	AdjListGraph() : size(0) { }
	~AdjListGraph() { reset(); }
	void reset(void) {
		for (int i = 0; i < size; i++)
			if (adj[i] != NULL) delete adj[i];
		size = 0;
	}
	void insertVertex(char val) { // 정점 삽입 연산
		if (!isFull()) {
			vertices[size] = val;
			adj[size++] = NULL;
		}
		else cout << "ERROR : 그래프 정점 개수 초과" << endl;
	}

	void insertEdge(int u, int v) { // 간선 삽입 연산
		adj[u] = new Node(v, adj[u]); // 인접 리스트에 추가
		adj[v] = new Node(u, adj[v]); // 방향 그래프 ==> 주석 처리함
	}
	void display() {
		cout << "Number of vertex : " << size << endl;
		for (int i = 0; i < size; i++) { // 각 행의 정보 출력
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
// 탐색 기능이 추가된 인접행렬 기반 그래프 클래스
class SrchAMGraph : public AdjMatGraph
{
protected:
	bool visited[MAX_VTXS]; // 정점의 방문 정보
public:
	void resetVisited() { // 모든 정점을 방문하지 않았다고 초기화
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}
	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	void DFS(int v) {
		visited[v] = true;
		cout << getVertex(v);

		for (int w = 0; w < size; w++)
			if (isLinked(v, w) && visited[w] == false)
				DFS(w); // 연결 + 방문X => 순환호출
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
		visited[v] = true; // 현재 정점을 방문함

		cout << getVertex(v) << " ";
		CircularQueue que;
		que.enqueue(v); // 시작 정점을 큐에 저장
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
class ConnectedComponentGraph : public SrchAMGraph {  // 클래스 상속
	int label[MAX_VTXS]; // CC 색상 (동일 CC에 동일 색상)
public:
	void labelDFS(int v, int color) { // 색상 레이블링
		visited[v] = true; // 노드 v 방문 여부 기록
		label[v] = color; // 노드 v의 색상
		for (int w = 0; w < size; w++) // 모든 노드에 대해서
			if (isLinked(v, w) && visited[w] == false)
				labelDFS(w, color); // 연결되어있고, 방문안한 노드 DFS
	}
	void findConnectedComponent() {
		int count = 0; // 연결성분 개수 초기화
		for (int i = 0; i < size; i++) // 모든 노드에 대해서
			if (visited[i] == false) // 방문안한 노드이면
				labelDFS(i, ++count); // 이 노드에서 DFS시작, CC개수 증가
		cout << "그래프 연결성분 개수 = = " << count << endl;
		for (int i = 0; i < size; i++) // 모든 노드에 대해서
			cout << getVertex(i) << "=" << label[i] << " ";
		cout << endl;
	}
};

int m[100][100]; // 행렬 입력
int label[100][100]; // 레이블링
int countNum[100]; // CC 개수 저장
int n; // 행렬 차원

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
		int count = 0; // CC 개수 초기화
		for (int i = 0; i < n; i++) // label 배열을 0과 1로 표현
			for (int j = 0; j < n; j++)
				if (m[i][j] > h + 1) label[i][j] = 1; // 높이 h보다 큰 부분만 1로
				else label[i][j] = 0;

		if (isAllZero()) break; // 높이 h보다 큰 부분이 없으면(all zero) stop

		for (int i = 0; i < n; i++) { // test : 안전영역 출력
			for (int j = 0; j < n; j++)
				cout << label[i][j];
			cout << endl;
		}

		for (int i = 0; i < n; i++) // Connected Component 알고리즘
			for (int j = 0; j < n; j++) // 맵을 탐색하면서 label 1인 부분은 dfs로
				if (label[i][j] == 1) {
					count++; // 새로운 CC를 찾을 때마다 증가  dfs(i, j, count + 1); // 2부터 labeling
				}
		countNum[h] = count; // 각 높이 h에서의 CC 개수 저장
		cout << "높이: " << h << "  안전영역 갯수: " << count << endl;
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
	//cout << "인접 행렬로 표현한 그래프" << endl;
	//g.display();



	cout << endl << endl;
	AdjListGraph LG; // 새로운 그래프 객체 생성
	for (int i = 0; i < 4; i++)
		LG.insertVertex('A' + i); // 정점 삽입: 'A' 'B', ...


	LG.insertEdge(0, 1); //A,B // 간선 삽입
	LG.insertEdge(0, 3); //A,D
	LG.insertEdge(1, 2); //B,C
	LG.insertEdge(1, 3); //B,D
	LG.insertEdge(2, 3); //C,D
	cout << "연결 리스트로 표현한 그래프" << endl;
	LG.display();



	//cout << endl << endl;
	//SrchAMGraph DG; // DFS 탐색기능이 있는 그래프 객체 생성
	//DG.load("graph.txt"); // 파일 "graph.txt"로부터 g를 설정함
	//cout << "그래프(grap.txt)" << endl;
	//DG.display(); // 인접행렬을 화면에 출력

	//cout << "DFS ==> ";
	//DG.resetVisited(); // 모든 정점을 방문하지 않은 것으로 초기화
	//DG.DFS(0); // 0번째 정점(A)에서 깊이 우선 탐색 시작
	//cout << endl;



	//cout << endl << endl;
	//SrchALGraph BG;
	//BG.load("graph.txt"); // 그래프 데이터 읽기
	//cout << "그래프(grap.txt)" << endl;
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

	//cout << "연결 성분 테스트 그래프 " << endl;
	//cc.display();
	//cc.resetVisited();
	//cc.findConnectedComponent();




	////cout << endl << endl;
	//cin >> n;
	//for (int i = 0; i < n; i++)
	//    for (int j = 0; j < n; j++)
	//        cin >> m[i][j];

	//// 안전영역 구하기
	//safeArea(n);

	//// 출력
	//cout << getMax(countNum, 100) << endl;
	return 0;
}
