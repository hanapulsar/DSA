#include <iostream>
#include "HashTable.h"

int length(const char* str) {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

int roman_hash(char c) {
	if (c == 'I') return 1;
	if (c == 'V') return 5;
	if (c == 'X') return 10;
	if (c == 'L') return 50;
	if (c == 'C') return 100;
	if (c == 'D') return 500;
	if (c == 'M') return 1000;
	return 0;
}

int roman_to_arabic(const char* string) {
	HashTable<int> table(16);

	table.insert('I', roman_hash('I'));
	table.insert('V', roman_hash('V'));
	table.insert('X', roman_hash('X'));
	table.insert('L', roman_hash('L'));
	table.insert('C', roman_hash('C'));
	table.insert('D', roman_hash('D'));
	table.insert('M', roman_hash('M'));

	int total = 0;
	int prev_val = 0;
	int str_len = length(string);

	for (int i = str_len - 1; i >= 0; --i) {
		char curr_char = string[i];
		int* value_ptr = table.search(curr_char);

		if (value_ptr != nullptr) {
			int curr_val = *value_ptr;

			if (curr_val < prev_val) {
				total -= curr_val;
			}
			else {
				total += curr_val;
			}
			prev_val = curr_val;
		}
	}
	return total;
}

int main() {
	std::cout << "Test 1: Basic Operations\n";
	HashTable<int> table(8);
	table.insert(10, 100);
	table.insert(20, 200);
	table.insert(30, 300);
	table.print();

	std::cout << "\nTest 2: Search and Assign\n";
	int* found = table.search(20);
	if (found) std::cout << "Found key 20, value: " << *found << "\n";

	table.insert_or_assign(20, 999);
	std::cout << "After assigning 999 to key 20:\n";
	table.print();

	std::cout << "\nTest 3: Erase and Linear Probing\n";
	table.erase(20);
	std::cout << "After erasing key 20:\n";
	table.print();

	int* search_after_delete = table.search(30);
	if (search_after_delete) {
		std::cout << "Key 30 still reachable after erasing 20: " << *search_after_delete << "\n";
	}

	std::cout << "\nTest 4: Copying\n";
	HashTable<int> copied_table = table;
	std::cout << "Copied table contents:\n";
	copied_table.print();

	std::cout << "\nTest 5: Collision Count\n";
	std::cout << "Elements with same hash as key 30: " << table.count(30) << "\n";

	std::cout << "\nTest 6: Random (5)\n";
	HashTable<int> test_table(5, true);
	std::cout << "Random table:\n";
	test_table.print();
	std::cout << "\n";

	std::cout << "\nTest 7: Roman to Arabic\n";
	const char* roman1 = "MCMXCIV";
	const char* roman2 = "LVIII";
	std::cout << "Roman: " << roman1 << " is Arabic: " << roman_to_arabic(roman1) << "\n";
	std::cout << "Roman: " << roman2 << " is Arabic: " << roman_to_arabic(roman2) << "\n";

	return 0;
}