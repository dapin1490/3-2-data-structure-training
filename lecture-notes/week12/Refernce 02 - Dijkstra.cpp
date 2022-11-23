// 본 코드 설명은 강의 시간에 진행합니다.

#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <limits>
using namespace std;

template <typename T>
struct Edge {
	unsigned src;
	unsigned dst;
	T weight;
};

template <typename T>
struct Label {
	unsigned ID;
	T distance;
	inline bool operator> (const Label<T>& l) const {
		return this->distance > l.distance;
	}
};

template <typename T>
class Graph {
private:
	unsigned V;
	vector<Edge<T>> edge_list;
public:
	Graph(unsigned N) : V(N) {}
	auto vertices() const { return V; }
	auto& edges() const { return edge_list; }
	auto edges(unsigned v) const { // const : 이 함수 안에서 쓰는 값들을 변경할 수 없다
		vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list) {
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		return edges_from_v;
	}
	void add_edge(Edge<T>&& e) { // 인자로 들어오는 구조체는 템플릿이기 때문에 참조 표시(&) 2번 쓴다고 한다
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			cerr << "errors" << endl;
	}
	template <typename U>
	friend ostream& operator<< (ostream&, const Graph<U>& G); // 템플릿을 썼기 때문에 필요
};

template<typename U>
ostream& operator<< (ostream& os, const Graph<U>& G) { // 근데 이거 클래스 선언 안해도 정의가 돼? 위에 써있는 거랑 약간 다르긴 한데 그게 무슨 차이인지는 모름
	for (unsigned i = 1; i < G.vertices(); ++i) {
		os << i << ":\t";
		auto edges = G.edges(i);
		for (auto& e : edges)
			os << "{" << e.dst << ": " << e.weight << "}, ";
		os << endl;
	}
	return os;
}

template <typename T>
auto create_reference_graph() {
	Graph<T> G(9);
	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2, 2}, {5, 3} }; // 1번에서 시작해서 { {2번으로 가중치 2}, {5번으로 가중치 3} }
	edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
	edge_map[3] = { {4, 2}, {7, 3} };
	edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
	edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
	edge_map[7] = { {3, 3}, {6, 4} };
	edge_map[8] = { {4, 5}, {5, 3}, {6, 1} };
	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{i.first, j.first, j.second}); // 순서대로 정점의 키, 연결된 정점, 가중치
	return G;
}

template <typename T>
auto CDIJKSTRA(const Graph<T>& G, unsigned src, unsigned dst) {
	priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;
	vector<T> distance(G.vertices(), numeric_limits<T>::max()); // numeric_limits<T>::max() : int가 가질 수 있는 최댓값
	set<unsigned> visited;
	vector<unsigned> parent(G.vertices());
	heap.emplace(Label<T>{src, 0});
	parent[src] = src;
	while (!heap.empty()) {
		auto current_vertex = heap.top();
		heap.pop();
		if (current_vertex.ID == dst) {
			cout << "Arrived at the destination vertex " << current_vertex.ID << endl;
			break;
		}
		if (visited.find(current_vertex.ID) == visited.end()) {
			cout << "Arrived at the vertex " << current_vertex.ID << endl;
			for (auto& e : G.edges(current_vertex.ID)) {
				auto neighbor = e.dst;
				auto new_distance = current_vertex.distance + e.weight;
				if (new_distance < distance[neighbor]) {
					heap.emplace(Label<T>{neighbor, new_distance});
					parent[neighbor] = current_vertex.ID;
					distance[neighbor] = new_distance;
				}
			}
			visited.insert(current_vertex.ID);
		}
	}
	vector<unsigned> shortest_path;
	auto current_vertex = dst;
	while (current_vertex != src) {
		shortest_path.push_back(current_vertex);
		current_vertex = parent[current_vertex];
	}
	shortest_path.push_back(src);
	reverse(shortest_path.begin(), shortest_path.end());
	return shortest_path;
}

int main() {
	using T = unsigned;
	auto G = create_reference_graph<T>();
	cout << "Reference graph" << endl;
	cout << G << endl;
	auto shortest_path = CDIJKSTRA<T>(G, 1, 6);
	cout << endl << "The shortest path between the vertex 1 and 6" << endl;
	for (auto v : shortest_path)
		cout << v << ' ';
	cout << endl;

    return 0;
}