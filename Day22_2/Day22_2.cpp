#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct Seq
{
	int value = 0;
	int last = -1;
};
int main()
{
	std::ifstream stream("..\\input22.txt");
	std::string line;
	int sum = 0;
	std::vector<std::vector<int>> changes;
	std::vector<std::vector<int>> values;
	std::vector<Seq> sequences(19 * 19 * 19 * 19);
	while (std::getline(stream, line)) {
		std::istringstream iss(line);
		int64_t value;
		iss >> value;
		changes.push_back(std::vector<int>{});
		values.push_back(std::vector<int>{});
		for (int i = 0; i < 2000; ++i) {
			int64_t prev = value;
			value = (value ^ (value * 64)) % 16777216;
			value = (value ^ (value / 32)) % 16777216;
			value = (value ^ (value * 2048)) % 16777216;
			changes.back().push_back((value % 10 - prev % 10) + 9);
			values.back().push_back(value % 10);
		}
	}
	for (int k = 0; k < changes.size(); ++k) {
		auto& v = changes[k];
		for (int i = 0; i < v.size() - 3; ++i) {
			int index = 0;
			for (int j = 0; j < 4; ++j) {
				index = index * 19 + v[i + j];
			}
			if (sequences[index].last != k) {
				sequences[index].last = k;
				sequences[index].value += values[k][i + 3];
			}
		}
	}

	for (auto& i : sequences) {
		sum = std::max(i.value, sum);
	}
	std::cout << sum << std::endl;
	return 0;
}
