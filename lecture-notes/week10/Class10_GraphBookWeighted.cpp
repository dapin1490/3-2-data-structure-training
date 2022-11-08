#include <iostream>
#include <fstream>
using namespace std;
#define MAX_VTXS 100
#define INF 9999 // INF이면 간선없음

// 가중치 그래프를 표현하는 클래스
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
				cout << getEdge(i, j) << "\t";
			cout << endl;
		}
	}
};

// 가중치 그래프를 표현하는 클래스
class WGraph : public AdjMatGraph {
public:
	void insertEdge(int u, int v, int weight) {
		if (weight > INF) weight = INF;
		setEdge(u, v, weight);
	}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }
	void load(string filename) {
		ifstream fp(filename);
		if (fp.is_open()) {
			int n, val;
			fp >> n; // 정점의 전체 개수
			for (int i = 0; i < n; i++) {
				char str[80];
				int val;
				fp >> str; // 정점의 이름
				insertVertex(str[0]); // 정점 삽입
				for (int j = 0; j < n; j++) {
					fp >> val; // 간선 정보
					insertEdge(i, j, val); // 간선 삽입
				}
			}
		}
		else cout << "File can not be found !" << endl;
		fp.close();
	}
};

// 힙에 저장할 노드 클래스
#define MAX_ELEMENT	200
// 정점 집합 클래스 (Union-Find 연산)
class VertexSets {
	int parent[MAX_VTXS]; // 부모 정점의 id
	int nSets; // 집합의 개수
public:
	VertexSets(int n) : nSets(n) {
	for (int i = 0; i < nSets; i++)
			parent[i] = -1; // 초기에 모든 정점이 고유의 집합에 속함
	}
	bool isRoot(int i) { return parent[i] < 0; } // -1이면 root
	int findSet(int v) { // v가 속한 집합을 찾아 root 반환
		while (!isRoot(v)) v = parent[v]; // v가 속한 집합의 루트를 찾음
		return v;
	}
	void unionSets(int s1, int s2) { // 집합 s1을 집합 s2와 합침
		parent[s1] = s2; // s1의 parent를 s2로 설정
		nSets--; // 2개의 집합을 합쳐서 집합 개수는 1 감소
	}
};

class HeapNode {
	int	key; // Key 값: 간선의 가중치
	int	v1; // 정점 1
	int	v2; // 정점 2
public:
	HeapNode(int k = 0, int u = 0, int v = 0) : key(k), v1(u), v2(v) { }
	void setKey(int k) { key = k; }
	void setKey(int k, int u, int v) {
		key = k;   v1 = u;  v2 = v;
	}
	int getKey() { return key; }
	int getV1() { return v1; }
	int getV2() { return v2; }
	void display() {
		cout << "\t" << "(" << v1 << "-" << v2 << ") -- " << key << endl;
	}
};
class MinHeap{
	HeapNode node[MAX_ELEMENT];
	int size;
public:
	MinHeap() : size(0) { }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }

	// 삽입 함수
	void insert(int key, int u, int v) {
		if (isFull()) return;
		int i = ++size;
		while (i != 1 && key < getParent(i).getKey()) {
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key, u, v);
	}
	// 삭제 함수
	HeapNode remove() {
		if (isEmpty()) return NULL;

		HeapNode root = node[1];
		HeapNode last = node[size--];

		int parent = 1;
		int	child = 2;

		while (child <= size) {
			if (child < size
				&& getLeft(parent).getKey() > getRight(parent).getKey())
				child++;

			if (last.getKey() <= node[child].getKey()) break;

			node[parent] = node[child];
			parent = child;
			child *= 2;
		}
		node[parent] = last;
		return root;
	}
};
class WGraphMST : public WGraph {
public:
	void Kruskal() { // kruskal의 최소 비용 신장 트리 프로그램
		MinHeap heap;
		// 1. 오름차순정렬 (heap sort)
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
				if (hasEdge(i, j))
					heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
		VertexSets set(size); // size개의 집합을 만듦
		int edgeAccepted = 0; // 선택된 간선의 수
		while (edgeAccepted < size - 1) { // 4.(n-1)개의 edge가 삽입될때까지
			HeapNode e = heap.remove(); // 2.가장 작은 edge 선택
			int uset = set.findSet(e.getV1()); // v1이 속한 집합의 루트 반환
			int vset = set.findSet(e.getV2()); // v2가 속한 집합의 루트 반환
			if (uset != vset) { // 3.사이클 생기지 않으면 MST삽입
				cout << "간선 추가 : " << getVertex(e.getV1()) << " - " << getVertex(e.getV2()) << " (비용 : " << e.getKey() << ")" << endl;
				set.unionSets(uset, vset); // 두개의 집합을 합함.
				edgeAccepted++;
			}
		}
	}
};

