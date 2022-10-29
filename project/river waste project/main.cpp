#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy, sort(����)
#include <map> // multimap ���� : https://blockdmask.tistory.com/88
using namespace std;

class complain { // �ο� Ŭ����
private:
	string pic_name; // ���� �̸�(�ʿ�� ����/��� ���� ��� ����, ���� ũ�⸦ ����� ���� ���� ��ü�� ���� ���� ������ ���� ������ ������ ���Եȴٰ� ����)
	int comp_date; // �ο� �Ű� ��¥
	pair<double, double> coordinates; // ���� ��ǥ
	int waste_cnt; // ���Ե� �������� ���� ��

public:
	int wastes[5]; // ��� �������� ������ getter�� �ᵵ �����ͷ� ���޵Ǿ� ���� ������ �����ϴ� public ������ ���

	complain(string pn, int cdate, double x, double y, int wcnt, int* ws);
	complain(string pn, int cdate, double x, double y, int wcnt, string ws);

	string get_name() { return pic_name; }
	int get_date() { return comp_date; }
	pair<double, double> get_codi() { return coordinates; }
	int get_wcnt() { return waste_cnt; }

	void rename(string new_name) { pic_name = new_name; } // ���� �̸� ����
	void update_wcnt(int num) { waste_cnt += num; }
	void print_date() { cout << comp_date / 10000 << "�� " << comp_date % 10000 / 100 << "�� " << comp_date % 100 << "��\n"; }
};

class accumed_compls { // ���� �ο� Ŭ����
private:
	int waste_code; // ������ �з� ��ȣ
	vector<complain> compls; // ������ �з� ��ȣ�� ���� �ش� ������ ���� �ο� ����
public:
	accumed_compls() {};
	accumed_compls(int wn); // ������

	int get_num() { return waste_code; } // ������ �з� ��ȣ ��ȯ
	int get_compls_size() { return compls.size(); } // �ο� ��� ���� ����(���� �ο� ��) ��ȯ

	void add_compl(complain new_comp) { compls.push_back(new_comp); } // �ο� �߰�
	void clear_compls(); // �ο� ó��(���� �ο� ���͸� clear�ϸ�, ���� �ο� �� 2���� �̻��� �����Ⱑ ���Ե� �ο��� ��� ������ ���� ǥ�⸦ ������ �� clear�ؾ� �Ѵ�.)
};

class compl_system { // ��õ ������ �ο� ó�� �ý���
private:
	int area_code; // ���� �ڵ�(������/������ ���)
	accumed_compls compls_list[5]; // ������ �з��� ���� �ο� �迭
	
	vector<complain> all_compls; // ��ü �ο� ����
	multimap<string, complain> comp_map; // ���� �̸� ���� ��ü �ο� ��Ƽ��
	multimap<double, complain> longitude_map; // �浵 ���� ��ü �ο� ��Ƽ��
	multimap<double, complain> latitude_map; // ���� ���� ��ü �ο� ��Ƽ��
	multimap<int, complain> cdate_map; // �ο� ���� ��¥ ���� ��ü �ο� ��Ƽ��
public:
	compl_system(int area); // ������
	void receive_compl(); // �ο� ����
	
	void view_all(); // ���� ����(sort_by)�� ���� ��ü �ο� ��ȸ(����ϰ� �� ���̹Ƿ� ��ȯ�� ����)
	void search_compl(); // �˻� ����(search_by)�� ���� Ư�� �ο� �˻�
	
	bool is_enough(int waste_code); // Ư�� �з��� ������ �ο��� ����� ���� ó���ص� �ɸ����� Ȯ��
	void clear_compls(int waste_code); // Ư�� �з��� ������ ���� �ο� �ϰ� ó��
	
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
		defalut:
			wastes[i] = NULL;
		}
	}
}

accumed_compls::accumed_compls(int wn) {
	waste_code = wn;
}

void accumed_compls::clear_compls() { // �ο� ó��(���� �ο� ���͸� clear�ϸ�, ���� �ο� �� 2���� �̻��� �����Ⱑ ���Ե� �ο��� ��� ������ ���� ǥ�⸦ ������ �� clear�ؾ� �Ѵ�.)
	vector<complain>::iterator i;

	for (i = compls.begin(); i != compls.end(); i++) {
		if ((*i).get_wcnt() > 1) {
			(*i).update_wcnt(-1);
			(*i).wastes[waste_code] = 0;
		}
	}

	compls.clear();
}

compl_system::compl_system(int area) {
	area_code = area;
	for (int i = 0; i < 5; i++) {
		compls_list[i] = accumed_compls(i);
	}
}
