#include <iostream>
using namespace std;

class node
{
public:
	int data;
	node *left;
	node *right;
};
class bst
{
private:
	node *find_impl(node *current, int value)
	{
		if (!current)
		{
			cout << endl;
			return NULL;
		}
		if (current->data == value)
		{
			cout << value << "has been found." << endl;
			return current;
		}
		if (value < current->data)
		{
			cout << current->data << "moved to left.";
			return find_impl(current->left, value);
		}
		cout << current->data << "moved to right.";
		return find_impl(current->right, value);
	}
	void insert_impl(node *current, int value)
	{
		if (value < current->data)
		{
			if (!current->left)
				current->left = new node{value, NULL, NULL};
			else
				insert_impl(current->left, value);
		}
		else
		{
			if (!current->right)
				current->right = new node{value, NULL, NULL};
			else
				insert_impl(current->right, value);
		}
	}
	void inorder_impl(node *start)
	{
		if (!start)
			return;
		inorder_impl(start->left);
		cout << start->data << " ";
		inorder_impl(start->right);
	}
	node *delete_impl(node *start, int value)
	{
		if (!start)
			return NULL;
		if (value < start->data)
			start->left = delete_impl(start->left, value);
		else if (value > start->data)
			start->right = delete_impl(start->right, value);
		else
		{
			if (!start->left)
			{
				auto tmp = start->right;
				delete start;
				return tmp;
			}
			if (!start->right)
			{
				auto tmp = start->left;
				delete start;
				return tmp;
			}
			auto succNode = successor(start);
			start->data = succNode->data;
			start->right = delete_impl(start->right, succNode->data);
		}
		return start;
	}

public:
	node *root = nullptr;
	node *find(int value)
	{
		return find_impl(root, value);
	}
	void insert(int value)
	{
		if (!root)
			root = new node{value, NULL, NULL};
		else
			insert_impl(root, value);
	}
	void inorder()
	{
		inorder_impl(root);
	}
	node *successor(node *start)
	{
		auto current = start->right;
		while (current && current->left)
			current = current->left;
		return current;
	}
	void deleteValue(int value)
	{
		root = delete_impl(root, value);
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

	cout << "Inorder Traversal: ";
	tree.inorder();
	cout << endl;

	tree.deleteValue(12);
	cout << "Delete 12 and Do Inorder Traversal: ";
	tree.inorder();
	cout << endl;

	if (tree.find(12))
		cout << "Value 12 is in the tree." << endl;
	else
		cout << "Value 12 is not in the tree. " << endl;
}