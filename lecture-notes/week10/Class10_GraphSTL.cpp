#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <utility>
using namespace std;
// 각 개체는 ADJ MATRIX의 인덱스로 연결지으면 편합니다. 따라서 enumerator 자료구조를 사용하며, 사용하기 편하게 객체로 선언합니다.
// enum는 특별히 지정하지 않으면 첫 값은 0으로 시작하여 마치 배열이나 MATRIX의 인덱스처럼 1씩 증가하죠? ADJ MATRIX의 인덱스로 사용하기 편할 겁니다.
// enum의 자세한 사용 방법은 웹페이지 https://en.cppreference.com/w/cpp/language/enum 를 참조하세요.
enum class city : int { SVO, LHR, ICN, SEA, DXB, SYD };

std::ostream& operator<<(std::ostream& os, const city _c) { // LINE 52의 콘솔창 출력을 위한 연산자 오버로딩입니다. cout << 는 ostream에 있으니 ostream의 연산자 << 를 LINE 10에 만든 city 클래스를 이용해 오버로딩합니다.
	switch (_c) { // enum에 저장한 내용들에 대해,
	case city::SVO: // SVO인 경우
		os << "MOSCOW"; // MOSCOW 라는 문자열을 출력할 수 있도록, 합니다. 아래처럼 switch-case 를 사용해서 일일이 지정해 둬야 합니다. switch 문은 작성이 조금 귀찮지만, 작성만 해두면 직관적으로 사용하기 편합니다.
		return os;
	case city::LHR:
		os << "LONDON";
		return os;
	case city::ICN:
		os << "INCHEON";
		return os;
	case city::SEA:
		os << "SEATLE";
		return os;
	case city::DXB:
		os << "DUBAI";
		return os;
	case city::SYD:
		os << "SYDNEY";
		return os;
	default:
		return os;
	}
}

