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
	std::ifstream stream("..\\input12.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<int64_t> stones;
	std::set<Key> keys;
	std::vector<std::string> lines;
	while (std::getline(stream, line) && !line.empty()) {
		lines.push_back(line);
	}

	const auto value = [&](int y, int x) {
		char c = lines[y][x];
		if (c == '.') {
			return 0;
		}
		struct P {
			int x, y;
		};
		std::vector<P> stack, found;
		stack.push_back(P{ x,y });
		while (!stack.empty()) {
			P  p = stack.back();
			stack.pop_back();
			if (lines[p.y][p.x] == '-') {
				continue;
			}
			lines[p.y][p.x] = '-';
			if (p.x > 0 && lines[p.y][p.x - 1] == c) {
				stack.push_back(P{ p.x - 1, p.y });
			}
			if (p.y > 0 && lines[p.y-1][p.x] == c) {
				stack.push_back(P{ p.x, p.y - 1 });
			}
			if (p.x < lines[0].size() - 1 && lines[p.y][p.x + 1] == c) {
				stack.push_back(P{ p.x + 1, p.y });
			}
			if (p.y < lines.size() - 1 && lines[p.y + 1][p.x] == c) {
				stack.push_back(P{ p.x, p.y + 1 });
			}
			found.push_back(p);
		}
		int area = found.size();
		int perimeter = 0;
		stack = found;
		while (!stack.empty()) {
			P  p = stack.back();
			stack.pop_back();
			if (p.x == 0 || lines[p.y][p.x - 1] != '-') {
				++perimeter;
			}
			if (p.y == 0 || lines[p.y - 1][p.x] != '-') {
				++perimeter;
			}
			if (p.x == lines[0].size() - 1 || lines[p.y][p.x + 1] != '-') {
				++perimeter;
			}
			if (p.y == lines.size() - 1 || lines[p.y + 1][p.x] != '-') {
				++perimeter;
			}
		}
		stack = found;
		while (!stack.empty()) {
			P  p = stack.back();
			stack.pop_back();
			lines[p.y][p.x] = '.';
		}
		return perimeter * area;
	};
	for (int i = 0; i < lines.size(); ++i) {
		for (int j = 0; j < lines[i].size(); ++j) {
			sum += value(i, j);
		}
	}

	std::cout << sum << std::endl;
	return 0;
}
