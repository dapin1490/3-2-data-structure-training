#include <iostream>
#include <fstream>
using namespace std;
#define MAX_VTXS 100
#define INF 9999 // INF�̸� ��������

// ����ġ �׷����� ǥ���ϴ� Ŭ����
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
				cout << getEdge(i, j) << "\t";
			cout << endl;
		}
	}
};

// ����ġ �׷����� ǥ���ϴ� Ŭ����
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
			fp >> n; // ������ ��ü ����
			for (int i = 0; i < n; i++) {
				char str[80];
				int val;
				fp >> str; // ������ �̸�
				insertVertex(str[0]); // ���� ����
				for (int j = 0; j < n; j++) {
					fp >> val; // ���� ����
					insertEdge(i, j, val); // ���� ����
				}
			}
		}
		else cout << "File can not be found !" << endl;
		fp.close();
	}
};

// ���� ������ ��� Ŭ����
#define MAX_ELEMENT	200
// ���� ���� Ŭ���� (Union-Find ����)
class VertexSets {
	int parent[MAX_VTXS]; // �θ� ������ id
	int nSets; // ������ ����
public:
	VertexSets(int n) : nSets(n) {
	for (int i = 0; i < nSets; i++)
			parent[i] = -1; // �ʱ⿡ ��� ������ ������ ���տ� ����
	}
	bool isRoot(int i) { return parent[i] < 0; } // -1�̸� root
	int findSet(int v) { // v�� ���� ������ ã�� root ��ȯ
		while (!isRoot(v)) v = parent[v]; // v�� ���� ������ ��Ʈ�� ã��
		return v;
	}
	void unionSets(int s1, int s2) { // ���� s1�� ���� s2�� ��ħ
		parent[s1] = s2; // s1�� parent�� s2�� ����
		nSets--; // 2���� ������ ���ļ� ���� ������ 1 ����
	}
};

class HeapNode {
	int	key; // Key ��: ������ ����ġ
	int	v1; // ���� 1
	int	v2; // ���� 2
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

	// ���� �Լ�
	void insert(int key, int u, int v) {
		if (isFull()) return;
		int i = ++size;
		while (i != 1 && key < getParent(i).getKey()) {
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key, u, v);
	}
	// ���� �Լ�
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
	void Kruskal() { // kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
		MinHeap heap;
		// 1. ������������ (heap sort)
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
				if (hasEdge(i, j))
					heap.insert(getEdge(i, j), i, j); // ��� ���� ����
		VertexSets set(size); // size���� ������ ����
		int edgeAccepted = 0; // ���õ� ������ ��
		while (edgeAccepted < size - 1) { // 4.(n-1)���� edge�� ���Եɶ�����
			HeapNode e = heap.remove(); // 2.���� ���� edge ����
			int uset = set.findSet(e.getV1()); // v1�� ���� ������ ��Ʈ ��ȯ
			int vset = set.findSet(e.getV2()); // v2�� ���� ������ ��Ʈ ��ȯ
			if (uset != vset) { // 3.����Ŭ ������ ������ MST����
				cout << "���� �߰� : " << getVertex(e.getV1()) << " - " << getVertex(e.getV2()) << " (��� : " << e.getKey() << ")" << endl;
				set.unionSets(uset, vset); // �ΰ��� ������ ����.
				edgeAccepted++;
			}
		}
	}
};

// Dijkstra�˰����� �ִ� ��� Ž�� ����� �߰��� �׷���
class WGraphDijkstra : public WGraph {
	int path[MAX_VTXS];
	int dist[MAX_VTXS]; // ���۳��κ����� �ִܰ�� �Ÿ�
	bool found[MAX_VTXS]; // �湮�� ���� ǥ�� ���� S -> ���� ���� �� true
public:
	int chooseVertex() { // ���� ��� ���� �̹湮 ������ ��ȯ
		int min = INF;
		int minpos = -1;
		for (int i = 0; i < size; i++)
			if (dist[i] < min && !found[i]) {
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() { //��� �������� dist[] �� ���
		for (int i = 0; i < size; i++) { cout << dist[i] << " "; }
		cout << endl;
	}
	void PrintPath(int start, int end) {
		cout << "[�ִܰ��: " << getVertex(start) << "<-" << getVertex(end) << "] " << getVertex(end);
		while (path[end] != start) {
			cout << "-" << getVertex(path[end]);
			end = path[end];
		}
		cout << "-" << getVertex(path[end]) << endl;
	}
	// Dijkstra�� �ִ� ��� �˰���: start �������� ������.
	void ShortestPath(int start) {
		for (int i = 0; i < size; i++) { //�ʱ�ȭ: dist[], found[]
			dist[i] = getEdge(start, i); //������� �� ��ȯ(���� ����ġ)
			path[i] = start;
			found[i] = false; //ó���� S������ �������.
		}
		found[start] = true; // S�� ����
		dist[start] = 0; // ���� �Ÿ�
		for (int i = 0; i < size; i++) {
			cout << "Step" << i + 1 << ": ";
			printDistance(); // ��� dist[] �迭�� ���
			int u = chooseVertex(); // S�� ������ ���� ��� ���� ���� ���� ��ȯ
			found[u] = true; // ���� S�� u�� ���Խ�Ŵ
			for (int w = 0; w < size; w++) {
				if (found[w] == false)//S�� ������ �ʴ� ��� w�� dist�� ����
					if (dist[u] + getEdge(u, w) < dist[w]) {
						dist[w] = dist[u] + getEdge(u, w);
						path[w] = u;
					}
			} // u�� ���İ��� ���� �ִ� �Ÿ��̸� dist[] ����
		}
	}
};
class WGraphFloyd : public WGraph
{
	int A[MAX_VTXS][MAX_VTXS]; // �ִܰ�� �Ÿ�
public:
	void ShortestPathFloyd() {
		for (int i = 0; i < size; i++) // �⺻ ���̷� �ʱ�ȭ
			for (int j = 0; j < size; j++) A[i][j] = getEdge(i, j);

		for (int k = 0; k < size; k++) { // ���� k�� ��ġ�� ���
			for (int i = 0; i < size; i++) // ��� (i,j) ��� ����
				for (int j = 0; j < size; j++)
					if (A[i][k] + A[k][j] < A[i][j])
						A[i][j] = A[i][k] + A[k][j];
			printA(); // �� �ܰ迡���� �ִܰ�� �Ÿ� ��� : k��
		}
	}
	void printA() {
		cout << "====================================" << endl;
		for (int i = 0; i < size; i++) { // ��� (i,j) ��� �Ÿ� ���
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
	//cout << "MST ũ�罺Į �˰���" << endl;
	//g.Kruskal();

	// ���ͽ�Ʈ��
	//WGraphDijkstra g;
	//string fn = "graph_sp.txt";
	//g.load(fn);
	//cout << "Dijkstra�� �ִܰ�� Ž���� ���� �׷��� : " << fn << endl << endl;
	//g.display();

	//cout << "Shortest Path By Dijkstra Algorithm" << endl;
	//g.ShortestPath(0);
	//cout << endl;
	//g.PrintPath(0, 3);

	// FLOYD
	WGraphFloyd f;
	string fn = "graph_sp.txt";
	f.load(fn);
	cout << "Dijkstra�� �ִܰ�� Ž���� ���� �׷���: " << fn << endl;
	f.display();

	cout << "Shortest Path By Dijkstra Algorithm" << endl;
	f.ShortestPathFloyd();

	return 0;
}