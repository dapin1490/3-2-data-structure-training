#include <iostream>
#include <queue>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;
void MaxHeapSorting(int a[], int n) {  // C++�� ���� Ǯ� �ڷᱸ��
	priority_queue <int> maxHeap;
	for (int i = 0; i < n; ++i)
		maxHeap.push(a[i]);
	for (int i = 0; i < n; i++) {
		a[i] = maxHeap.top();
		maxHeap.pop();
	}
}
void MinHeapSorting(int a[], int n) {  // C++�� ���� Ǯ� �ڷᱸ��
	priority_queue<int, vector<int>, greater<int>>minHeap; 
	for (int i = 0; i < n; ++i)
		minHeap.push(a[i]);
	for (int i = 0; i < n; ++i) {
		a[i] = minHeap.top();
		minHeap.pop();
	}
}

int main() {
	/*
	1. pair class
	���� �ٸ� ������ �� ��ü�� ���� �ϳ��� ��ü�� ����ϴ�.
	���: utility
	����: pair<[type 1], [type 2]> ��ü�̸�
	����
	make_pair(variable 1, variable 2): variable 1, 2�� pair ����
	p.first: p ��ü ù��° ���� ��ȯ
	p.second: p ��ü �ι�° ���� ��ȯ
	������ ����� �����մϴ�.
	�켱����ť�� ��� ��, p.first�� key�� �Ǹ�, ��� key���� ������ �� p.second�� key�� �ȴ�.
	2. tuple class
	pair�� �� ��ü���, tuple�� �� ��ü�� �ϳ��� ��ü�� ����ϴ�.
	���: tuple
	����
	tuple<[type 1], [type 2], [type 3]> ��ü�̸�(��1, ��2, ��3);
	������ ����� �����մϴ�.
	3. vector
	C++���� �����ϴ� �����̳�(�ڷᱸ��) �� �ϳ��� ���� �迭
	���� �迭�� �������� ���� �ſ� ���� ���̴� Ŭ�����Դϴ�.
	���: vector
	����
	vector<[type]> ��ü�̸�; eg. vector<int> vec;
	vec.push_back(5);
	vec.pop_back();
	*/

	// C++�� �켱����ť�� �⺻������ Max heap�� ����մϴ�.
	// Min heap�� ���� ��� greater��� Ű���带 ����� �����մϴ�.
	// ����(���� �ڵ��� 17�� MinHeapSorting �Լ�)�� �����ϼ���.
	
	// �Ʒ��� ������ pair�� �̿��� �켱���� ť ��������Դϴ�.
	// key ���� �����͸� �����ؼ� ����ϴ� ��찡 ���� ������, pair�� �켱���� ť ������ ���� ����մϴ�.
	// �� �ͼ��� ������.
	priority_queue<pair<int, string>> temp_data;// ���ϴ� �ڷ����� ���� �켱����ť�� ���¸� ����ϴ�.
	temp_data.push({1, "ù��° �մ�"});			// �켱����ť�� ù��° �����͸� �ֽ��ϴ�.
	temp_data.push({ 2, "�ι�° �մ�" });		// �ι�° �����͸� �ֽ��ϴ�.
	cout << temp_data.top().first << endl;		// �̷� �ð��� ��������, ���� root�� ����ϴ� �ڷᱸ���Դϴ�. ù ���(key ��)�� Ȯ���մϴ�.
	cout << temp_data.top().second << endl;		// �ι�° ��Ҹ� Ȯ���մϴ�.
	temp_data.pop();							// Root�� ��ȯ(������ ����)�մϴ�.

	// �ڵ� �Ƿ��� ����Ϸ��� ����� �ϸ� ��� ���� �����Ǵ��� Ȯ���ؾ� �մϴ�.
	// ���� �ð��� ��� �Բ� �� ��������, �� ���� �غ��� ��õ�մϴ�.
	return 0;
}