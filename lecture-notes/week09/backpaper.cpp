#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <stack>
#include <ctime>
#include "..\..\..\github desktop\3-2-data-structure-training\lecture-notes\week09\BFS_DFS.h"
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

	int g_size, line_num;
	int dst;

	input >> g_size >> line_num;
	Graph grp(g_size);
	vector<int> stations;

	output << "실행 시간 : " << currentDateTime() << "\n\n";

	output << "Graph 탐색 시작\n\n";

	for (int i = 0; i < line_num; i++) {
		int a, b;
		input >> a >> b;
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

	grp.DFS_to_destination(0, 8);

	output << "Graph 탐색 끝\n\nCity 탐색 시작\n\n";

	input >> g_size >> line_num;
	Graph cities(g_size);

	for (int i = 0; i < line_num; i++) {
		string city1, city2;
		input >> city1 >> city2 >> dst;
		cities.add_undir_edge(city1, city2, dst);
	}

	output << "CITY CODE LIST\n";
	for (map<string, int>::iterator i = city_code.begin(); i != city_code.end(); i++) {
		output << i->first << " : " << i->second << "\n";
	}
	output << "\n";

	cities.BFS(0);

	cities.DFS_by_iteration(0);

	cities.DFS_to_destination(0, 4);

	cities.DFS_by_recursion(0);
	
	input.close();
	output.close();
	return 0;
}