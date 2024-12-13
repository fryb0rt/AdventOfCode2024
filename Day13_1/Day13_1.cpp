#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

int solve(int aX, int aY, int bX, int bY, int priceX, int priceY) {
	int smallest = 0;
	for (int a = 0; a < 101; ++a) {
		for (int b = 0; b < 101; ++b) {
			int64_t X = aX * a + bX * b;
			int64_t Y = aY * a + bY * b;
			int value = a * 3 + b * 1;
			if (X == priceX && Y == priceY && (smallest > value || smallest == 0)) {
				smallest = value;
			}
		}
	}
	return smallest;
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

		std::istringstream i2(lines[i+1].substr(std::string("Button B: X+").size()));
		int numX2, numY2;
		i2 >> numX2;
		i2 >> c;
		i2 >> c;
		i2 >> c;
		i2 >> numY2;

		std::istringstream i3(lines[i+2].substr(std::string("Prize: X=").size()));
		int numX3, numY3;
		i3 >> numX3;
		i3 >> c;
		i3 >> c;
		i3 >> c;
		i3 >> numY3;
		sum += solve(numX1, numY1, numX2, numY2, numX3, numY3);
	}

	std::cout << sum << std::endl;
	return 0;
}
