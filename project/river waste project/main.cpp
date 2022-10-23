#include <iostream>
#include <vector> // vector
#include <utility> // pair
#include <algorithm> // copy
using namespace std;

class accumulate_node { // ���� �ο� ��� Ŭ����
private:
	int waste_number; // ������ �з� ��ȣ
	int accmed_compls; // ���� �ο� ��
	vector<complain_node> compl_list; // �ش� �ο� ����

public:
	/* �����ڴ� ���α׷� ù ���� �� ������� ���� ���� �ڵ����� ������ ����ŭ ����ǰ� �� ��.
	�ο��� �ϳ��� ������ ���� ���¸� ������ �Ѵ�. */
	accumulate_node(int wn) {
		waste_number = wn;
		accmed_compls = 0;
	}
	/*
	�ʿ� �޼ҵ�
	+ ���� �ο� �� ���� �޼ҵ�
	+ ������ �з� ��ȣ ��ȯ �޼ҵ�
	+ ���� �ο� �� ��ȯ �޼ҵ�
	+ �ο� ���� ��ȯ �޼ҵ�
	*/
};

class complain_node { // �ο� ��� Ŭ����
private:
	string pic_name; // ���� ���ϸ�
	pair<int, int> pic_size; // ���� ũ��
	pair<double, double> coordinates; // ��ǥ
	int wastes[5]; // ������ ���� ǥ��

public:
	complain_node(string pn, int width, int height, double x, double y, int ws[5]) {
		pic_name = pn;
		pic_size = make_pair(width, height);
		coordinates = make_pair(x, y);
		copy(ws, ws + 5, wastes); // �迭 ���� ���� : https://terrorjang.tistory.com/98
	}

	/*
	�ʿ� �޼ҵ�
	+ �� ��� ������ ���� ��ȯ�ϴ� �޼ҵ��
	+ ������ ���� �迭 ���� �޼ҵ�
	*/
};

int main() {
	// ���� �����
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	return 0;
}