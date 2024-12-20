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
	bool operator<(const P& other) const {
		return (y < other.y) ||
			(y == other.y && x < other.x);
	}
	bool operator==(const P& other) const {
		return (y == other.y) &&
			(x == other.x);
	}
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
	while (std::getline(stream, line)) {
		map.push_back(line);
	}
	P s, e;
	int cheat = 20;
	for (int y = 0; y < map.size(); ++y) {
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
	const auto countSteps = [&](P start, P end, auto& stepsMap) {
		int shortest = 10000000;
		stepsMap.resize(map.size());
		for (int y = 0; y < map.size(); ++y) {
			stepsMap[y].resize(map[0].size(), shortest);
		}
		std::vector<E> stack;
		stack.push_back(E{ start, 0 });
		while (!stack.empty()) {
			E p = stack.back();
			stack.pop_back();
			if (stepsMap[p.p.y][p.p.x] <= p.score) {
				continue;
			}
			stepsMap[p.p.y][p.p.x] = p.score;
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
		return stepsMap[e.y][e.x];
	};
	std::vector<std::vector<int>> cacheStart(map.size()), cacheEnd(map.size());
	int steps = countSteps(s, e, cacheStart);
	countSteps(e, s, cacheEnd);
	int diff = 100, count = 0;
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			if (map[y][x] != '#') {
				int cntS = cacheStart[y][x];
				for (int yy = -cheat; yy < cheat + 1; ++yy) {
					for (int xx = -cheat; xx < cheat + 1; ++xx) {
						P end{ x + xx, y + yy };
						int t = abs(xx) + abs(yy);
						if (t <= cheat && end.x > 0 && end.y > 0 && end.x < map[0].size() - 1 && end.y < map.size() - 1 && map[end.y][end.x] != '#') {
							int cnt = cntS + cacheEnd[end.y][end.x];
							int f = cnt + t;
							if (steps - f >= diff) {
								++count;
							}
						}
					}
				}
			}
		}
	}
	std::cout << count << std::endl;
	return 0;
}
