#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

struct Robot {
	int x, y;
	int vx, vy;

	void step(int maxx, int maxy) {
		x = x + vx;
		y = y + vy;
		if (x >= 0) {
			x %= maxx;
		}
		else {
			x += ((-x + maxx - 1) / maxx) * maxx;
		}
		if (y >= 0) {
			y %= maxy;
		}
		else {
			y += ((-y + maxy - 1) / maxy) * maxy;
		}
	}
};

int main()
{
	std::ifstream stream("..\\input14.txt");
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		if (!line.empty()) {
			lines.push_back(line);
		}
	}
	std::vector<Robot> robots;
	for (int i = 0; i < lines.size(); i += 1) {
		std::istringstream is(lines[i]);
		Robot r;
		char c;
		is >> c;
		is >> c;
		is >> r.x;
		is >> c;
		is >> r.y;
		is >> c;
		is >> c;
		is >> r.vx;
		is >> c;
		is >> r.vy;
		robots.push_back(r);
	}
	int maxy = 103;
	int maxx = 101;
	int maxPeriod = 0;
	for (auto& r : robots) {
		int x = r.x;
		int y = r.y;
		int step = 0;
		do {
			r.step(maxx, maxy);
			++step;
		} while (r.x != x || r.y != y);
		maxPeriod = std::max(step, maxPeriod);
	}
	
	std::vector<std::string> field;
	field.resize(maxy);
	for (int y = 0; y < maxy; ++y) {
		field[y].resize(maxx);
	}
	int step = 1;
	while (step <= maxPeriod) {
		std::cout << step << std::endl;
		for (int y = 0; y < maxy; ++y) {
			for (int x = 0; x < maxx; ++x) {
				field[y][x] = '.';
			}
		}
		for (int i = 0; i < robots.size(); ++i) {
			robots[i].step(maxx, maxy);
			field[robots[i].y][robots[i].x] = 'X';
		}
		if (step == 6668) {
			for (int y = 0; y < maxy; ++y) {
				for (int x = 0; x < maxx; ++x) {
					std::cout << field[y][x];
				}
				std::cout << std::endl;
			}
		}
		++step;
	}

	return 0;
}
