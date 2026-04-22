#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename T>
class HashTable {
private:
	enum Status { EMPTY, OCCUPIED, DELETED };

	struct Node {
		int key;
		T value;
		Status status;

		Node() : key(0), status(EMPTY) {}
	};

	Node* table;
	int table_capacity;
	int table_size;
	int l;
	unsigned int a;

	int hash_function(int key) const;
public:
	HashTable(int size);
	HashTable(int size, bool random);
	HashTable(const HashTable& src);
	~HashTable();
};

template <typename T>
int HashTable<T>::hash_function(int key) const {
	unsigned int k = static_cast<unsigned int>(key);
	return static_cast<int>((k * a) >> (32 - l));
}

template <typename T>
HashTable<T>::HashTable(int size) {

}

template <typename T>
HashTable<T>::HashTable(int size, bool random) {

}

template <typename T>
HashTable<T>::HashTable(const HashTable& src) {

}

template <typename T>
HashTable<T>::~HashTable() {
	delete[] table;
}

#endif