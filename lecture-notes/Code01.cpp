/*
자료구조 실습 1강 예시 코드
* Source:  코딩  테스트를  위한  자료  구조와  알고리즘  with C++
*/

#include <iostream>
#include <queue>
using namespace std;

class Job {
	int id;
	string user;
	int pages;

	static int count;

public:
	Job(const string& u, int p) : user(u), pages(p), id(++count) {}
	
	friend ostream& operator<<(ostream& os, const Job& j) {
		os << "id: " << j.id << ", 사용자: " << j.user << ", 페이지수: " << j.pages << "장";
		return os;
	}
};

int Job::count = 0;

template <size_t N>
class Printer {
	queue<Job> jobs;

public:
	bool addNewJob(const Job& job) {
		if (jobs.size() == N) {
		cout << "인쇄 대기열에 추가 실패: " << job << endl;
		return false;
		}
		cout << "인쇄 대기열에 추가: " << job << endl;
		jobs.push(job);
		return true;
	}

	void startPrinting() {
		while (not jobs.empty()) {
		cout << "인쇄 중: " << jobs.front() << endl;
		jobs.pop();
		}
	}
};

int main() {
	Printer<2> printer;

	Job j1("성신", 10);
	Job j2("수정", 4);
	Job j3("자료", 5);
	Job j4("구조", 7);

	printer.addNewJob(j1);
	printer.addNewJob(j2);
	printer.addNewJob(j3);
	printer.addNewJob(j4);
	printer.startPrinting();

	printer.addNewJob(j3); 
	printer.addNewJob(j4);
	printer.startPrinting();
}