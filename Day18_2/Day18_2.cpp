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
	P prev;
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
	std::vector<std::vector<P>> prev;
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
	for (int c = 1024; c < coords.size();) {
		map.resize(maxY);
		prev.resize(maxY);
		for (int y = 0; y < maxY; ++y) {
			map[y].resize(maxX, -1);
			prev[y].resize(maxX);
			for (int x = 0; x < maxX; ++x) {
				map[y][x] = -1;
			}
		}
		for (int i = 0; i < c; ++i) {
			P p = coords[i];
			map[p.y][p.x] = 0;
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
			prev[e.p.y][e.p.x] = e.prev;
			if (e.p.x > 0 && map[e.p.y][e.p.x - 1] != 0) {
				stack.push_back(E{ P{e.p.x - 1, e.p.y}, e.score + 1, e.p });
			}
			if (e.p.y > 0 && map[e.p.y - 1][e.p.x] != 0) {
				stack.push_back(E{ P{e.p.x, e.p.y - 1}, e.score + 1, e.p });
			}
			if (e.p.x < maxX - 1 && map[e.p.y][e.p.x + 1] != 0) {
				stack.push_back(E{ P{e.p.x + 1, e.p.y}, e.score + 1, e.p });
			}
			if (e.p.y < maxY - 1 && map[e.p.y + 1][e.p.x] != 0) {
				stack.push_back(E{ P{e.p.x, e.p.y + 1}, e.score + 1, e.p });
			}
		}
		if (map[maxY - 1][maxX - 1] == -1) {
			std::cout << coords[c-1].x << "," << coords[c - 1].y << std::endl;
			break;
		}
		else {
			std::vector<P> path;
			P p{ maxY - 1, maxX - 1 };
			while (p.x != 0 || p.y != 0) {
				path.push_back(p);
				p = prev[p.y][p.x];
			}
			bool hit = false;
			while (!hit) {
				P p = coords[c];
				for (P p2 : path) {
					if (p2.x == p.x && p2.y == p.y) {
						hit = true;
						break;
					}
				}
				++c;
			}
		}
	}
	return 0;
}
