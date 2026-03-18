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
	void print_tree(const Node* node) const;
	Node* insert_node(Node* node, int key, bool& inserted);
	bool contains_node(const Node* node, int key) const;
	Node* erase_node(Node* node, int key, bool& erased);
	bool check_strictly_balanced(const Node* node) const;

	Node* balance(Node* node);
	int get_height(const Node* node) const;
	void set_height(Node* node);
	int get_height_difference(const Node* node) const;
	Node* rotate_right(Node* node);
	Node* rotate_left(Node* node);

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

//Insert
bool Set::insert(int key) {
	bool inserted = false;
	root = insert_node(root, key, inserted);
	return inserted;
}

//Contains node
bool Set::contains(int key) const {
	return contains_node(root, key);
}

//Erase node
bool Set::erase(int key) {
	bool erased = false;
	root = erase_node(root, key, erased);
	return erased;
}

//Strictly balanced check
bool Set::strictly_balanced() const {
	return check_strictly_balanced(root);
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

//Print tree
void Set::print_tree(const Node* node) const {
	if (node != nullptr) {
		print_tree(node->left);
		std::cout << node->key << " ";
		print_tree(node->right);
	}
}

//Insert node
Set::Node* Set::insert_node(Node* node, int key, bool& inserted) {
	if (node == nullptr) {
		inserted = true;
		return new Node(key);
	}
	if (key < node->key) {
		node->left = insert_node(node->left, key, inserted);
	}
	else if (key > node->key) {
		node->right = insert_node(node->right, key, inserted);
	}
	else {
		inserted = false;
		return node;
	}
	return balance(node);
}

//Check if contain node
bool Set::contains_node(const Node* node, int key) const {
	if (node == nullptr) return false;
	if (node->key == key) return true;
	if (node->key > key) return contains_node(node->left, key);
	return contains_node(node->right, key);
}

//Erase node
Set::Node* Set::erase_node(Node* node, int key, bool& erased) {
	// TODO
}

//Check if strictly balanced
bool Set::check_strictly_balanced(const Node* node) const {
	if (node == nullptr) {
		return true;
	}

	int diff = get_height_difference(node);
	if (diff < -1 || diff > 1) return false;

	return check_strictly_balanced(node->left) && check_strictly_balanced(node->right);
}

//Balance tree after adding new node
Set::Node* Set::balance(Node* node) {
	set_height(node);
	if (get_height_difference(node) == 2) {
		if (get_height_difference(node->right) < 0) {
			node->right = rotate_right(node->right); //Big left rotation
		}
		return rotate_left(node); //Small left rotation
	}
	if (get_height_difference(node) == -2) {
		if (get_height_difference(node->left) > 0) {
			node->left = rotate_left(node->left); //Big right rotation
		}
		return rotate_right(node); //Small right rotation
	}
	return node;
}

//Get height
int Set::get_height(const Node* node) const {
	if (node != nullptr) {
		return node->height;
	}
	return 0;
}

//Set height
void Set::set_height(Node* node) {
	int height_left = get_height(node->left);
	int height_right = get_height(node->right);
	node->height = (height_left > height_right ? height_left : height_right) + 1;
}

//Get height difference for balance
int Set::get_height_difference(const Node* node) const {
	return get_height(node->right) - get_height(node->left);
}

//Small right rotation
Set::Node* Set::rotate_right(Node* node) {
	Node* q = node->left;
	node->left = q->right;
	q->right = node;
	set_height(node);
	set_height(q);
	return q;
}

//Small left rotation
Set::Node* Set::rotate_left(Node* node) {
	Node* q = node->right;
	node->right = q->left;
	q->left = node;
	set_height(node);
	set_height(q);
	return q;
}

#endif // !SET_H
