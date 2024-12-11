#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream stream("..\\input11.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<int64_t> stones;
	while (!stream.eof()) {
		int64_t num;
		stream >> num;
		stones.push_back(num);
	}
	const auto even = [&](int64_t num) {
		std::ostringstream s;
		s << num;
		auto ss = s.str();
		return ss.length() % 2 == 0;
	};
	const auto split = [&](int64_t index) {
		auto num = stones[index];
		std::ostringstream s;
		s << num;
		auto ss = s.str();
		std::istringstream i(ss.substr(0, ss.length() / 2));
		i >> num;
		stones[index] = num;
		std::istringstream i2(ss.substr(ss.length() / 2));
		i2 >> num;
		stones.insert(stones.begin() + index + 1, num);
	};
	for (int b = 0; b < 25; ++b) {
		for (int i = 0; i < stones.size(); ++i) {
			if (stones[i] == 0) {
				stones[i] = 1;
			}
			else if (even(stones[i])) {
				split(i);
				++i;
			}
			else {
				stones[i] *= 2024;
			}
		}
	}
	std::cout << stones.size() << std::endl;
	return 0;
}
