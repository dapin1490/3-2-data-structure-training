#include <iostream>
#include <fstream>
#include <queue>
#include <list> 
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <limits>
using namespace std;

// STL을 사용하지 않을 때의 코드 구성입니다.
// 우선 문제의 크기와 관련한 변수를 결정해 둡니다.
#define MAX_VTXS 100		// 최대 100개의 정점을 다룹니다.
#define INF 9999            // INF이면 간선이 없다고 표현합니다(STL을 사용하면 이렇게 안 해요).

// 가중치 그래프를 표현하는 클래스로 ADJ MATRIX(인접 행렬)을 사용합니다.
// 단, AdjMatGraph는 가중치를 고려하지 않습니다.
class AdjMatGraph {
protected:
	int    size;					// 정점의 갯수입니다.
	char   vertices[MAX_VTXS];		// 정점 정보입니다.
	int    adj[MAX_VTXS][MAX_VTXS];	// 간선을 인접 행렬로 표현합니다. 간선 표현 방식은 인접 행렬과 인접 리스트, 두 방식을 배웠죠?
public:
	AdjMatGraph() { reset(); }		// 가중치 그래프 클래스의 생성자입니다. reset 멤버 함수를 참조하세요.
	char getVertex(int i) { return vertices[i]; }		// 정점 정보를 반환합니다.
	int  getEdge(int i, int j) { return adj[i][j]; }	// 간선 정보를 반환합니다. 
	void setEdge(int i, int j, int val) { adj[i][j] = val; }	// 간선을 만듭니다. i정점과 j정점을 잇는 간선 weight(val)를 인접행렬에 입력합니다.
	bool isEmpty() { return size == 0; }		// 그래프가 정점이 하나도 없는 상태인지 확인합니다.
	bool isFull() { return size >= MAX_VTXS; }	// 그래프가 정점을 더 이상 추가할 수 없는 상태인지 확인합니다.

	void reset() {	// 그래프를 처음으로 돌려놓는 함수입니다.  
		size = 0;	// 정점은 하나도 없고,
		for (int i = 0; i < MAX_VTXS; ++i)
			for (int j = 0; j < MAX_VTXS; ++j)
				setEdge(i, j, 0);	// 연결되어 있는 모든 값도 0으로(연결되어 있지 않다고) 세팅합니다.
	}
	void insertVertex(char name) { // 정점을 그래프에 넣어주는 함수입니다. 
		if (!isFull()) vertices[size++] = name; // 정점을 더 넣을 수 있으면, 정점을 만들고, 그래프 크기도 하나 증가시킵니다(size++).
		else cout << "ERROR : 그래프 정점 개수 초과" << endl; // 정점을 더 넣을 수 없으면 콘솔창에 오류 메세지를 출력합니다.
	}
	void insertEdge(int u, int v) {	// 정점 u와 정점 v를 잇는 간선을 만듭니다. 
		setEdge(u, v, 1);	// 가중치를 고려하지 않기 때문에 가중치는 1입니다. 
		setEdge(v, u, 1);	// 방향성을 고려하지 않기 때문에 반대로도 이어 줍니다.
	}
	void display() {		// 인접 행렬의 모습을 콘솔창에 출력하는 멤버함수입니다. 
		cout << size << endl;	// 먼저 그래프의 크기(정점 갯수)를 출력하고,
		for (int i = 0; i < size; ++i) {		// 정점의 갯수만큼,
			cout << getVertex(i) << " ";		// 정점 정보를 출력합니다.
			for (int j = 0; j < size; ++j)		// 그리고 해당 정점이 어디에 연결되어 있는지를 표현합니다.
				cout << getEdge(i, j) << "\t";
			cout << endl;
		}
	}
};

// 가중치를 고려하지 않는 클래스를 상속받아서 , 가중치를 표현하는 클래스를 만듭니다.
// 배우는 절차 상 가중치를 고려하지 않는 클래스, 그리고 이어서 가중치가 있는 클래스를 배웠습니다.
// 실제 구현은 굳이 나누지 않아도 됩니다.
class WGraph : public AdjMatGraph {	// 위의 가중치를 고려하지 않는 그래프 클래스를 상속받습니다.
public:
	void insertEdge(int u, int v, int weight) {	// 가중치(weight)를 고려하여 간선을 만듭니다.
		if (weight > INF) weight = INF;			// 만약 이상한 가중치(이상하게 큰 값)가 들어오면 잘못된 값으로 판단하고, 연결되지 않았다고 봅니다.
		setEdge(u, v, weight);					// 제대로 된 가중치 값이 있다면, 정점 u와 v를 잇는 간선을 만듭니다. 
	}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }	// 간선이 이미 존재하는지 확인합니다. 초기값이 INF이기 때문에, 인접 행렬의 정점 i, j의 값이 INF가 아니라면 간선이 존재한다고 판단할 수 있습니다.
	void load(string filename) {		// 외부 파일에서 그래프 정보를 불러올 때 사용합니다. 불러오는 과정을 확인하여 문제에 따라 다르게 활용할 수 있어야 합니다.
		ifstream fp(filename);
		if (fp.is_open()) {
			int n, val;
			fp >> n;							// 정점의 전체 개수를 먼저 가져오고,
			for (int i = 0; i < n; i++) {
				char str[80];
				int val;
				fp >> str;						// 현재 문제는 정점 값이 char이기 때문에 char로 정점 정보를 가져옵니다.
				insertVertex(str[0]);			// 주어진 정보에 따라 정점을 삽입합니다. 
				for (int j = 0; j < n; j++) {
					fp >> val;					// 간선 정보를 읽어 와서,
					insertEdge(i, j, val);		// 간선을 만듭니다.          
				}
			}
		}
		else cout << "File can not be found !" << endl;
		fp.close();
	}
};

