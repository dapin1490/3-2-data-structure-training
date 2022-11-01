#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy, sort(예정)
#include <map> // multimap 참고 : https://blockdmask.tistory.com/88
#include <io.h> // 파일 존재 확인 참고 : https://tw0226.tistory.com/121
#include <string> // to_string
using namespace std;

// 행정동코드 출처 : https://www.mois.go.kr/frt/bbs/type001/commonSelectBoardArticle.do?bbsId=BBSMSTR_000000000052&nttId=94196

// C++ 에러 메시지 참고 : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(int error_code) {
	switch (error_code) {
	case 0: // 잘못된 입력 - int
		cout << "ValueErrorInt: int 값이 입력되어야 합니다.\n";
		break;
	case 1: // 잘못된 입력 - char
		cout << "ValueErrorChar: char 값이 입력되어야 합니다.\n";
		break;
	default:
		cout << "UnknownError: 알 수 없는 오류\n";
	}
	exit(1); // 프로그램 비정상 종료
}

class complain { // 민원 클래스
private:
	string pic_name; // 사진 이름(필요시 절대/상대 파일 경로 포함, 사진 크기를 비롯해 사진 파일 자체에 대한 각종 정보는 원본 파일의 정보에 포함된다고 본다)
	int comp_date; // 민원 신고 날짜
	pair<double, double> coordinates; // 사진 좌표
	int waste_cnt; // 포함된 쓰레기의 종류 수
public:
	int wastes[5]; // 멤버 변수지만 어차피 getter를 써도 포인터로 전달되어 원본 수정이 가능하니 public 변수로 사용

public:
	complain(string pn, int cdate, double x, double y, int wcnt, int* ws);
	complain(string pn, int cdate, double x, double y, int wcnt, string ws);

	string get_name() { return pic_name; } // 사진 이름 반환
	int get_date() { return comp_date; } // 민원 신고 날짜 반환
	pair<double, double> get_codi() { return coordinates; } // 사진 좌표 반환(pair)
	int get_wcnt() { return waste_cnt; } // 포함 쓰레기 종류 수 반환

	void rename(string new_name) { pic_name = new_name; } // 사진 이름 변경
	void update_wcnt(int num) { waste_cnt += num; } // 포함 쓰레기 종류 수 변경
	// 민원 신고 날짜 출력
	void print_date() { cout << comp_date / 10000 << "년 " << comp_date % 10000 / 100 << "월 " << comp_date % 100 << "일\n"; }
};

class accumed_compls { // 누적 민원 클래스
private:
	int waste_code; // 쓰레기 분류 번호
	vector<complain*> compls; // 쓰레기 분류 번호에 따른 해당 쓰레기 관련 민원 벡터
public:
	accumed_compls() { waste_code = NULL; }; // 기본 생성자
	accumed_compls(int wn); // 생성자

	int get_num() { return waste_code; } // 쓰레기 분류 번호 반환
	int get_compls_size() { return compls.size(); } // 민원 노드 벡터 길이(누적 민원 수) 반환

	void add_compl(complain* new_comp) { compls.push_back(new_comp); } // 민원 추가
	void clear_compls(); // 민원 처리(누적 민원 벡터를 clear하며, 개별 민원 중 2종류 이상의 쓰레기가 포함된 민원의 경우 쓰레기 포함 표기를 수정한 후 clear해야 한다.)
};

class compl_system { // 하천 쓰레기 민원 처리 시스템
private:
	long long area_code; // 지역 코드(행정동/법정동 등등)
	accumed_compls compls_list[5]; // 쓰레기 분류별 누적 민원 배열
	
	vector<complain*> all_compls; // 전체 민원 벡터
	multimap<string, complain*> comp_map; // 사진 이름 기준 전체 민원 멀티맵
	multimap<double, complain*> longitude_map; // 경도 기준 전체 민원 멀티맵
	multimap<double, complain*> latitude_map; // 위도 기준 전체 민원 멀티맵
	multimap<int, complain*, greater<int>> cdate_map_front; // 민원 접수 날짜 기준(최근순) 전체 민원 멀티맵
	multimap<int, complain*> cdate_map_back; // 민원 접수 날짜 기준(오래된순) 전체 민원 멀티맵
	// 맵 내림차순(greater) 참고 : https://0xd00d00.github.io/2021/08/22/map_value_reverse.html
public:
	compl_system() { area_code = NULL; } // 기본 생성자
	compl_system(long long area); // 생성자

	void system_on(); // 시스템 시작 : 사용자에게 지역 코드를 입력받고 기존 데이터 유무 확인, 새 로그 생성 등
	void receive_compl(); // 민원 접수
	
	void view_all(); // 정렬 기준(sort_by)에 따른 전체 민원 조회(출력하게 할 것이므로 반환값 없음)
	void search_compl(); // 검색 기준(search_by)에 따른 특정 민원 검색
	
