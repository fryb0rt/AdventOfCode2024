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
	std::ifstream stream("..\\input4.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> data;
	while (std::getline(stream, line)) {
		data.push_back(line);
	}
	std::string word = "MAS";
	const auto isXmas = [&](int x, int y) {
		int ok = 0;
		bool z = true;
		for (int i = 0; i < word.size(); ++i) {
			if (word[i] != data[y + i][x + i]) {
				z = false;
			}
		}
		ok += int(z);
		z = true;
		for (int i = 0; i < word.size(); ++i) {
			if (word[2-i] != data[y + i][x + i]) {
				z = false;
			}
		}
		ok += int(z);
		z = true;
		for (int i = 0; i < word.size(); ++i) {
			if (word[i] != data[y + 2 - i][x + i]) {
				z = false;
			}
		}
		ok += int(z);
		z = true;
		for (int i = 0; i < word.size(); ++i) {
			if (word[2 - i] != data[y +2 - i][x + i]) {
				z = false;
			}
		}
		ok += int(z);
		return ok == 2;
	};
	for (int y = 0; y < data.size()-2; ++y) {
		for (int x = 0; x < data[y].size()-2; ++x) {
			sum += isXmas(x, y);
			
		}
	}
	std::cout << sum << std::endl;
	return 0;
}