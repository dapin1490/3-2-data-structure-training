#include <iostream>
#include <string>
using namespace std;

class node {
public:
	int data;
	node* left;
	node* right;
};

class bst {
private:
	node* find_impl(node* current, int value) { // private 탐색 메소드
		if (!current) { // 현재 탐색하는 노드가 NULL인 경우
			cout << "No matching value found for " << value << ".\n";
			return NULL;
		}

		if (current->data == value) { // 원하는 값 찾음
			cout << value << " has been found.\n";
			return current;
		}

		if (value < current->data) { // 원하는 값이 더 작음
			cout << "current is " << current->data << ". pointer moved to left.\n";
			return find_impl(current->left, value); // 왼쪽 서브트리로 이동
		}

		// 위의 모든 선택문을 패스했다면 원하는 값이 더 큰 경우임
		cout << "current is " << current->data << ". pointer moved to right.\n";
		return find_impl(current->right, value); // 오른쪽 서브트리로 이동
	}

	void insert_impl(node* current, int value) { // private 삽입 메소드
		if (value < current->data) { // 삽입할 값이 현재 탐색하는 노드보다 작음
			if (!current->left) { // 왼쪽 서브트리 없음
				current->left = new node{ value, NULL, NULL }; // 바로 붙임
				cout << "current is " << current->data << ", " << value << " is inserted left\n";
			}
			else // 왼쪽 서브트리 있음
				insert_impl(current->left, value); // 왼쪽 서브트리에 삽입 메소드 다시 호출
		}
		else { // else: 삽입할 값이 현재 탐색하는 노드보다 크거나 같음
			if (!current->right) { // 오른쪽 서브트리 없음
				current->right = new node{ value, NULL, NULL }; // 바로 붙임
				cout << "current is " << current->data << ", " << value << " is inserted right\n";
			}
			else // else: 오른쪽 서브트리 있음
				insert_impl(current->right, value); //오른쪽 서브트리에 삽입 메소드 다시 호출
		}
	}

	void inorder_impl(node* start) { // private 중위순회(LDR) 메소드
		if (!start) // 현재 탐색중인 노드가 NULL
			return; // 돌아감

		inorder_impl(start->left); // L: 왼쪽 서브트리 순회 호출
		cout << start->data << " "; // D: 현재 노드 데이터 출력
		inorder_impl(start->right); // R: 오른쪽 서브트리 순회 호출
	}

	node* delete_impl(node* start, int value) { // private 특정 값 삭제 메소드
		cout << "current node is " << (start ? to_string(start->data) : "NULL") << ".\n";

		if (!start) { // 현재 노드가 NULL
			cout << "No value matches " << value << ".\n";
			return NULL; // 삭제한 노드 없음, NULL 반환
		}

		if (value < start->data) // 삭제할 값이 현재 노드보다 작음
			start->left = delete_impl(start->left, value); // 왼쪽 서브트리에 삭제 메소드 다시 호출
		else if (value > start->data) // else if: 삭제할 값이 현재 노드보다 큼
			start->right = delete_impl(start->right, value); // 오른쪽 서브트리에 삭제 메소드 다시 호출
		else { // else: 삭제할 값이 현재 노드와 같음
			if (!start->left) { // 왼쪽 서브트리가 없음
				cout << "there is no left subtree. bring the right subtree.\n";
				auto tmp = start->right; // 현재 노드의 오른쪽 서브트리를 가져옴
				cout << "delete " << value << ".\n";
				delete start; // 현재 노드를 지움
				return tmp; // 아까 가져온 오른쪽 서브트리 반환
			}

			if (!start->right) { // 오른쪽 서브트리가 없음
				cout << "there is no right subtree. bring the left subtree.\n";
				auto tmp = start->left; // 현재 노드의 왼쪽 서브트리 가져옴
				cout << "delete " << value << ".\n";
				delete start; // 현재 노드를 지움
				return tmp; // 아까 가져온 왼쪽 서브트리 반환
			}

			cout << "there are both subtrees. need successor.\n";
			auto succNode = successor(start); // 후계자 반환 메소드 호출
			start->data = succNode->data; // 현재 노드의 값을 후계자의 값으로 대체
			start->right = delete_impl(start->right, succNode->data); // 아까 가져온 후계자의 원래 노드 삭제
		}

		return start;
	}

public:
	node* root = nullptr;

	node* find(int value) { // 특정 값 탐색 메소드
		return find_impl(root, value); // 따로 구현된 private 탐색 메소드 호출
	}

	void insert(int value) { // 삽입 메소드
		if (!root) { // 루트가 비어있다면
			root = new node{ value, NULL, NULL }; // 로트에 바로 넣음
			cout << value << " is inserted into root\n";
		}
		else // else: 루트가 비어있지 않다면
			insert_impl(root, value); // 따로 구현된 private 삽입 메소드 호출
	}

	void inorder() { // 중위순회 메소드
		inorder_impl(root); // 호출
	}

	node* successor(node* start) { // 후계자 반환 메소드
		auto current = start->right; // 현재 노드의 오른쪽 서브트리 가져옴

		while (current && current->left) // 지금 갖고있는 노드와 그 노드의 왼쪽 서브트리가 모두 존재하는 동안 반복
			current = current->left; // 왼쪽 서브트리로 이동

		cout << "successor is " << (current ? to_string(current->data) : "NULL") << ".\n";
		return current; // 결과: 오른쪽 서브트리 왼쪽 맨 아래 리프노드 반환
	}

	void deleteValue(int value) { // 특정 값 삭제
		root = delete_impl(root, value); // 호출
	}
};

int main()
{
	bst tree;

	tree.insert(12);
	tree.insert(10);
	tree.insert(20);
	tree.insert(8);
	tree.insert(11);
	tree.insert(11);
	tree.insert(15);
	tree.insert(28);
	tree.insert(4);
	tree.insert(2);
	tree.insert(27);

	cout << "Inorder Traversal: ";
	tree.inorder();
	cout << "\n";

	tree.deleteValue(12);
	cout << "Delete 12 and Do Inorder Traversal: ";
	tree.inorder();
	cout << "\n";

	if (tree.find(12))
		cout << "Value 12 is in the tree.\n";
	else
		cout << "Value 12 is not in the tree.\n";

	tree.deleteValue(11);
	tree.deleteValue(4);
	tree.deleteValue(0);
	tree.inorder();
}