// Dijkstra알고리즘의 최단 경로 탐색 기능이 추가된 그래프
class WGraphDijkstra : public WGraph {
	int path[MAX_VTXS];
	int dist[MAX_VTXS]; // 시작노드로부터의 최단경로 거리
	bool found[MAX_VTXS]; // 방문한 정점 표시 집합 S -> 집합 포함 시 true
public:
	int chooseVertex() { // 가장 비용 적은 미방문 정점을 반환
		int min = INF;
		int minpos = -1;
		for (int i = 0; i < size; i++)
			if (dist[i] < min && !found[i]) {
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() { //모든 정점들의 dist[] 값 출력
		for (int i = 0; i < size; i++) { cout << dist[i] << " "; }
		cout << endl;
	}
	void PrintPath(int start, int end) {
		cout << "[최단경로: " << getVertex(start) << "<-" << getVertex(end) << "] " << getVertex(end);
		while (path[end] != start) {
			cout << "-" << getVertex(path[end]);
			end = path[end];
		}
		cout << "-" << getVertex(path[end]) << endl;
	}
	// Dijkstra의 최단 경로 알고리즘: start 정점에서 시작함.
	void ShortestPath(int start) {
		for (int i = 0; i < size; i++) { //초기화: dist[], found[]
			dist[i] = getEdge(start, i); //인접행렬 값 반환(간선 가중치)
			path[i] = start;
			found[i] = false; //처음에 S집합은 비어있음.
		}
		found[start] = true; // S에 포함
		dist[start] = 0; // 최초 거리
		for (int i = 0; i < size; i++) {
			cout << "Step" << i + 1 << ": ";
			printDistance(); // 모든 dist[] 배열값 출력
			int u = chooseVertex(); // S에 속하지 않은 비용 가장 작은 정점 반환
			found[u] = true; // 집합 S에 u를 포함시킴
			for (int w = 0; w < size; w++) {
				if (found[w] == false)//S에 속하지 않는 노드 w의 dist값 갱신
					if (dist[u] + getEdge(u, w) < dist[w]) {
						dist[w] = dist[u] + getEdge(u, w);
						path[w] = u;
					}
			} // u를 거쳐가는 것이 최단 거리이면 dist[] 갱신
		}
	}
};
class WGraphFloyd : public WGraph
{
	int A[MAX_VTXS][MAX_VTXS]; // 최단경로 거리
public:
	void ShortestPathFloyd() {
		for (int i = 0; i < size; i++) // 기본 길이로 초기화
			for (int j = 0; j < size; j++) A[i][j] = getEdge(i, j);

		for (int k = 0; k < size; k++) { // 정점 k를 거치는 경우
			for (int i = 0; i < size; i++) // 모든 (i,j) 경로 수정
				for (int j = 0; j < size; j++)
					if (A[i][k] + A[k][j] < A[i][j])
						A[i][j] = A[i][k] + A[k][j];
			printA(); // 각 단계에서의 최단경로 거리 출력 : k번
		}
	}
	void printA() {
		cout << "====================================" << endl;
		for (int i = 0; i < size; i++) { // 모든 (i,j) 경로 거리 출력
			for (int j = 0; j < size; j++) {
				if (A[i][j] == INF) cout << "  INF  ";
				else cout << A[i][j] << " ";
			}
			cout << endl;
		}
	}
};


int main() {
	//WGraph WG;
	//string fn = "graph_weighted.txt";
	//WG.load(fn);
	//WG.display();

	//WGraphMST g;
	//g.load("graph_weighted.txt");
	//cout << "MST 크루스칼 알고리즘" << endl;
	//g.Kruskal();

	// 다익스트라
	//WGraphDijkstra g;
	//string fn = "graph_sp.txt";
	//g.load(fn);
	//cout << "Dijkstra의 최단경로 탐색을 위한 그래프 : " << fn << endl << endl;
	//g.display();

	//cout << "Shortest Path By Dijkstra Algorithm" << endl;
	//g.ShortestPath(0);
	//cout << endl;
	//g.PrintPath(0, 3);

	// FLOYD
	WGraphFloyd f;
	string fn = "graph_sp.txt";
	f.load(fn);
	cout << "Dijkstra의 최단경로 탐색을 위한 그래프: " << fn << endl;
	f.display();

	cout << "Shortest Path By Dijkstra Algorithm" << endl;
	f.ShortestPathFloyd();

	return 0;
}