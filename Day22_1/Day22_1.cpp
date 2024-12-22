#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

int main()
{
	std::ifstream stream("..\\input22.txt");
	std::string line;
	int64_t sum = 0;
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		int64_t value;
		iss >> value;
		for (int i = 0; i < 2000; ++i) {
			int64_t prev = value;
			value = (value ^ (value * 64)) % 16777216;
			value = (value ^ (value / 32)) % 16777216;
			value = (value ^ (value * 2048)) % 16777216;
		}
		sum += value;
	}
	std::cout << sum << std::endl;
	return 0;
}
