#pragma once

#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy, sort(����)
#include <map> // multimap ���� : https://blockdmask.tistory.com/88
#include <io.h> // ���� ���� Ȯ�� ���� : https://tw0226.tistory.com/121
#include <string> // to_string
#include <fstream> // ���� �����
#include <ctime>
#include <sstream>
using namespace std;

// �������ڵ� ��ó : https://www.mois.go.kr/frt/bbs/type001/commonSelectBoardArticle.do?bbsId=BBSMSTR_000000000052&nttId=94196

const string intxt = "../river waste project/data/input.txt";
const string outtxt = "../river waste project/data/output.txt";

extern ifstream input{ intxt };
extern ofstream output{ outtxt };

string currentDateTime() {
	time_t t = time(nullptr);
	tm now;
	errno_t is_error = localtime_s(&now, &t);

	if (is_error == 0) {
		char buffer[256];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &now);
		return buffer;
	}
	else {
		return "���� �ð��� ���� �� ����";
	}
}

// C++ ���� �޽��� ���� : https://learn.microsoft.com/ko-kr/cpp/error-messages/compiler-errors-1/c-cpp-build-errors?view=msvc-170
void error(int error_code) {
	switch (error_code) {
	case -1:
		output << "���α׷� ������ ����\n";
		break;
	case 0: // �߸��� �Է� - int
		output << "ValueErrorInt: int ���� �ԷµǾ�� �մϴ�.\n";
		break;
	case 1: // �߸��� �Է� - char
		output << "ValueErrorChar: char ���� �ԷµǾ�� �մϴ�.\n";
		break;
	default:
		output << "UnknownError: �� �� ���� ����\n";
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
	complain(string pn, int cdate, double x, double y, int wcnt, int* ws) {
		pic_name = pn;
		comp_date = cdate;
		coordinates = make_pair(x, y);
		waste_cnt = wcnt;
		copy(ws, ws + 5, wastes); // �迭 ���� ���� : https://terrorjang.tistory.com/98
	}
	complain(string pn, int cdate, double x, double y, int wcnt, string ws) {
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

	string get_name() { return pic_name; } // ���� �̸� ��ȯ
	int get_date() { return comp_date; } // �ο� �Ű� ��¥ ��ȯ
	pair<double, double> get_codi() { return coordinates; } // ���� ��ǥ ��ȯ(pair)
	int get_wcnt() { return waste_cnt; } // ���� ������ ���� �� ��ȯ

	void rename(string new_name) { pic_name = new_name; } // ���� �̸� ����
	void update_wcnt(int num) { waste_cnt += num; } // ���� ������ ���� �� ����
	// �ο� �Ű� ��¥ ���
	void print_date() { output << comp_date / 10000 << "�� " << comp_date % 10000 / 100 << "�� " << comp_date % 100 << "��\n"; }
};

class accumed_compls { // ���� �ο� Ŭ����
private:
	int waste_code; // ������ �з� ��ȣ
	vector<complain*> compls; // ������ �з� ��ȣ�� ���� �ش� ������ ���� �ο� ����
public:
	accumed_compls() { waste_code = NULL; }; // �⺻ ������
	accumed_compls(int wn) { // ������
		waste_code = wn;
	}

	int get_num() { return waste_code; } // ������ �з� ��ȣ ��ȯ
	int get_compls_size() { return compls.size(); } // �ο� ��� ���� ����(���� �ο� ��) ��ȯ

	void add_compl(complain* new_comp) { compls.push_back(new_comp); } // �ο� �߰�
	void clear_compls() { // �ο� ó��(���� �ο� ���͸� clear�ϸ�, ���� �ο� �� 2���� �̻��� �����Ⱑ ���Ե� �ο��� ��� ������ ���� ǥ�⸦ ������ �� clear�ؾ� �Ѵ�.)
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
};

class compl_system { // ��õ ������ �ο� ó�� �ý���
private:
	string area_code; // ���� �ڵ�(������/������ ���)
	accumed_compls compls_list[5]; // ������ �з��� ���� �ο� �迭

	vector<complain*> all_compls; // ��ü �ο� ����
	multimap<string, complain*> comp_map; // ���� �̸� ���� ��ü �ο� ��Ƽ��
	multimap<double, complain*> latitude_map; // ���� ���� ��ü �ο� ��Ƽ��
	multimap<double, complain*> longitude_map; // �浵 ���� ��ü �ο� ��Ƽ��
	multimap<int, complain*, greater<int>> cdate_map_front; // �ο� ���� ��¥ ����(�ֱټ�) ��ü �ο� ��Ƽ��
	multimap<int, complain*> cdate_map_back; // �ο� ���� ��¥ ����(�����ȼ�) ��ü �ο� ��Ƽ��
	// �� ��������(greater) ���� : https://0xd00d00.github.io/2021/08/22/map_value_reverse.html
public:
	compl_system() { area_code = ""; } // �⺻ ������
	compl_system(string area) { // ������
		area_code = area;
		for (int i = 0; i < 5; i++) {
			compls_list[i] = accumed_compls(i);
		}
	}

	string get_acode() { return area_code; }

	void system_on() { // �ý��� ���� : ����ڿ��� ���� �ڵ带 �Է¹ް� ���� ������ ���� Ȯ��, �� �α� ���� ��
		string areacode;
		string file_route;
		bool is_file_valuable;
		char is_load_save;

		output << "��õ ������ �ο� ó�� �ý����� �����մϴ�. ���� ��ȣ�� ���ڸ� �Է��� �ּ���.\n";
		input >> areacode; // 20220901 ���� �������ڵ� csv ���Ͽ��� ��ȣ Ž���Ͽ� �߸��� �Է� ó�� �ʿ�
		output << "�Էµ� ������ȣ�� " << areacode << "�Դϴ�.\n";

		this->area_code = areacode;
		file_route = "data/" + areacode + ".csv";
		is_file_valuable = _access(file_route.c_str(), 0) != -1;

		if (is_file_valuable) { // ���� ���� Ȯ�� ���� : https://tw0226.tistory.com/121
			// ���� ������ ���� ������
			output << "���� �����Ͱ� �����մϴ�. �ҷ����ðڽ��ϱ�? Y / N\n";
			input >> is_load_save;
			output << "�Էµ� ���� " << is_load_save << "�Դϴ�.\n";

			if (is_load_save == 'N') { // ���� ������ �ҷ����� �ʱ�
				output << "����ϱ⸦ �����ϸ� ������ �����Ͱ� ��� �ҽǵ˴ϴ�. ����Ͻðڽ��ϱ�? Y / N\n";
				input >> is_load_save;
				output << "�Էµ� ���� " << is_load_save << "�Դϴ�.\n";

				switch (is_load_save) {
				case 'Y': // ���� ������ �����ϰ� �� ������ ���� ����
					is_load_save = 'N';
					break;
				case 'N': // ���� ������ ����ϱ�� ��
					is_load_save = 'Y';
					break;
				default: // �̻��� ��� �ϸ� ���� �� �� ����
					output << "�߸��� �Է�: 'Y' �Ǵ� 'N'�� �Է��� �� �ֽ��ϴ�.\n";
					error(-1);
				}
			}

			if (is_load_save == 'Y') { // ���� ������ �ҷ�����
				this->load_save(file_route);
			}
		}
		else if (!is_file_valuable) { // ���� ������ ���� �������� ����
			// �� ���̺� ���� ����� �޼ҵ� ����
		}

		if (is_file_valuable && is_load_save == 'N') {
			// ���� ������ ���� ���������� ����ڰ� ������ �����͸� �ҷ����� �ʱ�� ����
			// ���̺� ������ ������ �ε��� ���̺갡 �����Ƿ� �޼ҵ� ����.
			return;
		}
	}
	void receive_compl(); // �ο� ����

	void view_all(); // ���� ����(sort_by)�� ���� ��ü �ο� ��ȸ(����ϰ� �� ���̹Ƿ� ��ȯ�� ����)
	void search_compl(); // �˻� ����(search_by)�� ���� Ư�� �ο� �˻�

	bool is_enough(int waste_code); // Ư�� �з��� ������ �ο��� ����� ���� ó���ص� �ɸ����� Ȯ��
	void clear_compls(int waste_code); // Ư�� �з��� ������ ���� �ο� �ϰ� ó�� : ó�� �� ��ü �ο� ���ͳ� �ٸ� �� ��� NULL�� �����ϴ� ������ �ʿ���
	// ���Ϳ��� NULL ����� ���� : https://cho001.tistory.com/164

	void load_save(string froute) { // ���Ͽ� ��ϵ� �����͸� ���� ���� ���� ��� �ε�. �Ź� �� �ý����� ������ ���� �����ϱ�.
		ifstream data_file{ froute };

		string pic_name;
		int comp_date;
		pair<double, double> coordinates;
		int waste_cnt;
		int wastes[5];

		output << "start loading...\n";

		while (!data_file.eof()) {
			string line;
			istringstream word; // ���� : https://chbuljumeok1997.tistory.com/42

			getline(data_file, line);
			word = istringstream(line);
				
			word >> line; // ���� : https://myprivatestudy.tistory.com/48
			pic_name = line;
				
			word >> line;
			comp_date = stoi(line);

			word >> line;
			coordinates.first = stod(line);
			word >> line;
			coordinates.second = stod(line);

			word >> line;
			waste_cnt = stoi(line);

			for (int i = 0; i < 5; i++) {
				word >> line;
				wastes[i] = stoi(line);
			}

			complain cp{ pic_name, comp_date, coordinates.first, coordinates.second, waste_cnt, wastes };
			this->all_compls.push_back(&cp);
			this->comp_map.emplace(cp.get_name(), &cp);
			this->latitude_map.emplace(cp.get_codi().first, &cp);
			this->longitude_map.emplace(cp.get_codi().second, &cp);
			this->cdate_map_front.emplace(cp.get_date(), &cp);
			this->cdate_map_back.emplace(cp.get_date(), &cp);

			for (int i = 0; i < 5; i++) {
				switch (cp.wastes[i]) {
				case 0:
					continue;
				default:
					this->compls_list[i].add_compl(&cp);
				}
			}
		}

		output << "load complete\n";
		data_file.close();
	}
	void save_task(); // ���� ���� ��Ȳ�� ���Ϸ� ���. ������ �����ϰų� �߰� ������ �ʿ��� �� ����.
};