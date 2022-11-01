#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy, sort(����)
#include <map> // multimap ���� : https://blockdmask.tistory.com/88
#include <io.h> // ���� ���� Ȯ�� ���� : https://tw0226.tistory.com/121
#include <string> // to_string
using namespace std;

// �������ڵ� ��ó : https://www.mois.go.kr/frt/bbs/type001/commonSelectBoardArticle.do?bbsId=BBSMSTR_000000000052&nttId=94196

// C++ ���� �޽��� ���� : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(int error_code) {
	switch (error_code) {
	case 0: // �߸��� �Է� - int
		cout << "ValueErrorInt: int ���� �ԷµǾ�� �մϴ�.\n";
		break;
	case 1: // �߸��� �Է� - char
		cout << "ValueErrorChar: char ���� �ԷµǾ�� �մϴ�.\n";
		break;
	default:
		cout << "UnknownError: �� �� ���� ����\n";
	}
	exit(1); // ���α׷� ������ ����
}

class complain { // �ο� Ŭ����
private:
	string pic_name; // ���� �̸�(�ʿ�� ����/��� ���� ��� ����, ���� ũ�⸦ ����� ���� ���� ��ü�� ���� ���� ������ ���� ������ ������ ���Եȴٰ� ����)
	int comp_date; // �ο� �Ű� ��¥
	pair<double, double> coordinates; // ���� ��ǥ
	int waste_cnt; // ���Ե� �������� ���� ��
public:
	int wastes[5]; // ��� �������� ������ getter�� �ᵵ �����ͷ� ���޵Ǿ� ���� ������ �����ϴ� public ������ ���

public:
	complain(string pn, int cdate, double x, double y, int wcnt, int* ws);
	complain(string pn, int cdate, double x, double y, int wcnt, string ws);

	string get_name() { return pic_name; } // ���� �̸� ��ȯ
	int get_date() { return comp_date; } // �ο� �Ű� ��¥ ��ȯ
	pair<double, double> get_codi() { return coordinates; } // ���� ��ǥ ��ȯ(pair)
	int get_wcnt() { return waste_cnt; } // ���� ������ ���� �� ��ȯ

	void rename(string new_name) { pic_name = new_name; } // ���� �̸� ����
	void update_wcnt(int num) { waste_cnt += num; } // ���� ������ ���� �� ����
	// �ο� �Ű� ��¥ ���
	void print_date() { cout << comp_date / 10000 << "�� " << comp_date % 10000 / 100 << "�� " << comp_date % 100 << "��\n"; }
};

class accumed_compls { // ���� �ο� Ŭ����
private:
	int waste_code; // ������ �з� ��ȣ
	vector<complain*> compls; // ������ �з� ��ȣ�� ���� �ش� ������ ���� �ο� ����
public:
	accumed_compls() { waste_code = NULL; }; // �⺻ ������
	accumed_compls(int wn); // ������

	int get_num() { return waste_code; } // ������ �з� ��ȣ ��ȯ
	int get_compls_size() { return compls.size(); } // �ο� ��� ���� ����(���� �ο� ��) ��ȯ

	void add_compl(complain* new_comp) { compls.push_back(new_comp); } // �ο� �߰�
	void clear_compls(); // �ο� ó��(���� �ο� ���͸� clear�ϸ�, ���� �ο� �� 2���� �̻��� �����Ⱑ ���Ե� �ο��� ��� ������ ���� ǥ�⸦ ������ �� clear�ؾ� �Ѵ�.)
};

class compl_system { // ��õ ������ �ο� ó�� �ý���
private:
	long long area_code; // ���� �ڵ�(������/������ ���)
	accumed_compls compls_list[5]; // ������ �з��� ���� �ο� �迭
	
	vector<complain*> all_compls; // ��ü �ο� ����
	multimap<string, complain*> comp_map; // ���� �̸� ���� ��ü �ο� ��Ƽ��
	multimap<double, complain*> longitude_map; // �浵 ���� ��ü �ο� ��Ƽ��
	multimap<double, complain*> latitude_map; // ���� ���� ��ü �ο� ��Ƽ��
	multimap<int, complain*, greater<int>> cdate_map_front; // �ο� ���� ��¥ ����(�ֱټ�) ��ü �ο� ��Ƽ��
	multimap<int, complain*> cdate_map_back; // �ο� ���� ��¥ ����(�����ȼ�) ��ü �ο� ��Ƽ��
	// �� ��������(greater) ���� : https://0xd00d00.github.io/2021/08/22/map_value_reverse.html
public:
	compl_system() { area_code = NULL; } // �⺻ ������
	compl_system(long long area); // ������

