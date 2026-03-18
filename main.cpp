#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "Set.h"

using namespace std;

int lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return static_cast<int>(x); //cast because W4
}

void test_fill(int N) {
	long long time_set = 0;
	long long time_vector = 0;
	const int attempts = 100;

	for (int i = 0; i < attempts; ++i) {
		Set s;
		int count = 0;
		auto start = chrono::high_resolution_clock::now();
		while (count < N) {
			if (s.insert(lcg())) {
				count++;
			}
		}
		auto end = chrono::high_resolution_clock::now();
		time_set += chrono::duration_cast<chrono::microseconds>(end - start).count();

		vector<int> v;
		count = 0;
		start = chrono::high_resolution_clock::now();
		while (count < N) {
			int val = lcg();
			if (find(v.begin(), v.end(), val) == v.end()) {
				v.push_back(val);
				count++;
			}
		}
		end = chrono::high_resolution_clock::now();
		time_vector += chrono::duration_cast<chrono::microseconds>(end - start).count();
	}

	cout << "Fill " << N << " with " << attempts << " attempts.\n";
	cout << "Set " << time_set / attempts << " microseconds.\n";
	cout << "Vector " << time_vector / attempts << " microseconds.\n";
}

void test_search(int N) {
	long long time_set = 0;
	long long time_vector = 0;
	const int attempts = 1000;

	Set s;
	vector<int> v;
	int count = 0;
	while (count < N) {
		int value = lcg();
		if (s.insert(value)) {
			v.push_back(value);
			count++;
		}
	}

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < attempts; ++i) {
		s.contains(lcg());
	}
	auto end = chrono::high_resolution_clock::now();
	time_set += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < attempts; ++i) {
		int value = lcg();
		(void)find(v.begin(), v.end(), value); //(void) W4
	}
	end = chrono::high_resolution_clock::now();
	time_vector += chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	cout << "Search in " << N << " elements with " << attempts << " attempts.\n";
	cout << "Set " << time_set / attempts << " nanoseconds.\n";
	cout << "Vector " << time_vector / attempts << " nanoseconds.\n";
}

void test_remove_add(int N) {
	long long time_set = 0;
	long long time_vector = 0;
	const int attempts = 1000;

	Set s;
	vector<int> v;
	int count = 0;
	while (count < N) {
		int value = lcg();
		if (s.insert(value)) {
			v.push_back(value);
			count++;
		}
	}

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < attempts; ++i) {
		s.insert(lcg());
		s.erase(lcg());
	}
	auto end = chrono::high_resolution_clock::now();
	time_set += chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < attempts; ++i) {
		int add_value = lcg();
		int erase_value = lcg();
		
		if (find(v.begin(), v.end(), add_value) == v.end()) {
			v.push_back(add_value);
		}
		auto found_elem = find(v.begin(), v.end(), erase_value);
		if ( found_elem != v.end()) {
			v.erase(found_elem);
		}
	}
	end = chrono::high_resolution_clock::now();
	time_vector += chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "Add/remove in " << N << " elements with " << attempts << " attempts.\n";
	cout << "Set " << time_set / attempts << " microseconds.\n";
	cout << "Vector " << time_vector / attempts << " microseconds.\n";
}

bool is_subset(const Set& set1, const Set& set2) {
	std::vector<int> subset = set1.to_vector();

	for (int key : subset) { //Range-based
		if (!set2.contains(key)) {
			return false;
		}
	}

	return true;
}

bool is_any_subset(const Set& set1, const Set& set2) {
	return is_subset(set1, set2) || is_subset(set2, set1);
}

int main() {

	test_fill(100000);
	test_search(1000);
	test_remove_add(10000);

	Set s1;
	s1.insert(1);
	s1.insert(5);

	Set s2;
	s2.insert(1);
	s2.insert(2);
	s2.insert(3);
	s2.insert(4);

	if (is_any_subset(s1, s2)) {
		std::cout << "True!\n";
	}
	else {
		std::cout << "False!\n";
	}

	std::cin.get();
	return 0;
}
