#include <iostream>
#include "HashTable.h"

int lenght(const char* str) {
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
	int str_len = lenght(string);

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
	HashTable<int> test_table(5, true);
	std::cout << "Random table:\n";
	test_table.print();
	std::cout << "\n";

	const char* roman1 = "MCMXCIV";
	const char* roman2 = "LVIII";

	std::cout << "Roman: " << roman1 << " is Arabic: " << roman_to_arabic(roman1) << "\n";
	std::cout << "Roman: " << roman2 << " is Arabic: " << roman_to_arabic(roman2) << "\n";

	return 0;
}