	void system_on(); // �ý��� ���� : ����ڿ��� ���� �ڵ带 �Է¹ް� ���� ������ ���� Ȯ��, �� �α� ���� ��
	void receive_compl(); // �ο� ����
	
	void view_all(); // ���� ����(sort_by)�� ���� ��ü �ο� ��ȸ(����ϰ� �� ���̹Ƿ� ��ȯ�� ����)
	void search_compl(); // �˻� ����(search_by)�� ���� Ư�� �ο� �˻�
	
	bool is_enough(int waste_code); // Ư�� �з��� ������ �ο��� ����� ���� ó���ص� �ɸ����� Ȯ��
	void clear_compls(int waste_code); // Ư�� �з��� ������ ���� �ο� �ϰ� ó�� : ó�� �� ��ü �ο� ���ͳ� �ٸ� �� ��� NULL�� �����ϴ� ������ �ʿ���
	// ���Ϳ��� NULL ����� ���� : https://cho001.tistory.com/164

	void load_save(); // ���Ͽ� ��ϵ� �����͸� ���� ���� ���� ��� �ε�. �Ź� �� �ý����� ������ ���� �����ϱ�.
	void save_task(); // ���� ���� ��Ȳ�� ���Ϸ� ���. ������ �����ϰų� �߰� ������ �ʿ��� �� ����.
};

int main() {
	// ���� �����
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	return 0;
}

complain::complain(string pn, int cdate, double x, double y, int wcnt, int* ws) {
	pic_name = pn;
	comp_date = cdate;
	coordinates = make_pair(x, y);
	waste_cnt = wcnt;
	copy(ws, ws + 5, wastes); // �迭 ���� ���� : https://terrorjang.tistory.com/98
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

void accumed_compls::clear_compls() { // �ο� ó��(���� �ο� ���͸� clear�ϸ�, ���� �ο� �� 2���� �̻��� �����Ⱑ ���Ե� �ο��� ��� ������ ���� ǥ�⸦ ������ �� clear�ؾ� �Ѵ�.)
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

	cout << "��õ ������ �ο� ó�� �ý����� �����մϴ�. ���� ��ȣ�� �Է��� �ּ���.\n";
	cin >> areacode; // 20220901 ���� �������ڵ� csv ���Ͽ��� ��ȣ Ž���Ͽ� �߸��� �Է� ó�� �ʿ�

	file_route = "data/" + to_string(areacode) + ".csv";
	is_file_valuable = _access(file_route.c_str(), 0) != -1;

	if (is_file_valuable) { // ���� ���� Ȯ�� ���� : https://tw0226.tistory.com/121
		// ���� ������ ���� ������
		cout << "���� �����Ͱ� �����մϴ�. �ҷ����ðڽ��ϱ�? Y / N\n";
		cin >> is_load_save;

		for (int i = 1; i <= 6; i++) {
			if (is_load_save == 'Y' || is_load_save == 'N')
				break;
			if (i == 6) {
				cout << "�Է� Ƚ���� �ʰ��߽��ϴ�. ���α׷��� �����մϴ�.\n";
				error(1);
			}

			cout << "�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է��Ͻʽÿ�. (5ȸ �� " << i << "ȸ) Y / N\n";
			cin >> is_load_save;
		}

		if (is_load_save == 'N') { // ���� ������ �ҷ����� �ʱ�
			cout << "����ϱ⸦ �����ϸ� ������ �����Ͱ� ��� �ҽǵ˴ϴ�. ����Ͻðڽ��ϱ�? Y / N";
			cin >> is_load_save;

			switch (is_load_save) {
			case 'Y': // ���� ������ �����ϰ� �� ������ ���� ����
				is_load_save = 'N';
				break;
			case 'N': // ���� ������ ����ϱ�� ��
				is_load_save = 'Y';
				break;
			default: // �� �̻��� ��� �ϸ� ���� �� �� ����
				error(1);
			}
		}
		if (is_load_save == 'Y') { // ���� ������ �ҷ�����

		}
	}

	if (!is_file_valuable || (is_file_valuable && is_load_save == 'N')) {
		// ���� ������ ���� �������� �ʰų�, ���������� ����ڰ� ������ �����͸� �ҷ����� �ʱ�� ����
	}
}
