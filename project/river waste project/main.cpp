#include <iostream>
//#include <vector> // vector
//#include <utility> // pair
//#include <algorithm> // copy, sort(예정)
//#include <map> // multimap 참고 : https://blockdmask.tistory.com/88
//#include <io.h> // 파일 존재 확인 참고 : https://tw0226.tistory.com/121
//#include <string> // to_string
#include <ctime>
#include "compl_system.h"
using namespace std;

//string currentDateTime() {
//	time_t t = time(nullptr);
//	tm now;
//	errno_t is_error = localtime_s(&now, &t);
//
//	if (is_error == 0) {
//		char buffer[256];
//		strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &now);
//		return buffer;
//	}
//	else {
//		return "현재 시간을 얻을 수 없음";
//	}
//}

int main() {
	// 빠른 입출력
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	output << "main.cpp 실행 시각 : " << currentDateTime() << "\n\n";

	//// 참고 : https://cplusplus.com/reference/ctime/mktime/
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
	system.system_on();

	input.close();
	output.close();
	return 0;
}