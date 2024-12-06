#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Visited {
	bool dir[4];
};

bool hasLoop(std::vector<std::string>& lines, int px, int py) {
	std::vector<std::vector<Visited>> visited;
	visited.resize(lines.size());
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 0; x < lines[y].size(); ++x) {
			Visited vv;
			for (int i = 0; i < 4; ++i) {
				vv.dir[i] = false;
			}
			visited[y].push_back(vv);
		}
	}
	int dir = 0;
	int plusX[4] = { 0,1,0,-1 };
	int plusY[4] = { -1,0,1,0 };
	do {
		visited[py][px].dir[dir] = true;
		int nx = px + plusX[dir];
		int ny = py + plusY[dir];
		if (nx >= 0 && ny >= 0 && nx < lines[0].size() && ny < lines.size() && lines[ny][nx] == '#') {
			dir++;
			if (dir == 4) {
				dir = 0;
			}
		}
		else {
			px = nx;
			py = ny;
		}
	} while (px >= 0 && py >= 0 && px < lines[0].size() && py < lines.size() && visited[py][px].dir[dir] == false);
	return px >= 0 && py >= 0 && px < lines[0].size() && py < lines.size();
}
int main()
{
	std::ifstream stream("..\\input6.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> lines;
	

	while (std::getline(stream, line) && !line.empty()) {
		lines.push_back(line);
	}
	int px, py;
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 0; x < lines[y].size(); ++x) {
			if (lines[y][x] == '^') {
				px = x;
				py = y;
			}
		}
	}
	for (int y = 0; y < lines.size(); ++y) {
		for (int x = 0; x < lines[y].size(); ++x) {
			if (lines[y][x] == '.') {
				lines[y][x] = '#';
				sum += int(hasLoop(lines, px, py));
				lines[y][x] = '.';
			}
		}
	}
	std::cout << sum << std::endl;
	return 0;
}
