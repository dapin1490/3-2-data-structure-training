#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy, sort(예정)
using namespace std;

class complain_node { // 민원 노드 클래스
private:
	string pic_name; // 사진 파일명
	pair<int, int> pic_size; // 사진 크기
	pair<double, double> coordinates; // 좌표

public:
	int wastes[5]; // 쓰레기 유무 표시

	complain_node(string pn, int width, int height, double x, double y, int ws[5]);

	// 각 멤버 변수별 값을 반환하는 메소드들
	string get_name() { return pic_name; }
	pair<int, int> get_size() { return pic_size; }
	pair<int, int> get_codi() { return coordinates; }
};

class accumulate_node { // 누적 민원 노드 클래스
private:
	int waste_number; // 쓰레기 분류 번호
	vector<complain_node> compl_list; // 해당 민원 벡터

public:
	/* 생성자는 프로그램 첫 실행 시 사용자의 조작 없이 자동으로 정해진 수만큼 실행되게 할 것.
	민원이 하나도 들어오지 않은 상태를 전제로 한다. */
	accumulate_node(int wn);

	// 새 민원 추가됨
	void add_compl();

	// 누적 민원 처리
	void clear_compl();

	// 쓰레기 분류 번호 반환
	int get_wnum() { return waste_number; }

	// 누적 민원 수 반환
	int get_num_of_compls() { return compl_list.size(); }

	// 민원 벡터 반환
	vector<complain_node> get_compl_list() { return compl_list; }
};

class waste_system { // 하천 쓰레기 민원 처리 시스템
private:
	accumulate_node acc_list[5]; // 누적 민원 객체 배열
	int area; // 담당 지역 번호(행정동코드 사용, 사용자가 시스템 생성 시 직접 입력)


public:
	// 생성자 등등 추가
};

int main() {
	// 빠른 입출력
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	return 0;
}

accumulate_node::accumulate_node(int wn) {
	waste_number = wn;
}

complain_node::complain_node(string pn, int width, int height, double x, double y, int ws[5]) {
	pic_name = pn;
	pic_size = make_pair(width, height);
	coordinates = make_pair(x, y);
	copy(ws, ws + 5, wastes); // 배열 복사 참고 : https://terrorjang.tistory.com/98
}
