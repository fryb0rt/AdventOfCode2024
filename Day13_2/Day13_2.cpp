#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

int64_t solve(int64_t aX, int64_t aY, int64_t bX, int64_t bY, int64_t priceX, int64_t priceY) {
	const int64_t det = aX * bY - bX * aY;
	if (det != 0) {
		const int64_t a = priceX * bY - priceY * bX;
		const int64_t b = priceY * aX - priceX * aY;
		if (a % det == 0 && b % det == 0) {
			return (a * 3 + b * 1) / det;
		}
	}
	return 0;
}

int main()
{
	std::ifstream stream("..\\input13.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}

	for (int i = 0; i < lines.size(); i += 3) {
		std::istringstream i1(lines[i].substr(std::string("Button A: X+").size()));
		int numX1, numY1;
		i1 >> numX1;
		char c;
		i1 >> c;
		i1 >> c;
		i1 >> c;
		i1 >> numY1;

		std::istringstream i2(lines[i + 1].substr(std::string("Button B: X+").size()));
		int numX2, numY2;
		i2 >> numX2;
		i2 >> c;
		i2 >> c;
		i2 >> c;
		i2 >> numY2;

		std::istringstream i3(lines[i + 2].substr(std::string("Prize: X=").size()));
		int numX3, numY3;
		i3 >> numX3;
		i3 >> c;
		i3 >> c;
		i3 >> c;
		i3 >> numY3;
		sum += solve(numX1, numY1, numX2, numY2, int64_t(numX3) + 10000000000000, int64_t(numY3) + 10000000000000);
	}

	std::cout << sum << std::endl;
	return 0;
}
