#include <iostream>
#include <queue>
#include <list> 
#include <vector>

using namespace std;

// 본 코드는 수업 시간 중 다루기 위하 최소한의 형식만 갖추고 있습니다. 
// LMS - 강의자료 - 수업 자료 09 첨부 파일의 코드를 참고하여 노드 클래스를 별도로 구성하는 것을 추천합니다. 
// 또한 상기 자료에 적혀 있는 코드가 아니더라도, 본인이 편하게 이해할 수 있는 코드를 작성해 두는 것이 좋아요.

class CGraph {
private:
	int n_vertices;			// 정점 갯수입니다. 주어진 문제는 간단히 정수로 표현하고 있기 때문에 데이터(키값)을 신경쓰지 않았습니다. 
	bool* visited;			// 각 정점의 방문 여부입니다. 정점 갯수에 따라 달라지니 포인터, 또는 벡터로 만들면 편합니다. 
	vector<int> dist;		// 첫번째 주어진 문제가 하나의 정점(정착장)에서 다른 정점(쓰레기)까지의 거리를 구하는 문제입니다. 거리를 저장할 변수를 두되, 정점 갯수에 때라 달라지니 포인터, 또는 벡터로 만듭니다. 
	vector<list<int>> adj;	// 각 정점이 어떤 정점들과 연결되어 있는지를 저장합니다. 정점 갯수 만큼 adj를 만들어야 하기에 포인터, 또는 벡터로 만듭니다. 그리고 각각의 adj[i]에 연결되는 다른 정점들을 구현한 방법은 list입니다.
public:
	CGraph(int _n_vertices) {					// 생성자로 그래프를 만듭니다. 문제가 간단하니 필요한 건 오직 정점의 갯수입니다. 
		this->n_vertices = _n_vertices;			// this 포인터는 교수가 심심해서 썼습니다. 안 써도 되죠. 
		visited = new bool[_n_vertices];		// bool* 로 만들었으니 정점의 갯수를 이용해 변수의 크기를 정해 줍니다. 
		for (int i = 0; i < _n_vertices; ++i) {	// 그리고 방문하지 않았다고 초기화 합니다. 
			visited[i] = false;
		}
		dist.resize(_n_vertices);				// 거리 vector도 주어진 갯수만큼 만들어 주고, 
		adj.resize(_n_vertices);				// adj vector도 주어진 갯수만큼 만들어 줍니다. 각각의 vector 원소들은 list로 구성되나, 몇개나 연결될지는 모르기 때문에 초기화하지 않습니다. 초기화하지 않아도 되는 건 list가 동적으로(내가 원하는대로 그 때 그 때 크기를 바꿀 수 있는) 작동하는 constainer이기 때문입니다. 쓰기 편하죠?
	}
	~CGraph() {
		delete visited;		// 멤버 변수 visited는 포인터변수이기 때문에 소멸자에서 삭제해 줍니다. vector로 만들었다면 필요없겠죠?
	}
	void setUndirectEdges(int _s, int _d) {		// 방향성이 없는(_s 정점에서 _d 정점으로 갈 수도, _d 정점에서 _s 정점으로 갈 수도 있는 그래프입니다. 
		adj[_s].push_back(_d);					// _s 정점과 _d 정점이 연결돼 있다고(_s 정점에서 _d 정점으로 이동할 수 있다고) 간선(edge)를 만듭니다. 
		adj[_d].push_back(_s);					// 방향성이 없으니 거꾸로도 연결돼 있습니다. 
	}
	void setDirectEdges(int _s, int _d) {		// 방향성이 있는 경우 _s에서 _d로만 갈 수 있습니다. 
		adj[_s].push_back(_d);
	}
	void BFS(int _s) {			// BFS 알고리즘입니다. 하나의 정점 _s에서 시작합니다. 
		visited[_s] = true;		// 시작점이니 _s는 당연히 방문했습니다. 
		queue<int> Q;			// 큐를 만들어 정점을 탐색하기 위한 준비를 합니다. 
		Q.push(_s);				// 우선 시작점 _s를 큐에 넣어줍니다. 
		while (!Q.empty()) {	// 큐에 더이상 정점이 남아있지 않을 때까지 반복합니다. 		
			_s = Q.front();		// 큐에 가장 먼저 들어간 정점의 값을 꺼냅니다. 
			Q.pop();			// 그리고 꺼낸 큐의 정점은 큐에서 삭제합니다. 
			list<int>::iterator iter;		// 큐에서 꺼낸 정점(_s)과 연결되어 있는 정점들(adj[_s])을 차례로 탐색해 갑니다. 연결된 정점은 리스트로 연결되어 있으니 iterator를 이용해 탐색합니다. 
			for (iter = adj[_s].begin(); iter != adj[_s].end(); ++iter) { // iterator를 사용하는 방법입니다. 일반적인 for loop와 큰 차이가 없죠?
				if (!visited[*iter]) {			// 방문하지 않은 정점만 탐색하면 됩니다. iterator를 사용하면 포인터 사용에 주의하세요.
					visited[*iter] = true;		// _s 근처의 *iter 정점 중 방문하지 않은 경우 방문합니다. 
					Q.push(*iter);				// 그리고 방문한 근처 정점 *iter를 큐에 넣습니다. 
					dist[*iter] = dist[_s] + 1;	// _s 정점의 근처에 있는(연결되어 있는 정점들) *iter는 모두 _s로부터 1만큼 떨어져 있습니다.  
				}
			}
		}
	}
	void BFS(vector<int> _docks) {		// 시작점이 여러개인 경우입니다. 문제에서는 2개지만, 여러개가 올 수도 있으니 vector로 가져오겠습니다. 함수는 오버로딩합니다. 기억나죠? 매개변수가 다르면 함수 이름이 같아도 돼요.
		int n_docks = _docks.size();	// 시작점의 갯수를 확인하고,
		queue<int> Q;
		for (int i = 0; i < n_docks; ++i) {	
			visited[_docks[i]] = true;	// 시작점이니 모두 방문한 뒤에,
			Q.push(_docks[i]);			// 동일한 방식으로 큐에 넣어주면 됩니다. 
		}
		int _s = 0;						
		while (!Q.empty()) {			// 아래는 같은 방식으로 알고리즘을 진행하면 됩니다. 
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
		for (int i = 0; i < n_vertices; ++i) {		// 저장한 거리들을 확인해 봅니다. 콘솔창에 간략히 출력할게요.
			cout << i << " : " << dist[i] << endl;
		}
	}
};

int main() {
	CGraph OGraph(10);				// 문제를 가능한 간단하게 만들었기에, 정점의 갯수만 이용해 그래프를 만들 수 있도록 클래스를 만들었습니다. 
	OGraph.setUndirectEdges(0, 1);	// 그리고 주어진 문제에 따라 간선을 연결합니다. 
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
	vector docks = { 0, 3 };		// 2번 문제를 풉니다. 시작점이 될 정착장은 0과 3, 둘입니다. 
	OGraph.BFS(docks);				// 알고리즘을 실행합니다. 
	return 0;
}

// BFS와 DFS 알고리즘은 다른 여러 그래프 알고리즘의 기본이며, 간단하기 때문에 면접 문제로 출제되기도 하고, 여러 변형 문제들이 있습니다.
// 알고리즘과 코드를 이해했다면, 백지 상태에서 구현해 보는 연습을 해 보세요.
// 짧은 코드니 한두번 해보면 금세 익힐 수 있습니다. 
// vector, list, iterator 등 지난 학기에 다루지 않은 C++ 언어의 기능들도 익숙해 지길 바랍니다. 