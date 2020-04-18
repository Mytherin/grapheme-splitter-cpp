#include "graphemesplitter.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace graphemesplitter;
using namespace std;

std::vector<std::string> split_graphemes(const char *str, size_t length) {
	std::vector<std::string> result;
	size_t pos = 0;
	while(pos < length) {
		size_t next_pos = next_grapheme(str, length, pos);
		result.push_back(std::string(str + pos, next_pos - pos));
		pos = next_pos;
	}
	return result;
}

std::vector<std::string> split_graphemes(std::string str) {
	return split_graphemes(str.c_str(), str.size());
}

string print_list(vector<string> list) {
	string str = to_string(list.size()) + " -> [";
	for(int i = 0; i < list.size(); i++) {
		if (i > 0) {
			str += ", ";
		}
		str += list[i];
	}
	str += "]";
	return str;

}

void test_split(string str, vector<string> expected_splits) {
	auto graphemes = split_graphemes(str);
	bool all_equal = true;
	if (graphemes.size() != expected_splits.size()) {
		all_equal = false;
	} else {
		bool all_equal = true;
		for(size_t i = 0; i < graphemes.size(); i++) {
			if (graphemes[i] != expected_splits[i]) {
				all_equal = false;
			}
		}
	}
	if (all_equal) {
		// printf("SUCCESS: %s -> %s\n", str.c_str(), print_list(graphemes).c_str());
	} else {
		printf("FAIL splitting %s\n: expected the following splits: %s\n but got the following splits: %s\n", str.c_str(), print_list(expected_splits).c_str(), print_list(graphemes).c_str());
		split_graphemes(str);
	}
}

void simple_test() {
	test_split("abcd", {"a", "b", "c", "d"});
	test_split("🤦🏼‍♂️🤦🏼‍♂️🤦🏼‍♂️", {"🤦🏼‍♂️", "🤦🏼‍♂️", "🤦🏼‍♂️"});
	test_split("🌷🎁💩😜👍🏳️‍🌈", {"🌷", "🎁", "💩", "😜", "👍", "🏳️‍🌈"});
	test_split("Ĺo͂řȩm̅", {"Ĺ", "o͂", "ř", "ȩ", "m̅"});
	test_split("뎌쉐", {"뎌", "쉐"});
	test_split("अनुच्छेद", {"अ", "नु", "च्", "छे", "द"});
	test_split("S̈a", {"S̈", "a"});
	test_split("Z͑ͫ̓ͪ̂ͫ̽͏̴̙̤̞͉͚̯̞̠͍A̴̵̜̰͔ͫ͗͢L̠ͨͧͩ͘G̴̻͈͍͔̹̑͗̎̅͛́Ǫ̵̹̻̝̳͂̌̌͘!͖̬̰̙̗̿̋ͥͥ̂ͣ̐́́͜͞", {"Z͑ͫ̓ͪ̂ͫ̽͏̴̙̤̞͉͚̯̞̠͍", "A̴̵̜̰͔ͫ͗͢", "L̠ͨͧͩ͘", "G̴̻͈͍͔̹̑͗̎̅͛́", "Ǫ̵̹̻̝̳͂̌̌͘", "!͖̬̰̙̗̿̋ͥͥ̂ͣ̐́́͜͞"});
}

bool ishex(char c) {
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

int hex_value(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else {
		return 10 + c - 'A';
	}
}

int main() {
	simple_test();
	ifstream file("test/GraphemeBreakTest.txt");
	string line;
	string break_possible = "÷";
	string no_break_possible = "×";
	while (getline(file, line)) {
		if (line[0] == '#') {
			continue;
		}
		vector<string> expected_splits;
		string total_string;
		string current_string;
		for(size_t i = 0; i < line.size(); i++) {
			if (line[i] == '#') {
				break;
			}
			if (ishex(line[i])) {
				// start of hex
				size_t j = i + 1;
				while(ishex(line[j])) {
					j++;
				}
				string hex = line.substr(i, j - i);
				int hex_multiplier = 1;
				int codepoint = 0;
				for(size_t k = hex.size(); k > 0; k--) {
					codepoint += hex_multiplier * hex_value(hex[k - 1]);
					hex_multiplier *= 16;
				}
				string utf8str = codepoint_to_utf8(codepoint);
				current_string += utf8str;
				total_string += utf8str;
				i = j;
				continue;
			}
			if (line.substr(i, break_possible.size()) == break_possible) {
				// break possible here
				if (current_string.size() > 0) {
					expected_splits.push_back(current_string);
					current_string = "";
				}
			} else if (line.substr(i, no_break_possible.size()) == no_break_possible) {
				// no break possible here
			}
		}
		if (current_string.size() != 0) {
			throw "EEK";
		}
		test_split(total_string, expected_splits);
	}
}