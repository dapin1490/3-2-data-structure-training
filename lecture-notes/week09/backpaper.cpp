#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include <ctime>
#include "BFS_DFS.h"
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
		return "현재 시간을 얻을 수 없음";
	}
}

int main()
{
	// 빠른 입출력
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int g_size;
	input_file >> g_size;
	Graph grp(g_size);
	vector<int> stations;

	output_file << "실행 시간 : " << currentDateTime() << "\n\n";

	while (!input_file.eof()) {
		int a, b;
		input_file >> a >> b;
		grp.add_undir_edge(a, b);
	}
	
	grp.BFS(0);
	
	grp.BFS(3);
	
	stations = { 0, 3 };
	grp.BFS(stations);

	stations = { 0, 3, 8 };
	grp.BFS(stations);

	grp.DFS_by_iteration(0);

	grp.DFS_by_iteration(3);

	stations = { 0, 3 };
	grp.DFS_by_iteration(stations);

	stations = { 0, 3, 8 };
	grp.DFS_by_iteration(stations);

	grp.DFS_by_recursion(0);

	stations = { 0, 3 };
	grp.DFS_by_recursion(stations);

	stations = { 0, 3, 8 };
	grp.DFS_by_recursion(stations);
	
	input_file.close();
	output_file.close();
	return 0;
}