	bool is_enough(int waste_code); // 특정 분류의 쓰레기 민원이 충분히 많아 처리해도 될만한지 확인
	void clear_compls(int waste_code); // 특정 분류의 쓰레기 관련 민원 일괄 처리 : 처리 후 전체 민원 벡터나 다른 맵 등에서 NULL을 제거하는 과정이 필요함
	// 벡터에서 NULL 지우기 참고 : https://cho001.tistory.com/164

	void load_save(); // 파일에 기록된 데이터를 통한 이전 업무 기록 로드. 매번 새 시스템을 생성할 수는 없으니까.
	void save_task(); // 업무 진행 상황을 파일로 기록. 업무를 종료하거나 중간 저장이 필요할 때 실행.
};

int main() {
	// 빠른 입출력
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	return 0;
}

complain::complain(string pn, int cdate, double x, double y, int wcnt, int* ws) {
	pic_name = pn;
	comp_date = cdate;
	coordinates = make_pair(x, y);
	waste_cnt = wcnt;
	copy(ws, ws + 5, wastes); // 배열 복사 참고 : https://terrorjang.tistory.com/98
}

complain::complain(string pn, int cdate, double x, double y, int wcnt, string ws) {
	pic_name = pn;
	comp_date = cdate;
	coordinates = make_pair(x, y);
	waste_cnt = wcnt;
	
	for (int i = 0; i < 5; i++) {
		switch (ws.at(i)) {
		case '0':
			wastes[i] = 0;
			break;
		case '1':
			wastes[i] = 1;
			break;
		default:
			wastes[i] = NULL;
		}
	}
}

accumed_compls::accumed_compls(int wn) {
	waste_code = wn;
}

void accumed_compls::clear_compls() { // 민원 처리(누적 민원 벡터를 clear하며, 개별 민원 중 2종류 이상의 쓰레기가 포함된 민원의 경우 쓰레기 포함 표기를 수정한 후 clear해야 한다.)
	vector<complain*>::iterator i;

	for (i = compls.begin(); i != compls.end(); i++) {
		if ((*i)->get_wcnt() > 1) {
			(*i)->update_wcnt(-1);
			(*i)->wastes[waste_code] = 0;
		}

		if ((*i)->get_wcnt() == 0) {
			complain* del_comp = (*i);
			(*i) = nullptr;
			delete del_comp;
		}
	}

	compls.clear();
}

compl_system::compl_system(long long area) {
	area_code = area;
	for (int i = 0; i < 5; i++) {
		compls_list[i] = accumed_compls(i);
	}
}

void compl_system::system_on() {
	long long areacode;
	string file_route;
	bool is_file_valuable;
	char is_load_save;

	cout << "하천 쓰레기 민원 처리 시스템을 시작합니다. 지역 번호를 입력해 주세요.\n";
	cin >> areacode; // 20220901 기준 행정동코드 csv 파일에서 번호 탐색하여 잘못된 입력 처리 필요

	file_route = "data/" + to_string(areacode) + ".csv";
	is_file_valuable = _access(file_route.c_str(), 0) != -1;

	if (is_file_valuable) { // 파일 존재 확인 참고 : https://tw0226.tistory.com/121
		// 기존 데이터 파일 존재함
		cout << "기존 데이터가 존재합니다. 불러오시겠습니까? Y / N\n";
		cin >> is_load_save;

		for (int i = 1; i <= 6; i++) {
			if (is_load_save == 'Y' || is_load_save == 'N')
				break;
			if (i == 6) {
				cout << "입력 횟수를 초과했습니다. 프로그램을 종료합니다.\n";
				error(1);
			}

			cout << "올바르지 않은 입력입니다. 다시 입력하십시오. (5회 중 " << i << "회) Y / N\n";
			cin >> is_load_save;
		}

		if (is_load_save == 'N') { // 기존 데이터 불러오지 않기
			cout << "계속하기를 선택하면 기존의 데이터가 모두 소실됩니다. 계속하시겠습니까? Y / N";
			cin >> is_load_save;

			switch (is_load_save) {
			case 'Y': // 기존 데이터 무시하고 새 데이터 생성 진행
				is_load_save = 'N';
				break;
			case 'N': // 기존 데이터 사용하기로 함
				is_load_save = 'Y';
				break;
			default: // 또 이상한 대답 하면 나도 안 해 던져
				error(1);
			}
		}
		if (is_load_save == 'Y') { // 기존 데이터 불러오기

		}
	}

	if (!is_file_valuable || (is_file_valuable && is_load_save == 'N')) {
		// 기존 데이터 파일 존재하지 않거나, 존재하지만 사용자가 기존의 데이터를 불러오지 않기로 했음
	}
}
