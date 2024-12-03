#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

int main()
{
	std::ifstream stream("..\\input3.txt");
	std::string line, line2;
	int64_t sum = 0;
	std::vector<int> dos;
	std::vector<int> donts;
	while (std::getline(stream, line2)) {
		line += line2;
	}
	int offset = 0;
	while (true) {
		auto mulPos = line.find("do()", offset);
		if (mulPos == std::string::npos) {
			break;
		}
		dos.push_back(mulPos);
		offset = mulPos += 4;
	}
	offset = 0;
	while (true) {
		auto mulPos = line.find("don't()", offset);
		if (mulPos == std::string::npos) {
			break;
		}
		donts.push_back(mulPos);
		offset = mulPos += 7;
	}
	offset = 0;
	while (true) {
		auto mulPos = line.find("mul(", offset);
		if (mulPos == std::string::npos) {
			break;
		}
		offset = mulPos += 4;
		int number1 = 0;
		int i = 0;
		while (isDigit(line[offset + i])) {
			number1 = number1 * 10 + line[offset + i] - '0';
			++i;
		}
		if (i < 1 || i > 3 || line[offset + i] != ',') {
			continue;
		}
		offset += i + 1;
		i = 0;
		int number2 = 0;
		while (isDigit(line[offset + i])) {
			number2 = number2 * 10 + line[offset + i] - '0';
			++i;
		}
		if (i < 1 || i > 3 || line[offset + i] != ')') {
			continue;
		}
		int closestDo = -1;
		for (int j : dos) {
			if (j < mulPos && j > closestDo) {
				closestDo = j;
			}
		}
		int closestDont = -1;
		for (int j : donts) {
			if (j < mulPos && j > closestDont) {
				closestDont = j;
			}
		}
		offset += i + 1;
		if (closestDont != -1 && closestDont > closestDo) {
			continue;
		}
		sum += number1 * number2;
	}
	std::cout << sum << std::endl;
	return 0;
}