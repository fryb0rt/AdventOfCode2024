#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct Node {
	std::string name;
	int value;
};

struct Key {
	std::vector<int> heights;
};
int main()
{
	std::ifstream stream("..\\input25.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<Key> keys;
	std::vector<Key> locks;
	while (!stream.eof()) {
		std::vector<std::string> map;
		while (std::getline(stream, line) && !line.empty()) {
			map.push_back(line);
		}
		std::vector<int> h;
		for (int i = 0; i < map[0].size(); ++i) {
			int cnt = 0;
			for (int y = 0; y < map.size(); ++y) {
				cnt += map[y][i] == '#';
			}
			h.push_back(cnt - 1);
		}
		int cnt = 0;
		for (int i = 0; i < map[0].size(); ++i) {
			cnt += map[0][i] == '#';
		}
		if (cnt == map[0].size()) {
			locks.push_back(Key{ h });
		}
		else {
			keys.push_back(Key{ h });
		}
	}

	for (auto& k : keys) {
		for (auto& l : locks) {
			bool ok = true;
			for (int i = 0; i < k.heights.size(); ++i) {
				ok &= k.heights[i] + l.heights[i] < 6;
			}
			sum += ok;
		}
	}
	
	std::cout << sum << std::endl;
	return 0;
}
