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
	int dir;
	bool operator<(const E& e) const {
		return score > e.score;
	}
};

int main()
{
	std::ifstream stream("..\\input16.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> map;
	std::vector<std::vector<std::vector<int>>> minScore;
	while (std::getline(stream, line) && !line.empty()) {
		map.push_back(line);
	}
	P e, s;

	minScore.resize(map.size());
	for (int y = 0; y < map.size(); ++y) {
		minScore[y].resize(map[0].size());
		for (int x = 0; x < map[0].size(); ++x) {
			minScore[y][x].resize(4, 1000000);
			if (map[y][x] == 'E') {
				e.x = x;
				e.y = y;
			}
			if (map[y][x] == 'S') {
				s.x = x;
				s.y = y;
			}
		}
	}
	int moveX[4] = { 1, 0, -1, 0 };
	int moveY[4] = { 0, 1, 0, -1 };

	std::priority_queue<E> q;
	q.push(E{ s, 0, 0 });
	int record = -1;
	while (!q.empty() && (record == -1 || q.top().score < record)) {
		E elem = q.top();
		q.pop();
		if (elem.p.x == e.x && elem.p.y == e.y) {
			if (elem.score < record || record == -1) {
				record = elem.score;
				std::cout << record << std::endl;
			}
			continue;
		}
		// Try to turn
		E elemCW = elem, elemCCW = elem;
		elemCW.score += 1000;
		elemCW.dir = (elem.dir + 1) % 4;
		elemCCW.score += 1000;
		elemCCW.dir = (elem.dir + 3) % 4;
		if (elemCW.score < minScore[elemCW.p.y][elemCW.p.x][elemCW.dir]) {
			minScore[elemCW.p.y][elemCW.p.x][elemCW.dir] = elemCW.score;
			q.push(elemCW);
		}
		if (elemCCW.score < minScore[elemCCW.p.y][elemCCW.p.x][elemCCW.dir]) {
			minScore[elemCCW.p.y][elemCCW.p.x][elemCCW.dir] = elemCCW.score;
			q.push(elemCCW);
		}
		elem.p.x += moveX[elem.dir];
		elem.p.y += moveY[elem.dir];
		elem.score++;
		if (map[elem.p.y][elem.p.x] != '#' && elem.score < minScore[elem.p.y][elem.p.x][elem.dir]) {
			minScore[elem.p.y][elem.p.x][elem.dir] = elem.score;
			q.push(elem);
		}
	}
	
	std::cout << record << std::endl;
	return 0;
}
