#ifndef SET_H
#define SET_H

#include <iostream>

class Set {
private:
	struct Node {
		int key;
		Node* left;
		Node* right;
		int height;

		Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
	};

	Node* root;

	void delete_tree(Node* node);
	Node* copy_tree(const Node* node);
	void print_tree(const Node* node) const; //const

public:
	Set();
	~Set();
	Set(const Set& src);
	Set& operator=(const Set& src);
	void print() const;
	bool insert(int key);
	bool contains(int key) const;
	bool erase(int key);
	bool strictly_balanced() const;
};

//Constructor
Set::Set() : root(nullptr) {}

//Destructor
Set::~Set() {
	delete_tree(root);
}

//Copy constructor
Set::Set(const Set& src) {
	root = copy_tree(src.root);
}

//Assigment operator
Set& Set::operator=(const Set& src) {
	if (this == &src) {
		return *this;
	}
	delete_tree(root);
	root = copy_tree(src.root);
	return *this;
}

//Print tree
void Set::print() const {
	print_tree(root);
	std::cout << "\n";
}

//Insert node
bool Set::insert(int key) {
	//TODO
}

//Contains node
bool Set::contains(int key) const {
	//TODO
}

//Erase node
bool Set::erase(int key) {
	//TODO
}

//Strictly balanced check
bool Set::strictly_balanced() const {
	//TODO
}

//Delete tree
void Set::delete_tree(Node* node) {
	if (node != nullptr) {
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}

//Copy tree
Set::Node* Set::copy_tree(const Node* node) {
	if (node == nullptr) return nullptr;
	Node* new_node = new Node(node->key);
	new_node->height = node->height;
	new_node->left = copy_tree(node->left);
	new_node->right = copy_tree(node->right);
	return new_node;
}

void Set::print_tree(const Node* node) const {
	if (node != nullptr) {
		print_tree(node->left);
		std::cout << node->key << " ";
		print_tree(node->right);
	}
}

#endif // !SET_H
