#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>


struct Key {
	int b;
	int64_t num;
	bool operator<(const Key& other) const {
		return b < other.b || (b == other.b && num < other.num);
	}
	int64_t stones;
};

bool even(int64_t num) {
	std::ostringstream s;
	s << num;
	auto ss = s.str();
	return ss.length() % 2 == 0;
};

void split(int64_t num, int64_t& num1, int64_t& num2) {
	std::ostringstream s;
	s << num;
	auto ss = s.str();
	std::istringstream i(ss.substr(0, ss.length() / 2));
	i >> num1;
	std::istringstream i2(ss.substr(ss.length() / 2));
	i2 >> num2;
};

std::set<Key> keys;

const int stepCount = 75;

int64_t countSplits(int64_t number, int step) {
	auto it = keys.find(Key{ step, number });
	if (it != keys.end()) {
		return it->stones;
	}
	if (step == stepCount) {
		return 1;
	}
	int64_t returnNum;
	if (number == 0) {
		returnNum = countSplits(1, step + 1);
	}
	else if (even(number)) {
		int64_t num1, num2;
		split(number, num1, num2);
		returnNum = countSplits(num1, step + 1) + countSplits(num2, step + 1);
	}
	else {
		returnNum = countSplits(number * 2024, step + 1);
	}
	keys.insert(Key{ step, number, returnNum });
	return returnNum;
};

int main()
{
	std::ifstream stream("..\\input11.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<int64_t> stones;
	std::set<Key> keys;
	while (!stream.eof()) {
		int64_t num;
		stream >> num;
		stones.push_back(num);
	}

	for (int i = 0; i < stones.size(); ++i) {
		sum += countSplits(stones[i], 0);
	}

	std::cout << sum << std::endl;
	return 0;
}
