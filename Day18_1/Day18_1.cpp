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
	bool operator<(const E& e) const {
		return score > e.score;
	}
};

int main()
{
	std::ifstream stream("..\\input18.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::vector<int>> map;
	int maxX = 71, maxY = 71;
	std::vector<P> coords;
	while (std::getline(stream, line) && !line.empty()) {
		std::istringstream iss(line);
		int num;
		char c;
		iss >> num;
		iss >> c;
		P p;
		p.x = num;
		iss >> num;
		p.y = num;
		coords.push_back(p);
	}
	map.resize(maxY);
	for (int y = 0; y < maxY; ++y) {
		map[y].resize(maxX, -1);
	}
	for (int i = 0; i < 1024; ++i) {
		P p = coords[i];
		map[p.y][p.x] = 0;
	}
	for (int y = 0; y < maxY; ++y) {
		for (int x = 0; x < maxX; ++x) {
			std::cout << map[y][x];
		}
		std::cout << std::endl;
	}
	std::vector<E> stack;
	stack.push_back(E{ P{0,0}, 0 });
	while (!stack.empty()) {
		E e = stack.back();
		stack.pop_back();
		if (map[e.p.y][e.p.x] != -1 && map[e.p.y][e.p.x] <= e.score) {
			continue;
		}
		map[e.p.y][e.p.x] = e.score;
		if (e.p.x > 0 && map[e.p.y][e.p.x - 1] != 0) {
			stack.push_back(E{ P{e.p.x - 1, e.p.y}, e.score + 1 });
		}
		if (e.p.y > 0 && map[e.p.y - 1][e.p.x] != 0) {
			stack.push_back(E{ P{e.p.x, e.p.y - 1}, e.score + 1 });
		}
		if (e.p.x < maxX - 1 && map[e.p.y][e.p.x + 1] != 0) {
			stack.push_back(E{ P{e.p.x + 1, e.p.y}, e.score + 1 });
		}
		if (e.p.y < maxY - 1 && map[e.p.y + 1][e.p.x] != 0) {
			stack.push_back(E{ P{e.p.x, e.p.y + 1}, e.score + 1 });
		}
	}
	std::cout << map[maxY - 1][maxX - 1] << std::endl;
	return 0;
}
