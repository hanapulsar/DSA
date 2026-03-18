#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>

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
	Node* find_min(Node* node) const;
	Node* remove_min(Node* node);
	bool check_strictly_balanced(const Node* node) const;

	Node* balance(Node* node);
	int get_height(const Node* node) const;
	void set_height(Node* node);
	int get_height_difference(const Node* node) const;
	Node* rotate_right(Node* node);
	Node* rotate_left(Node* node);

	void tree_to_vector(const Node* node, std::vector<int>& vec) const;

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
	std::vector<int> to_vector() const;
};

Set::Set() : root(nullptr) {}

Set::~Set() {
	delete_tree(root);
}

Set::Set(const Set& src) {
	root = copy_tree(src.root);
}

Set& Set::operator=(const Set& src) {
	if (this == &src) {
		return *this;
	}
	delete_tree(root);
	root = copy_tree(src.root);
	return *this;
}

void Set::print() const {
	print_tree(root);
	std::cout << "\n";
}

bool Set::insert(int key) {
	bool inserted = false;
	root = insert_node(root, key, inserted);
	return inserted;
}

bool Set::contains(int key) const {
	return contains_node(root, key);
}

bool Set::erase(int key) {
	bool erased = false;
	root = erase_node(root, key, erased);
	return erased;
}

bool Set::strictly_balanced() const {
	return check_strictly_balanced(root);
}

void Set::delete_tree(Node* node) {
	if (node != nullptr) {
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}

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

bool Set::contains_node(const Node* node, int key) const {
	if (node == nullptr) return false;
	if (node->key == key) return true;
	if (node->key > key) return contains_node(node->left, key);
	return contains_node(node->right, key);
}

Set::Node* Set::erase_node(Node* node, int key, bool& erased) {
	if (node == nullptr) {
		erased = false;
		return nullptr;
	}

	if (key < node->key) {
		node->left = erase_node(node->left, key, erased);
	}
	else if (key > node->key) {
		node->right = erase_node(node->right, key, erased);
	}
	else {
		erased = true;
		Node* left_node = node->left;
		Node* right_node = node->right;

		delete node;

		if (right_node == nullptr) {
			return left_node;
		}

		Node* min_node = find_min(right_node);
		min_node->right = remove_min(right_node);
		min_node->left = left_node; 

		return balance(min_node);
	}

	return balance(node);
}

Set::Node* Set::find_min(Node* node) const {
	if (node->left != nullptr) {
		return find_min(node->left);
	}
	return node;
}

Set::Node* Set::remove_min(Node* node) {
	if (node->left == nullptr) return node->right;
	node->left = remove_min(node->left);
	return balance(node);
}

bool Set::check_strictly_balanced(const Node* node) const {
	if (node == nullptr) {
		return true;
	}

	int diff = get_height_difference(node);
	if (diff < -1 || diff > 1) return false;

	return check_strictly_balanced(node->left) && check_strictly_balanced(node->right);
}

Set::Node* Set::balance(Node* node) {
	set_height(node);
	if (get_height_difference(node) == 2) {
		if (get_height_difference(node->right) < 0) {
			node->right = rotate_right(node->right);
		}
		return rotate_left(node);
	}
	if (get_height_difference(node) == -2) {
		if (get_height_difference(node->left) > 0) {
			node->left = rotate_left(node->left);
		}
		return rotate_right(node);
	}
	return node;
}

int Set::get_height(const Node* node) const {
	if (node != nullptr) {
		return node->height;
	}
	return 0;
}

void Set::set_height(Node* node) {
	int height_left = get_height(node->left);
	int height_right = get_height(node->right);
	node->height = (height_left > height_right ? height_left : height_right) + 1;
}

int Set::get_height_difference(const Node* node) const {
	return get_height(node->right) - get_height(node->left);
}

Set::Node* Set::rotate_right(Node* node) {
	Node* q = node->left;
	node->left = q->right;
	q->right = node;
	set_height(node);
	set_height(q);
	return q;
}

Set::Node* Set::rotate_left(Node* node) {
	Node* q = node->right;
	node->right = q->left;
	q->left = node;
	set_height(node);
	set_height(q);
	return q;
}

std::vector<int> Set::to_vector() const {
	std::vector<int> vec;
	tree_to_vector(root, vec);
	return vec;
}

void Set::tree_to_vector(const Node* node, std::vector<int>& vec) const {
	if (node != nullptr) {
		tree_to_vector(node->left, vec);
		vec.push_back(node->key);
		tree_to_vector(node->right, vec);
	}
}

#endif // !SET_H