class CGraph {
	vector<vector<int>> mat_data; // ADJ MATRIX(인접 행렬)입니다. 정점의 갯수 n만큼 nxn matrix로 만듭니다. 정점의 갯수를 모르고 변할 수 있으니 vector로 만듭니다. 2차원 vector 선언 방법도 익혀 두세요.
	vector <list<pair<city, int>>> adj_data; // ADJ LIST(인접 리스트)입니다. 정점의 갯수 n만큼 리스트를 만들고, 각각의 리스트는 pair를 이용해 해당 정점에서 이동할 수 있는 공항 정보와 거리 정보를 넣어둡니다.
public:
	CGraph(int _n) {
		mat_data.reserve(_n); // ADJ MATRIX 초기화 방법중 하나입니다. 먼저 행 갯수를 정점 수 만큼 만들어 줍니다.
		vector<int> v_row(_n); // 그리고 각 행에 들어갈 열 벡터를 크기 n으로 만들어 줍니다.
		fill(v_row.begin(), v_row.end(), -1); // 열 벡터를 -1로 초기화합니다. fill은 algorithm 헤더를 가져와서 사용할 수 있으며, iterator를 사용합니다. https://en.cppreference.com/w/cpp/algorithm/fill를 참조하세요.
		for (int i = 0; i < _n; ++i) { // 그리고 초기화 한 열 벡터를 이용해 LINE 42에 만들어 준 ADJ MATRIX의 각 행에 채워 넣습니다.
			mat_data.push_back(v_row);
		}

		adj_data.resize(_n); // ADJ LIST입니다. LIST는 정점 크기만큼 벡터로 선언해 두었으니, 간단히 resize를 이용해 n개 크기의 벡터를 만듭니다. LINE 39를 보면 벡터의 각 요소는 리스트로 만들어 두었죠?
	}
	void addUndirEdge(const city c1, const city c2, int dis) { // 두 도시를 연결합니다. 두 도시 객체를 그대로 가져오는 게 직관적이죠? 두 도시를 연결하고, 도시까지의 거리(그래프의 weight)를 LINE 39처럼 pair로 저장합니다.
		std::cout << "Add Edge : " << c1 << " - " << c2 << " = " << dis << endl; // 연결 잘 되었는지 확인해 줍니다. cout << 을 이용하기 위해, city 클래스(LINE 10)를 연산자 오버로딩해야 합니다. LINE 12에 작성해 두었습니다.
		auto n1 = static_cast<int>(c1); // enum 크래스의 객체들은 이제 ADJ MATRIX의 인덱스로 저장해 줘야 합니다. c1이 city 객체지만, enum로 만들었으니 int로 형변환만 하면 곧바로 인덱스로 사용할 수 있습니다.
		auto n2 = static_cast<int>(c2); // c1과 같이 인덱스로 사용하기 위해 형변환합니다.
		mat_data[n1][n2] = dis; // 그리고 ADJ MATRIX의 인덱스에 각각 거리 값을 넣어 줍니다.
		mat_data[n1][n2] = dis; // 무방향 그래프이니 대칭으로 넣어 줍니다.

		adj_data[n1].push_back(make_pair(c2, dis)); // ADJ LIST는 그 동안 계속 했으니 보다 익숙하죠? adj_data는 일단 벡터고, 벡터의 원소 adj_data[n1]은 list이며, list의 원소는 pair<city, int>입니다. 페어로 만들어 두면 도시와 거리를 쌍으로 확인하기 쉽겠죠?
		adj_data[n2].push_back(make_pair(c1, dis)); // 역시 무방향 그래프이니 반대로도 넣어 줍니다.
	}
	void remUndirEdge(const city c1, const city c2, int dis) { // ADJ MATRIX의 간선을 삭제합니다.
		cout << "Remove Edge : " << c1 << " - " << c2 << endl; // 연산자 오버로딩을 구현해 뒀으니 쉽게 사용이 가능합니다.
		auto n1 = static_cast<int>(c1); // LINE 53과 마찬가지로 객체의 인덱스를 가져옵니다.
		auto n2 = static_cast<int>(c2);
		mat_data[n1][n2] = -1; // 그리고 -1로 초기화합니다.
		mat_data[n2][n1] = -1;
	}
	void print_adj_airport() { // 그래프를 다 구성한 뒤 연결이 잘 되어 있는지 ADJ LIST를 전부 확인해 콘솔창에 출력해 보는 함수입니다. ADJ MATRIX는 그냥 매트릭스니 생략하고, ADJ LIST에 대한 내용만 담습니다. 이 함수의 사용은 LINE 103에 했어요.
		int n_airport = adj_data.size(); // 그래프를 만들기 전, 몇개의 정점이 주어질지 알 수 없으니 정점의 갯수(공항의 갯수)를 게산합니다.
											// ADJ LIST의 요소는 list로 되어 있습니다. 그리고 몇개의 정점과 연결되어 있는지 알지 못합니다(list의 크기를 알지 못합니다.) 따라서 iterator로 순회합니다.
		typedef list<pair <city, int>> A; // 그런데 list의 요소는 pair로 내가 따로 만든 형태이기 때문에, 그냥 막 iterator를 쓰기 어렵습니다. template을 이용해 내가 만든 형태를 A라고 정의해 줍니다.
		for (int i = 0; i < n_airport; ++i) { // 각각의 도시들을 전부 다 보겠습니다.
			cout << city(i) << " is connected to "; // 공항들을 하나씩 출력하고,

			A::iterator iter; // LINE 71에 만들어 둔 template을 이용해 iterator를 만듭니다.
			for (iter = adj_data[i].begin(); iter != adj_data[i].end(); ++iter) {	// iterator를 이용해 list의 내용을 처음부터 끝까지 살펴봅니다.
				cout << (*iter).first << " (" << (*iter).second << ")";	// iterator는 포인터를 사용합니다. pair 구성은 first는 도시이름, second는 거리로 만들었습니다(LINE 39, 58, 59).
				if (*iter != adj_data[i].back()) {		// list 맨 마지막 요소전까지는 해당 내용들을 계속 이어 붙이고,
					cout << ", and ";
				}
				else
					cout << endl; // list 맨 마지막 요소가 되면 줄을 바꾸고 다음 도시에 대해 출력합니다.
			}
		}
	}
};

int main() {
	CGraph OGraph(6);
	OGraph.addUndirEdge(city::LHR, city::SVO, 2500); // 사용법은 별 다를게 없으니 생략합니다.
	OGraph.addUndirEdge(city::LHR, city::ICN, 9000);
	OGraph.addUndirEdge(city::LHR, city::DXB, 5500);
	OGraph.addUndirEdge(city::ICN, city::SVO, 6600);
	OGraph.addUndirEdge(city::ICN, city::SEA, 2500);
	OGraph.addUndirEdge(city::ICN, city::DXB, 2500);
	OGraph.addUndirEdge(city::ICN, city::SYD, 2500);
	OGraph.addUndirEdge(city::SEA, city::SVO, 2500);
	OGraph.addUndirEdge(city::SEA, city::SYD, 2500);
	OGraph.addUndirEdge(city::SEA, city::LHR, 2500);
	OGraph.remUndirEdge(city::SEA, city::LHR, 2500);

	cout << endl << endl;
	OGraph.print_adj_airport();

	return 0;
}
