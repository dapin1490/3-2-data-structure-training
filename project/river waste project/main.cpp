#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy
using namespace std;

class accumulate_node { // 누적 민원 노드 클래스
private:
	int waste_number; // 쓰레기 분류 번호
	int accmed_compls; // 누적 민원 수
	vector<complain_node> compl_list; // 해당 민원 벡터

public:
	/* 생성자는 프로그램 첫 실행 시 사용자의 조작 없이 자동으로 정해진 수만큼 실행되게 할 것.
	민원이 하나도 들어오지 않은 상태를 전제로 한다. */
	accumulate_node(int wn);
	/*
	필요 메소드
	+ 누적 민원 수 변경 메소드
	+ 쓰레기 분류 번호 반환 메소드
	+ 누적 민원 수 반환 메소드
	+ 민원 벡터 반환 메소드
	*/
};

class complain_node { // 민원 노드 클래스
private:
	string pic_name; // 사진 파일명
	pair<int, int> pic_size; // 사진 크기
	pair<double, double> coordinates; // 좌표
	int wastes[5]; // 쓰레기 유무 표시

public:
	complain_node(string pn, int width, int height, double x, double y, int ws[5]);

	/*
	필요 메소드
	+ 각 멤버 변수별 값을 반환하는 메소드들
	+ 쓰레기 유무 배열 변경 메소드
	*/
};

int main() {
	// 빠른 입출력
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	return 0;
}

accumulate_node::accumulate_node(int wn) {
	waste_number = wn;
	accmed_compls = 0;
}

complain_node::complain_node(string pn, int width, int height, double x, double y, int ws[5]) {
	pic_name = pn;
	pic_size = make_pair(width, height);
	coordinates = make_pair(x, y);
	copy(ws, ws + 5, wastes); // 배열 복사 참고 : https://terrorjang.tistory.com/98
}