// 다익스트라 알고리즘의 최단 경로 탐색 기능이 추가된 그래프입니다.
// 다익스트라 알고리즘은 가중치가 있는 경우 사용하죠? 따라서 위에 만들어 둔 가중치 그래프(WGraph)를 상속받고, 다익스트라 알고리즘을 작동시킬 몇 가지 기능만 추가로 구현합니다. 
// 따라서 별도의 상속 클래스로 구현하지 않고, 하나의 클래스로 구현해도 됩니다. 
class WGraphDijkstra : public WGraph {
	int path[MAX_VTXS];		// 경로입니다. 
	int dist[MAX_VTXS];		// 시작노드로부터의 최단경로 거리입니다.
	bool found[MAX_VTXS];	// 방문한 정점 표시 집합 S입니다. 방문하게 되면(집합 S에 포함되면) true로 만들어 줍니다. 
public:
	int chooseVertex() {	// 근처의 정점 중에서 아직 방문하지 않았고, 가장 적은 비용으로 갈 수 있는 정점을 선택하는 함수입니다.
		int min = INF;		// 가장 적은 비용을 찾아야 되니, 임시 변수를 만들어 큰 값을 넣어 줍니다.	
		int minpos = -1;	// 선택한 정점을 반환하기 위한 임시 변수입니다.
		for (int i = 0; i < size; i++)			// 정점을 모두 확인해서,
			if (dist[i] < min && !found[i]) {	// 방문하지 않은 곳 중 최소 비용으로 갈 수 있는 정점을 찾아나갑니다.
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() {		//모든 정점들까지의 최단거리를 콘솔창에 출력하는 함수입니다.
		for (int i = 0; i < size; i++) { cout << dist[i] << " "; }
		cout << endl;
	}
	void PrintPath(int start, int end) {	// 해당 정점까지의 경로를 콘솔창에 출력하는 함수입니다. 
		cout << "[최단경로: " << getVertex(start) << "<-" << getVertex(end) << "] " << getVertex(end);
		while (path[end] != start) {
			cout << "-" << getVertex(path[end]);
			end = path[end];
		}
		cout << "-" << getVertex(path[end]) << endl;
	}
	// 다익스트라 기본 경로 알고리즘입니다. 
	// 정점 s 에서 시작합니다.
	void ShortestPath(int s) { 
		for (int i = 0; i < size; i++) {	// 다익스트라 알고리즘에 필요한 변수들을 초기화하여 알고리즘 작동을 준비합니다.
			dist[i] = getEdge(s, i);		// 정점 s와 모든 정점들 i에 대해 하나 하나 간선의 값을 확인해 가면서, 해당 정점까지의 거리 정보를 저장해 둡니다.
			path[i] = s;					// 각 정점까지의 최단 경로입니다. 해당 정점에 도착하기 위한 최단 경로의 바로 앞 정점을 추가해 줍니다.
			found[i] = false;				// 처음에 S집합은 비어있음.
		}
		found[s] = true;	// 정점 s를 방문하였으므로, s를 방문하였다고(집합 S에 포함) 합니다.
		dist[s] = 0;		// 처음 위치의 거리는 지금 내가 시작한 곳이니 0입니다. 
		for (int i = 0; i < size; i++) {		// 모든 정점에 대해 확인을 해 줍니다. 
			cout << "Step" << i + 1 << ": ";	// 콘솔창에 과정을 출력해 주기 위한 코드 라인입니다.
			printDistance();					// 현재 상태에서 다른 모든 정점까지의 거리를 콘솔창에 출력합니다.
			int u = chooseVertex();				// 근처의 정점 중에서 아직 방문하지 않았고, 가장 적은 비용으로 갈 수 있는 정점을 선택합니다.
			found[u] = true;					// 그리고 선택한 정점을 방문(집합 S에 포함)합니다.
			for (int w = 0; w < size; w++) {	// 다시 모든 정점에 대해 
				if (found[w] == false)			// 방문하지 않은 정점들(집합 S에 속하지 않는 노드 w)의 거리 값을 갱신합니다.
					if (dist[u] + getEdge(u, w) < dist[w]) {	// 갱신 방법은 새로 포함한 u 정점까지의 거리(dist[u])와 새로 개척한 경로 getEdge(u, w)를 더한 값이 새로운 거리가 되고, 기존에 알던 경로는 dist[w]가 됩니다. 새로 개척한 경로가 더 짧으면 업데이트 해 줍니다.
						dist[w] = dist[u] + getEdge(u, w);		// 더 좋은 경로를 찾았으니 업데이트 해 주고, 
						path[w] = u;							//  최단 경로에 추가해 줍니다.
					}
			}       
		}
	}
	
};

int main() {
	
	WGraphDijkstra g;
	string fn = "graph_sp.txt";
	g.load(fn);
	cout << "Dijkstra의 최단경로 탐색을 위한 그래프 : " << fn << endl << endl;
	g.display();
	g.ShortestPath(0);

	return 0;
}

