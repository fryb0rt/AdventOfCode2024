#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Rule {
	int first, after;
};


int main()
{
	std::ifstream stream("..\\input5.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<Rule> rules;

	while (std::getline(stream, line) && !line.empty()) {
		std::istringstream iss(line);
		int num1, num2;
		char c;
		iss >> num1 >> c >> num2;
		rules.push_back(Rule{ num1, num2 });
	}
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		std::vector<int> numbers;
		int num;
		char c;
		while (!iss.eof()) {
			iss >> num >> c;
			numbers.push_back(num);
		}
		bool wrong = false;
		for (int i = 0; i < numbers.size(); ++i) {
			for (auto rule : rules) {
				if (numbers[i] == rule.first) {
					for (int j = 0; j < i; ++j) {
						if (numbers[j] == rule.after) {
							wrong = true;
						}
					}
				}
			}
		}
		if (wrong) {
			for (int pos = 0; pos < numbers.size(); ++pos) {
				for (int i = pos; i < numbers.size(); ++i) {
					std::swap(numbers[pos], numbers[i]);
					bool wrong = false;
					for (auto rule : rules) {
						if (numbers[pos] == rule.after) {
							for (int j = pos + 1; j < numbers.size(); ++j) {
								if (numbers[j] == rule.first) {
									wrong = true;
								}
							}
						}
					}
					if (wrong) {
						std::swap(numbers[pos], numbers[i]);
					}
					else {
						break;
					}

				}
			}
			const int middle = numbers[numbers.size() / 2];
			sum += middle;
		}
	}
	std::cout << sum << std::endl;
	return 0;
}