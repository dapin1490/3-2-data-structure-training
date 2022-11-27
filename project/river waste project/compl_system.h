#pragma once

#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy, equal, sort(����)
#include <map> // multimap ���� : https://blockdmask.tistory.com/88
#include <io.h> // ���� ���� Ȯ�� ���� : https://tw0226.tistory.com/121
#include <string> // to_string
#include <fstream> // ���� �����
#include <ctime>
#include <sstream>
using namespace std;

// �������ڵ� ��ó : https://www.mois.go.kr/frt/bbs/type001/commonSelectBoardArticle.do?bbsId=BBSMSTR_000000000052&nttId=94196

enum class _error : int{shut_down, ValueErrorInt, ValueErrorChar, UnknownError};

const string root = "C:/Users/dpgbu/Desktop/SAE/tool/github desktop/3-2-data-structure-training/project/river waste project/";
const string intxt = root + "data/input.txt";
const string outtxt = root + "data/output.txt";

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
void error(_error code, string message="") {
	if (message.length() > 1) {
		output << "error message: " << message << "\n";
	}

	switch (code) {
	case _error::shut_down:
		output << "���α׷� ������ ����\n";
		break;
	case _error::ValueErrorInt: // �߸��� �Է� - int
		output << "ValueErrorInt: int ���� �ԷµǾ�� �մϴ�.\n";
		break;
	case _error::ValueErrorChar: // �߸��� �Է� - char
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
	time_t rawtime; // �ο� �Ű� ��¥(time_t)
	tm comp_date; // �ο� �Ű� ��¥(tm)
	errno_t is_valid_date; // �ο� �Ű� ��¥�� ���� ���� ������ִ���
	pair<double, double> coordinates; // ���� ��ǥ
	int waste_cnt; // ���Ե� �������� ���� ��
public:
	int wastes[5]; // ��� �������� ������ getter�� �ᵵ �����ͷ� ���޵Ǿ� ���� ������ �����ϴ� public ������ ���

public:
	complain() { pic_name = "None"; }
	complain(string pn, int cdate, double x, double y, int wcnt, int* ws) {
		// ���� : https://cplusplus.com/reference/ctime/mktime/
		// ���� : https://www.it-note.kr/143
		rawtime = time(&rawtime);
		is_valid_date = localtime_s(&comp_date, &rawtime);
		comp_date.tm_year = cdate / 10000 - 1900;
		comp_date.tm_mon = cdate % 10000 / 100 - 1;
		comp_date.tm_mday = cdate % 100;
		rawtime = mktime(&comp_date);

		pic_name = pn;
		coordinates = make_pair(x, y);
		waste_cnt = wcnt;
		copy(ws, ws + 5, wastes); // �迭 ���� ���� : https://terrorjang.tistory.com/98
		
		// print();
	}
	complain(string pn, int cdate, double x, double y, int wcnt, string ws) {
		// ���� : https://cplusplus.com/reference/ctime/mktime/
		// ���� : https://www.it-note.kr/143
		time_t rawtime = time(&rawtime);
		is_valid_date = localtime_s(&comp_date, &rawtime);
		comp_date.tm_year = cdate / 10000 - 1900;
		comp_date.tm_mon = (cdate % 10000) / 100 - 1;
		comp_date.tm_mday = cdate % 100;
		rawtime = mktime(&comp_date);
		
		pic_name = pn;
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

		// print();
	}

	string get_name() { return pic_name; } // ���� �̸� ��ȯ
	time_t get_date() { return rawtime; } // �ο� �Ű� ��¥ ��ȯ
	pair<double, double> get_codi() { return coordinates; } // ���� ��ǥ ��ȯ(pair)
	int get_wcnt() { return waste_cnt; } // ���� ������ ���� �� ��ȯ

	void rename(string new_name) { pic_name = new_name; } // ���� �̸� ����
	void update_wcnt(int num) { waste_cnt += num; } // ���� ������ ���� �� ����
	// �ο� ���� ���
	void print() {
		output << "�ο� ���ϸ� : \"" << pic_name << "\"\n";
		if (is_valid_date == 0) {
			char buffer[256];
			//strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &comp_date);
			strftime(buffer, sizeof(buffer), "%Y-%m-%d", &comp_date);
			output << "�Ű� ���� : " << buffer << "\n";
		}
		else {
			output << "�Ű� ���� : ���� �� ����\n";
		}
		output << "�Ű� ��ǥ : (" << coordinates.first << ", " << coordinates.second << ")\n";
		output << "���� ������ ���� �� : " << waste_cnt << "\n";
		output << "�Ϲ� " << (wastes[0] == 0 ? 'X' : 'O')
			<< "   �ö�ƽ " << (wastes[1] == 0 ? 'X' : 'O')
			<< "   ĵ " << (wastes[2] == 0 ? 'X' : 'O')
			<< "   ���� " << (wastes[3] == 0 ? 'X' : 'O')
			<< "   ���� " << (wastes[4] == 0 ? 'X' : 'O') << "\n\n";
	}
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

bool is_wcnt_zero(complain c) {
	if (c.get_wcnt() == 0)
		return true;
	return false;
}

class compl_system { // ��õ ������ �ο� ó�� �ý���
private:
	pair<int, int> area_code; // ���� �ڵ�(����, �浵 ���� �κ�)
	int thresh; // �ο� ó�� �ּ� ���� : ������ �ο��� ���� �� ������ Ŭ �� ó��. �⺻���� 20
	accumed_compls compls_list[5]; // ������ �з��� ���� �ο� �迭

	vector<complain> all_compls; // ��ü �ο� ����
	multimap<string, complain> map_comp; // ���� �̸� ���� ��ü �ο� ��Ƽ��
	multimap<double, complain> map_latitude; // ���� ���� ��ü �ο� ��Ƽ��
	multimap<double, complain> map_longitude; // �浵 ���� ��ü �ο� ��Ƽ��
	multimap<time_t, complain, greater<time_t>> map_cdate_front; // �ο� ���� ��¥ ����(�ֱټ�) ��ü �ο� ��Ƽ��
	multimap<time_t, complain> map_cdate_back; // �ο� ���� ��¥ ����(�����ȼ�) ��ü �ο� ��Ƽ��
	// �� ��������(greater) ���� : https://0xd00d00.github.io/2021/08/22/map_value_reverse.html

	bool is_same(complain& a, complain& b) {
		if (a.get_name() != b.get_name())
			return false;

		if (a.get_wcnt() != b.get_wcnt())
			return false;

		auto a_codi = a.get_codi();
		auto b_codi = b.get_codi();
		if (a_codi.first != b_codi.first || a_codi.second != b_codi.second)
			return false;

		// ���� : https://torbjorn.tistory.com/357
		if (!equal(a.wastes, a.wastes + 5, b.wastes, b.wastes + 5))
			return false;

		time_t a_raw = a.get_date();
		tm a_tm;
		time_t b_raw = b.get_date();
		tm b_tm;
		errno_t a_val = localtime_s(&a_tm, &a_raw);
		errno_t b_val = localtime_s(&b_tm, &b_raw);
		if (a_tm.tm_year != b_tm.tm_year || a_tm.tm_mon != b_tm.tm_mon || a_tm.tm_mday != b_tm.tm_mday)
			return false;

		return true;
	}

	// ��Ȯ��
	// Ư�� �з��� ������ �ο��� ����� ���� ó���ص� �ɸ����� Ȯ��
	bool is_enough(int waste_code) {
		if (compls_list[waste_code].get_compls_size() >= thresh)
			return true;
		return false;
	}

	void view_all(multimap<string, complain>& mc) {
		output << "���� �̸������� ��� �ο��� ��ȸ�մϴ�.\n";

		char ans = 'Y';
		auto iter = mc.begin();
		int total = 1;
		int mc_len = mc.size();

		output << "�� �ο� �� : " << mc_len << "\n\n";

		while (iter != mc.end() && ans != 'N') {
			int cnt = 1;
			for (iter; iter != mc.end() && cnt < 20; iter++, cnt++, total++) {
				output << total << "/" << mc_len << "\n";
				iter->second.print();
			}

			if (mc_len - total > 0) {
				output << "���� �ο� " << mc_len - total << "��\n";
				output << "�� ���� Y / N\n";
				input >> ans;
			}
			else {
				output << "���� �ο� 0��\n";
				output << "��� �ο��� ��ȸ�Ͽ����ϴ�. ";
				break;
			}
		}

		output << "��ȸ�� �����մϴ�.\n";
	}
	void view_all(multimap<double, complain> ml, int code) {
		if (code == 1) {
			output << "called view latitude map\n";
		}
		else if (code == 2) {
			output << "called view longitude map\n";
		}
		else {
			output << "called view coordinate maps but wrong code\n";
			return;
		}
	}
	void view_all(multimap<time_t, complain, greater<time_t>> mcf) {
		output << "called view cdate front map\n";
	}
	void view_all(multimap<time_t, complain> mcb) {
		output << "called view cdate back map\n";
	}
public:
	compl_system() { area_code = make_pair(NULL, NULL); thresh = 20; } // �⺻ ������
	compl_system(int x, int y) { // ������
		area_code = make_pair(x, y);
		for (int i = 0; i < 5; i++) {
			compls_list[i] = accumed_compls(i);
		}
		thresh = 20;
	}

	pair<int, int> get_acode() { return area_code; }
	void set_thresh(int n) { thresh = n; }

	// ���� ���� Ȯ�ε�
	// �ý��� ���� : ����ڿ��� ���� �ڵ带 �Է¹ް� ���� ������ ���� Ȯ��, �� �α� ���� ��
	void system_on() {
		pair<int, int> acode;
		string file_route;
		bool is_file_valuable;
		char is_load_save;

		output << "��õ ������ �ο� ó�� �ý����� �����մϴ�. ���� ������ ������ �浵 ���� �κ��� �������� �����Ͽ� �Է��� �ּ���.\n";
		input >> acode.first >> acode.second;
		output << "�Էµ� �ڵ�� (" << acode.first << ", " << acode.second << ")�Դϴ�.\n";

		this->area_code = acode;
		file_route = root + "data/" + to_string(acode.first) + "_" + to_string(acode.second) + ".csv";
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
					error(_error::shut_down, "�߸��� �Է�: 'Y' �Ǵ� 'N'�� �Է��� �� �ֽ��ϴ�.");
				}
			}

			if (is_load_save == 'Y') { // ���� ������ �ҷ�����
				this->load_save();
			}
		}
		else if (!is_file_valuable) { // ���� ������ ���� �������� ����
			// �� ���̺� ���� ����� �޼ҵ� ����
			// ���� : https://homzzang.com/b/cpp-34
			ofstream new_save(file_route);
			new_save.close();
			return;
		}

		if (is_file_valuable && is_load_save == 'N') {
			// ���� ������ ���� ���������� ����ڰ� ������ �����͸� �ҷ����� �ʱ�� ����
			// ���̺� ������ ������ �ε��� ���̺갡 �����Ƿ� �޼ҵ� ����.
			return;
		}
	}

	// ���� ���� Ȯ�ε�
	// �ο� ����
	void receive_compl() {
		complain new_comp;
		string word;
		string pn; // ���� �̸�(�ʿ�� ����/��� ���� ��� ����, ���� ũ�⸦ ����� ���� ���� ��ü�� ���� ���� ������ ���� ������ ������ ���Եȴٰ� ����)
		int cdate; // �ο� �Ű� ��¥
		double x, y; // ���� ��ǥ
		int wcnt; // ���Ե� �������� ���� ��
		string ws;
		char ans = 'N';
		string waiting_file_route = root + "data/waiting list.csv";

		while (ans != 'Y') {
			output << "�� �ο��� �Է��մϴ�. �ο���(���ϸ�)�� �Է��� �ּ���.\n";
			input >> pn;

			output << "�ο� �Ű� ��¥�� 8�ڸ� ���ڷ� �Է��� �ּ���.\n";
			input >> word;
			cdate = stoi(word);

			output << "�Ű� ��ġ(����, �浵)�� �������� �����Ͽ� �Է��� �ּ���.\n";
			input >> word;
			x = stod(word);
			input >> word;
			y = stod(word);

			output << "�Ű��� �������� ���� ���� �Է��� �ּ���.\n";
			input >> word;
			wcnt = stoi(word);

			output << "�з��� ������ ���� ���θ� ���� ���� �ټ� �ڸ� ���ڷ� �Է��� �ּ���.\n";
			input >> ws;

			new_comp = complain(pn, cdate, x, y, wcnt, ws);

			output << "�ο� ���� �Է��� �Ϸ�Ǿ����ϴ�. �Է��� ������ �ٽ� Ȯ���� �ּ���.\n\n";
			new_comp.print();

			output << "�� ������ ����Ͻðڽ��ϱ�? Y / N\n";
			input >> ans;
		}

		if (int(x) != this->area_code.first || int(y) != this->area_code.second) {
			output << "�ش� �ο��� ���� ������ ��ġ���� �ʽ��ϴ�. ���� ��� ��Ͽ� �߰��մϴ�.\n";

			// ���� : https://blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=sea5727&logNo=220978963342
			fstream file;
			file.open(waiting_file_route, ios::app);

			file << pn << "," << cdate << "," << x << "," << y << "," << wcnt << ",";
			for (int i = 0; i < 5; i++) {
				file << ws.at(i) << (i < 4 ? "," : "");
			}

			file.close();

			return;
		}

		output << "�ο��� ���� ���Դϴ�...\n";

		this->all_compls.push_back(new_comp);
		this->map_comp.insert(make_pair(new_comp.get_name(), new_comp));
		this->map_latitude.emplace(new_comp.get_codi().first, new_comp);
		this->map_longitude.emplace(new_comp.get_codi().second, new_comp);
		this->map_cdate_front.emplace(new_comp.get_date(), new_comp);
		this->map_cdate_back.emplace(new_comp.get_date(), new_comp);

		for (int i = 0; i < 5; i++) {
			switch (new_comp.wastes[i]) {
			case 0:
				continue;
			default:
				this->compls_list[i].add_compl(&new_comp);
			}
		}

		output << "�ο��� �����Ǿ����ϴ�.\n";

		return;
	}

	// ��Ȯ��
	// ���� ����(sort_by)�� ���� ��ü �ο� ��ȸ(����ϰ� �� ���̹Ƿ� ��ȯ�� ����)
	void view_all() {
		// ������ ���� ���� : ���� �̸� ��������, ���� ��������, �浵 ��������, ���� ��¥ ��������/��������
		// �� ���
		int ans;
		output << "������ ��� �ο��� ��ȸ�մϴ�. ���� ������ ���ڷ� ������ �ּ���.\n1. ���� �̸�\n2. ����\n3. �浵\n4. ���� ���� ��������\n5. ���� ���� ��������\n";
		input >> ans;

		switch (ans) {
		case 1: output << "������ ���� '1. ���� �̸�'�Դϴ�.\n"; view_all(map_comp); break;
		case 2: output << "������ ���� '2. ����'�Դϴ�.\n"; view_all(map_latitude, 1); break;
		case 3: output << "������ ���� '3. �浵'�Դϴ�.\n"; view_all(map_longitude, 2); break;
		case 4: output << "������ ���� '4. ���� ���� ��������'�Դϴ�.\n"; view_all(map_cdate_front); break;
		case 5: output << "������ ���� '5. ���� ���� ��������'�Դϴ�.\n"; view_all(map_cdate_back); break;
		default:
			output << "�߸��� �Է��Դϴ�. ��ȸ�� �����մϴ�.\n";
		}

		return;
	}

	// ��Ȯ��
	// �˻� ����(search_by)�� ���� Ư�� �ο� �˻�
	void search_compl() {
		// ������ �˻� ���� : ���� �̸�(��Ÿ ����), ����, �浵, ���� ��¥
		// ���� ���� �� ��ȸ
		return;
	}

	// ��Ȯ��
	// Ư�� �з��� ������ ���� �ο� �ϰ� ó�� : ó�� �� ��ü �ο� ���ͳ� �ٸ� �� ��� NULL�� �����ϴ� ������ �ʿ���
	void clear_compls(int waste_code) {
		// ���Ϳ��� NULL ����� ���� : https://cho001.tistory.com/164
		output << "ó�� ��û ������ �ڵ� : " << waste_code << "\n";
		if (!is_enough(waste_code)) {
			output << "������ �ο��� ���� �ּ� ó�� �������� �����ϴ�. �׷��� ó���Ͻðڽ��ϱ�? Y / N\n";
			char ans;
			input >> ans;
			if (ans == 'N') {
				output << "�ο��� ó������ �ʽ��ϴ�. ó�� ��û�� �����մϴ�.\n";
				return;
			}
		}

		compls_list[waste_code].clear_compls();

		for (complain& e : all_compls) {
			if (e.get_wcnt() == 0) {
				auto mc = map_comp.find(e.get_name());
				for (mc; mc != map_comp.end(); mc++) {
					if (compl_system::is_same(e, mc->second))
						map_comp.erase(mc);
				}

				auto ml = map_latitude.find(e.get_codi().first);
				for (ml; ml != map_latitude.end(); ml++) {
					if (compl_system::is_same(e, ml->second))
						map_latitude.erase(ml);
				}

				auto ml2 = map_longitude.find(e.get_codi().second);
				for (ml2; ml2 != map_longitude.end(); ml2++) {
					if (compl_system::is_same(e, ml2->second))
						map_latitude.erase(ml2);
				}

				auto mcf = map_cdate_front.find(e.get_date());
				for (mcf; mcf != map_cdate_front.end(); mcf++) {
					if (compl_system::is_same(e, mcf->second))
						map_cdate_front.erase(mcf);
				}

				auto mcb = map_cdate_back.find(e.get_date());
				for (mcb; mcb != map_cdate_front.end(); mcb++) {
					if (compl_system::is_same(e, mcb->second))
						map_cdate_front.erase(mcb);
				}
			}
		}

		// ���� : https://cho001.tistory.com/164
		all_compls.erase(remove_if(all_compls.begin(), all_compls.end(), ::is_wcnt_zero), all_compls.end());

		return;
	}

	// ���� ���� Ȯ��
	// ���Ͽ� ��ϵ� �����͸� ���� ���� ���� ��� �ε�. �Ź� �� �ý����� ������ ���� �����ϱ�.
	void load_save() {
		string file_route = root + "data/" + to_string(int(area_code.first)) + "_" + to_string(int(area_code.second)) + ".csv";
		ifstream data_file{ file_route };

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

			if (line.length() <= 1) {
				break;
			}

			word = istringstream(line);
			
			// ���� : https://myprivatestudy.tistory.com/48
			getline(word, line, ','); // ���� : https://myprivatestudy.tistory.com/48
			pic_name = line;
				
			getline(word, line, ',');
			comp_date = stoi(line);

			getline(word, line, ',');
			coordinates.first = stod(line);
			getline(word, line, ',');
			coordinates.second = stod(line);

			getline(word, line, ',');
			waste_cnt = stoi(line);

			for (int i = 0; i < 5; i++) {
				getline(word, line, ',');
				wastes[i] = stoi(line);
			}

			complain cp{ pic_name, comp_date, coordinates.first, coordinates.second, waste_cnt, wastes };
			this->all_compls.push_back(cp);
			this->map_comp.emplace(cp.get_name(), cp);
			this->map_latitude.emplace(cp.get_codi().first, cp);
			this->map_longitude.emplace(cp.get_codi().second, cp);
			this->map_cdate_front.emplace(cp.get_date(), cp);
			this->map_cdate_back.emplace(cp.get_date(), cp);

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

	// ���� ���� Ȯ��
	// ���� ���� ��Ȳ�� ���Ϸ� ���. ������ �����ϰų� �߰� ������ �ʿ��� �� ����.
	void save_task() {
		string file_route = root + "data/" + to_string(int(area_code.first)) + "_" + to_string(int(area_code.second)) + ".csv";
		ofstream save_file{ file_route };

		// �����̸�,��¥8�ڸ�,����,�浵,�������,�� ������ ����

		output << "���� ����� �����մϴ�...\n";

		for (auto i : all_compls) {
			save_file << i.get_name() << ","; // ���� �̸� ���Ͽ� �Է�

			// �ο� ��¥�� 8�ڸ� ���ڷ� ��ȯ
			time_t date = i.get_date();
			tm date_tm;
			errno_t err = localtime_s(&date_tm, &date);
			char date_cstr[128];
			strftime(date_cstr, sizeof(date_cstr), "%Y%m%d", &date_tm);
			string date_str = date_cstr;
			save_file << date_str << ","; // �ο� ��¥ ���Ͽ� �Է�

			save_file << i.get_codi().first << "," << i.get_codi().second << ","; // ����, �浵 ���Ͽ� �Է�
			save_file << i.get_wcnt() << ","; // ������ �� ���Ͽ� �Է�
			
			for (int j = 0; j < 5; j++)
				save_file << i.wastes[j] << (j < 4 ? "," : "\n");
		}

		save_file.close();

		output << "���� ����� ����Ǿ����ϴ�.\n";
		
		return;
	}
};