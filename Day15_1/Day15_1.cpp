#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

void move(char m, int& rx, int& ry, std::vector<std::string>& map) {
    int vx = 0, vy = 0;
	switch (m) {
	case '<': vx = -1; break;
	case '>': vx = 1; break;
	case '^': vy = -1; break;
	case 'v': vy = 1; break;
	default:return;
	}
	int sx = rx + vx, sy = ry + vy;
	int ex = sx, ey = sy;
	while (map[ey][ex] == 'O') {
		ex += vx;
		ey += vy;
	}
	if (map[ey][ex] == '#') {
		return;
	}
	map[sy][sx] = '.';
	rx = sx;
	ry = sy;
	while (sx != ex || sy != ey) {
		sx += vx;
		sy += vy;
		map[sy][sx] = 'O';
	}
}

int main()
{
	std::ifstream stream("..\\input15.txt");
	std::string line;
	int64_t sum = 0;
	std::vector<std::string> map;
	while (std::getline(stream, line) && !line.empty()) {
		map.push_back(line);
	}
	std::string moves;
	while (std::getline(stream, line) && !line.empty()) {
		moves += line;
	}

	int rx = 0;
	int ry = 0;
	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			
			if (map[y][x] == '@') {
				rx = x;
				ry = y;
				map[y][x] = '.';
				break;
			}
		}
	}
	for (char c : moves) {
		move(c, rx, ry, map);
	}

	for (int y = 0; y < map.size(); ++y) {
		for (int x = 0; x < map[0].size(); ++x) {
			std::cout << map[y][x];
			if (map[y][x] == 'O') {
				sum += y * 100 + x;
			}
		}
		std::cout << std::endl;

	}
	std::cout << sum << std::endl;
	return 0;
}
