#include <iostream>
#include <queue>
#include <list> 
#include <vector>

using namespace std;

// �� �ڵ�� ���� �ð� �� �ٷ�� ���� �ּ����� ���ĸ� ���߰� �ֽ��ϴ�. 
// LMS - �����ڷ� - ���� �ڷ� 09 ÷�� ������ �ڵ带 �����Ͽ� ��� Ŭ������ ������ �����ϴ� ���� ��õ�մϴ�. 
// ���� ��� �ڷῡ ���� �ִ� �ڵ尡 �ƴϴ���, ������ ���ϰ� ������ �� �ִ� �ڵ带 �ۼ��� �δ� ���� ���ƿ�.

class CGraph {
private:
	int n_vertices;			// ���� �����Դϴ�. �־��� ������ ������ ������ ǥ���ϰ� �ֱ� ������ ������(Ű��)�� �Ű澲�� �ʾҽ��ϴ�. 
	bool* visited;			// �� ������ �湮 �����Դϴ�. ���� ������ ���� �޶����� ������, �Ǵ� ���ͷ� ����� ���մϴ�. 
	vector<int> dist;		// ù��° �־��� ������ �ϳ��� ����(������)���� �ٸ� ����(������)������ �Ÿ��� ���ϴ� �����Դϴ�. �Ÿ��� ������ ������ �ε�, ���� ������ ���� �޶����� ������, �Ǵ� ���ͷ� ����ϴ�. 
	vector<list<int>> adj;	// �� ������ � ������� ����Ǿ� �ִ����� �����մϴ�. ���� ���� ��ŭ adj�� ������ �ϱ⿡ ������, �Ǵ� ���ͷ� ����ϴ�. �׸��� ������ adj[i]�� ����Ǵ� �ٸ� �������� ������ ����� list�Դϴ�.
public:
	CGraph(int _n_vertices) {					// �����ڷ� �׷����� ����ϴ�. ������ �����ϴ� �ʿ��� �� ���� ������ �����Դϴ�. 
		this->n_vertices = _n_vertices;			// this �����ʹ� ������ �ɽ��ؼ� ����ϴ�. �� �ᵵ ����. 
		visited = new bool[_n_vertices];		// bool* �� ��������� ������ ������ �̿��� ������ ũ�⸦ ���� �ݴϴ�. 
		for (int i = 0; i < _n_vertices; ++i) {	// �׸��� �湮���� �ʾҴٰ� �ʱ�ȭ �մϴ�. 
			visited[i] = false;
		}
		dist.resize(_n_vertices);				// �Ÿ� vector�� �־��� ������ŭ ����� �ְ�, 
		adj.resize(_n_vertices);				// adj vector�� �־��� ������ŭ ����� �ݴϴ�. ������ vector ���ҵ��� list�� �����ǳ�, ��� ��������� �𸣱� ������ �ʱ�ȭ���� �ʽ��ϴ�. �ʱ�ȭ���� �ʾƵ� �Ǵ� �� list�� ��������(���� ���ϴ´�� �� �� �� �� ũ�⸦ �ٲ� �� �ִ�) �۵��ϴ� constainer�̱� �����Դϴ�. ���� ������?
	}
	~CGraph() {
		delete visited;		// ��� ���� visited�� �����ͺ����̱� ������ �Ҹ��ڿ��� ������ �ݴϴ�. vector�� ������ٸ� �ʿ������?
	}
	void setUndirectEdges(int _s, int _d) {		// ���⼺�� ����(_s �������� _d �������� �� ����, _d �������� _s �������� �� ���� �ִ� �׷����Դϴ�. 
		adj[_s].push_back(_d);					// _s ������ _d ������ ����� �ִٰ�(_s �������� _d �������� �̵��� �� �ִٰ�) ����(edge)�� ����ϴ�. 
		adj[_d].push_back(_s);					// ���⼺�� ������ �Ųٷε� ����� �ֽ��ϴ�. 
	}
	void setDirectEdges(int _s, int _d) {		// ���⼺�� �ִ� ��� _s���� _d�θ� �� �� �ֽ��ϴ�. 
		adj[_s].push_back(_d);
	}
	void BFS(int _s) {			// BFS �˰����Դϴ�. �ϳ��� ���� _s���� �����մϴ�. 
		visited[_s] = true;		// �������̴� _s�� �翬�� �湮�߽��ϴ�. 
		queue<int> Q;			// ť�� ����� ������ Ž���ϱ� ���� �غ� �մϴ�. 
		Q.push(_s);				// �켱 ������ _s�� ť�� �־��ݴϴ�. 
		while (!Q.empty()) {	// ť�� ���̻� ������ �������� ���� ������ �ݺ��մϴ�. 		
			_s = Q.front();		// ť�� ���� ���� �� ������ ���� �����ϴ�. 
			Q.pop();			// �׸��� ���� ť�� ������ ť���� �����մϴ�. 
			list<int>::iterator iter;		// ť���� ���� ����(_s)�� ����Ǿ� �ִ� ������(adj[_s])�� ���ʷ� Ž���� ���ϴ�. ����� ������ ����Ʈ�� ����Ǿ� ������ iterator�� �̿��� Ž���մϴ�. 
			for (iter = adj[_s].begin(); iter != adj[_s].end(); ++iter) { // iterator�� ����ϴ� ����Դϴ�. �Ϲ����� for loop�� ū ���̰� ����?
				if (!visited[*iter]) {			// �湮���� ���� ������ Ž���ϸ� �˴ϴ�. iterator�� ����ϸ� ������ ��뿡 �����ϼ���.
					visited[*iter] = true;		// _s ��ó�� *iter ���� �� �湮���� ���� ��� �湮�մϴ�. 
					Q.push(*iter);				// �׸��� �湮�� ��ó ���� *iter�� ť�� �ֽ��ϴ�. 
					dist[*iter] = dist[_s] + 1;	// _s ������ ��ó�� �ִ�(����Ǿ� �ִ� ������) *iter�� ��� _s�κ��� 1��ŭ ������ �ֽ��ϴ�.  
				}
			}
		}
	}
	void BFS(vector<int> _docks) {		// �������� �������� ����Դϴ�. ���������� 2������, �������� �� ���� ������ vector�� �������ڽ��ϴ�. �Լ��� �����ε��մϴ�. ��ﳪ��? �Ű������� �ٸ��� �Լ� �̸��� ���Ƶ� �ſ�.
		int n_docks = _docks.size();	// �������� ������ Ȯ���ϰ�,
		queue<int> Q;
		for (int i = 0; i < n_docks; ++i) {	
			visited[_docks[i]] = true;	// �������̴� ��� �湮�� �ڿ�,
			Q.push(_docks[i]);			// ������ ������� ť�� �־��ָ� �˴ϴ�. 
		}
		int _s = 0;						
		while (!Q.empty()) {			// �Ʒ��� ���� ������� �˰����� �����ϸ� �˴ϴ�. 
			_s = Q.front();
			Q.pop();
			list<int>::iterator iter;
			for (iter = adj[_s].begin(); iter != adj[_s].end(); ++iter) {
				if (!visited[*iter]) {
					visited[*iter] = true;
					Q.push(*iter);
					dist[*iter] = dist[_s] + 1;
				}
			}
		}
		for (int i = 0; i < n_vertices; ++i) {		// ������ �Ÿ����� Ȯ���� ���ϴ�. �ܼ�â�� ������ ����ҰԿ�.
			cout << i << " : " << dist[i] << endl;
		}
	}
};

