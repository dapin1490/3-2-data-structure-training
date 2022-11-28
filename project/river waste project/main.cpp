#include <iostream>
//#include <vector> // vector
//#include <utility> // pair
//#include <algorithm> // copy, sort(����)
//#include <map> // multimap ���� : https://blockdmask.tistory.com/88
//#include <io.h> // ���� ���� Ȯ�� ���� : https://tw0226.tistory.com/121
//#include <string> // to_string
#include <ctime>
#include "compl_system.h"
using namespace std;

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

int main() {
	// ���� �����
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	// �ڵ� ���� �ð� ���� : https://scarlettb.tistory.com/5
	clock_t clock_start, clock_finish;
	double clock_duration;

	output << "main.cpp ���� �ð� : " << currentDateTime() << "\n\n";

	clock_start = clock();

	//// ���� : https://cplusplus.com/reference/ctime/mktime/
	//time_t rawtime = time(&rawtime);
	//tm sometime;
	//errno_t is_error = localtime_s(&sometime, &rawtime);
	//sometime.tm_year = 2021 - 1900;
	//sometime.tm_mon = 10 - 1;
	//sometime.tm_mday = 11;
	//mktime(&sometime);
	//if (is_error == 0) {
	//	char buffer[256];
	//	strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &sometime);
	//	output << buffer << "\n\n";
	//}

	compl_system system;
	system.system_on(); // ���� ���� Ȯ����

	system.receive_compl(); // ���� ���� Ȯ����

	// system.save_task(); // ���� ���� Ȯ����, ���� �� ������ ������ ����Ǳ� ������ �ּ� ó��

	system.view_all(); // ���� ���� Ȯ����
	system.view_all(); // ���� ���� Ȯ����
	system.view_all(); // ���� ���� Ȯ����
	system.view_all(); // ���� ���� Ȯ����
	system.view_all(); // ���� ���� Ȯ����

	system.clear_compls(); // �ڵ� 1 : ���� �ο� ����, ó�� ���� �̴�, ���� ó��
	system.clear_compls(); // �ڵ� 3 : ���� �ο� ����, ���� ó�� �׽�Ʈ

	system.view_all();

	clock_finish = clock();

	// clock_duration = (double)(clock_finish - clock_start) / CLOCKS_PER_SEC; // �� ������ ȯ��
	clock_duration = (double)(clock_finish - clock_start);
	output << "\n���α׷� ���� �ð� : " << clock_duration << "ms\n";

	input.close();
	output.close();

	return 0;
}