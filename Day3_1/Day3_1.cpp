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
	std::string line;
	int64_t sum = 0;
	while (std::getline(stream, line)) {
		int offset = 0;
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
			sum += number1 * number2;
			offset += i + 1;
		}
	}
	std::cout << sum << std::endl;
	return 0;
}