int main() {
	CGraph OGraph(10);				// ������ ������ �����ϰ� ������⿡, ������ ������ �̿��� �׷����� ���� �� �ֵ��� Ŭ������ ��������ϴ�. 
	OGraph.setUndirectEdges(0, 1);	// �׸��� �־��� ������ ���� ������ �����մϴ�. 
	OGraph.setUndirectEdges(0, 2);
	OGraph.setUndirectEdges(1, 3);
	OGraph.setUndirectEdges(1, 4);
	OGraph.setUndirectEdges(2, 3);
	OGraph.setUndirectEdges(3, 4);
	OGraph.setUndirectEdges(4, 5);
	OGraph.setUndirectEdges(4, 6);
	OGraph.setUndirectEdges(4, 7);
	OGraph.setUndirectEdges(5, 7);
	OGraph.setUndirectEdges(5, 8);
	OGraph.setUndirectEdges(5, 9);
	OGraph.setUndirectEdges(6, 7);
	OGraph.setUndirectEdges(7, 8);
	vector docks = { 0, 3 };		// 2�� ������ Ǳ�ϴ�. �������� �� �������� 0�� 3, ���Դϴ�. 
	OGraph.BFS(docks);				// �˰����� �����մϴ�. 
	return 0;
}

// BFS�� DFS �˰����� �ٸ� ���� �׷��� �˰����� �⺻�̸�, �����ϱ� ������ ���� ������ �����Ǳ⵵ �ϰ�, ���� ���� �������� �ֽ��ϴ�.
// �˰���� �ڵ带 �����ߴٸ�, ���� ���¿��� ������ ���� ������ �� ������.
// ª�� �ڵ�� �ѵι� �غ��� �ݼ� ���� �� �ֽ��ϴ�. 
// vector, list, iterator �� ���� �б⿡ �ٷ��� ���� C++ ����� ��ɵ鵵 �ͼ��� ���� �ٶ��ϴ�. 