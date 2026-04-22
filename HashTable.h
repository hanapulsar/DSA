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
	int calculate_l(int size);
	int calculate_capacity(int power);
	int lcg();
public:
	HashTable(int size);
	HashTable(int size, bool random);
	HashTable(const HashTable& src);
	~HashTable();
	HashTable& operator=(const HashTable& src);
	void HashTable<T>::print() const;
};

template <typename T>
int HashTable<T>::hash_function(int key) const {
	unsigned int k = static_cast<unsigned int>(key);
	return static_cast<int>((k * a) >> (32 - l));
}

template <typename T>
int HashTable<T>::calculate_l(int size) {
	int power = 0;
	int n = 1;
	while (n < size) {
		n *= 2;
		power++;
	}
	return power;
}

template <typename T>
int HashTable<T>::calculate_capacity(int power) {
	int n = 1;
	for (int i = 0; i < power; ++i) {
		n *= 2;
	}
	return n;
}

template <typename T>
int HashTable<T>::lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return static_cast<int>(x);
}

template <typename T>
HashTable<T>::HashTable(int size) {
	a = 3;
	table_size = 0;
	l = calculate_l(size);
	table_capacity = calculate_capacity(l);
	table = new Node[table_capacity];
}

template <typename T>
HashTable<T>::HashTable(int size, bool random) {
	a = 3;
	table_size = 0;
	l = calculate_l(size);
	table_capacity = calculate_capacity(l);
	table = new Node[table_capacity];

	if (random) {
		for (int i = 0; i < size; ++i) {
			int random_key = lcg();
			T random_value = T();
			insert(random_key, random_value);
		}
	}
}

template <typename T>
HashTable<T>::HashTable(const HashTable& src) {
	a = src.a;
	table_size = src.table_size;
	l = src.l;
	table_capacity = src.table_capacity;
	table = new Node[table_capacity];

	for (int i = 0; i < table_capacity; ++i) {
		table[i].key = src.table[i].key;
		table[i].value = src.table[i].value;
		table[i].status = src.table[i].status;
	}
}

template <typename T>
HashTable<T>::~HashTable() {
	delete[] table;
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable& src) {
	if (this == &src) {
		return *this;
	}

	delete[] table;

	a = src.a;
	table_size = src.table_size;
	l = src.l;
	table_capacity = src.table_capacity;
	table = new Node[table_capacity];

	for (int i = 0; i < table_capacity; ++i) {
		table[i].key = src.table[i].key;
		table[i].value = src.table[i].value;
		table[i].status = src.table[i].status;
	}

	return *this;
}

template <typename T>
void HashTable<T>::print() const {
	for (int i = 0; i < table_capacity; ++i) {
		if (table[i].status == OCCUPIED) {
			std::cout << "[" << i << "] Key: " << table[i].key << " Value: " << table[i].value << endl;
		}
	}
}

#endif