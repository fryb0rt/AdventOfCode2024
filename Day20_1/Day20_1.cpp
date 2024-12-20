#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

struct P {
	int x, y;
};


struct E {
	P p;
	int score;
};


int main()
{
	std::ifstream stream("..\\input20.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> map;
	std::vector<std::vector<int>> stepsMap;
	while (std::getline(stream, line)) {
		map.push_back(line);
	}
	P s, e;
	stepsMap.resize(map.size());
	for (int y = 0; y < map.size(); ++y) {
		stepsMap[y].resize(map[0].size(), 10000000);
		for (int x = 0; x < map[0].size(); ++x) {
			if (map[y][x] == 'S') {
				s.x = x;
				s.y = y;
			}
			if (map[y][x] == 'E') {
				e.x = x;
				e.y = y;
			}
		}
	}
	int dirX[4] = { 1,0,-1,0 };
	int dirY[4] = { 0, 1,0,-1 };
	const auto countSteps = [&]() {
		for (int y = 0; y < map.size(); ++y) {
			for (int x = 0; x < map[0].size(); ++x) {
				stepsMap[y][x] = 10000000;
			}
		}
		std::vector<E> stack;
		stack.push_back(E{ s, 0 });
		int shortest = 10000000;
		while (!stack.empty()) {
			E p = stack.back();
			stack.pop_back();
			if (stepsMap[p.p.y][p.p.x] <= p.score) {
				continue;
			}
			stepsMap[p.p.y][p.p.x] = p.score;
			if (p.p.x == e.x && p.p.y == e.y && p.score < shortest) {
				shortest = p.score;
			}
			if (p.score >= shortest) {
				continue;
			}
			++p.score;
			for (int c = 0; c < 4; ++c) {
				E p2 = p;
				p2.p.x += dirX[c];
				p2.p.y += dirY[c];
				if (map[p2.p.y][p2.p.x] != '#') {
					stack.push_back(p2);
				}
			}
		}
		return shortest;
	};
	int steps = countSteps();
	std::vector<int> ss;
	for (int y = 1; y < map.size() - 1; ++y) {
		std::cout << y << std::endl;
		for (int x = 1; x < map[0].size() - 1; ++x) {
			if (map[y][x] == '#') {
				map[y][x] = '.';
				int cnt = steps - countSteps();
				if (cnt >= 100)
					ss.push_back(cnt);
				map[y][x] = '#';
			}
		}
	}
	std::cout << ss.size() << std::endl;
	return 0;
}
